from parser import parse_file
from loguru import logger
from transformers.loop_interchange import LoopInterchangeV2
from variable_map import VariableMap, restrict_var_map, calculate_array_sizes
from simple_formatter import SimpleFormatter
from multiprocessing import Pool
from build import PathBuilder
from codegen import CodeGen
import sys

pattern_str = 'delete_me'
n_programs = 2
n_mutations = 3
output_dir = pattern_str

logger.remove()
logger.add(sys.stdout, level='INFO')
logger.add(sink = 'multiple.log',
           level = 'INFO',
           format = ('{process.name} | '
                     '{time:YYYYMMDD_HH:mm:ss.SSS} | '
                     '{file}:{function}:{line} | '
                     '{message}'),
           enqueue = True)

program, _ = parse_file('loops/multiple.loop')
logger.info(program.pprint())

default_min = 0
default_max = 64
var_map = VariableMap(default_min, default_max)

def calculate_program_parameters(program, var_map):
    restricted = restrict_var_map(program, var_map)
    logger.info('Restricted var map:\n' + restricted.pprint())
    array_sizes = calculate_array_sizes(program.decls, restricted)
    return restricted, array_sizes

def iterate_programs(program, restricted, array_sizes, n):
    count = 0
    if count >= n:
        return

    yield program
    count += 1

    # print(var_map.pprint())
    loop_interchange = LoopInterchangeV2(program)
    def iterate_mutations():
        nonlocal count

        for mutation in loop_interchange.transform(program, restricted):
            if count >= n:
                break
            yield mutation
            count += 1

    yield from iterate_mutations()

def program_str(p):
    return f'p{p:04d}'

def mutation_str(m):
    return f'm{m:04d}'

patterns = []

codegen = CodeGen(output_dir)

def generate_batch(p):
    p_str = program_str(p)

    new_var_map, new_array_sizes = calculate_program_parameters(program, var_map)
    codegen.generate_wrapper(pattern_str, p_str,
                             program, new_var_map, new_array_sizes)

    m = 0
    mutations = []
    for mutation in iterate_programs(program, new_var_map, new_array_sizes, n_mutations):
        m_str = mutation_str(m)
        codegen.generate_code(pattern_str, p_str, m_str,
                              mutation, new_var_map, new_array_sizes)
        m += 1

for p in range(n_programs):
    generate_batch(p)
pool = Pool()

pool.map(generate_batch, range(n_programs))
codegen.generate_pattern_file()
