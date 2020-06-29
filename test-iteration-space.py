from parser import parse_file
from loguru import logger
from transformers.loop_interchange import LoopInterchangeV2
from variable_map import VariableMap, restrict_var_map, calculate_array_sizes
from simple_formatter_v2 import SimpleFormatter
from multiprocessing import Pool
from build import PathBuilder
from codegen import CodeGen
import sys

pattern_str = 'new_formatter'
n_programs = 1
n_mutations = 1
output_dir = pattern_str

logger.remove()
logger.add(sys.stdout, level='INFO')
logger.add(sink = 'new_formmater.log',
           level = 'INFO',
           format = ('{process.name} | '
                     '{time:YYYYMMDD_HH:mm:ss.SSS} | '
                     '{file}:{function}:{line} | '
                     '{message}'),
           enqueue = True)

program, _ = parse_file('simple.loop')
logger.info(program.pprint())

default_min = 0
default_max = 64
var_map = VariableMap(default_min, default_max)

def iterate_programs(program, var_map, n):
    count = 0
    if count >= n:
        return

    restricted = restrict_var_map(program, var_map)
    logger.info('Restricted var map:\n' + restricted.pprint())
    array_sizes = calculate_array_sizes(program.decls, restricted)

    yield (program, restricted, array_sizes)
    count += 1

    # print(var_map.pprint())
    loop_interchange = LoopInterchangeV2(program)
    def iterate_mutations():
        nonlocal count

        for mutation in loop_interchange.transform(program, restricted):
            if count >= n:
                break
            yield (mutation, restricted, array_sizes)
            count += 1

    yield from iterate_mutations()

# from pathlib import Path
# Path(output_dir).mkdir(parents=True, exist_ok=True)
# import os
# os.symlink('dodo.py', f'{output_dir}/dodo.py')

def program_str(p):
    return f'p{p:04d}'

def mutation_str(m):
    return f'm{m:04d}'

patterns = []

codegen = CodeGen(output_dir)

def generate_batch(p):
    p_str = program_str(p)
    m = 0
    mutations = []
    for (mutation, new_var_map, new_array_sizes) in iterate_programs(program, var_map, n_mutations):
        m_str = mutation_str(m)
        codegen.generate_code(pattern_str, p_str, m_str,
                              mutation, program, new_var_map, new_array_sizes)
        # mutations.append(m_str)
        # pb = PathBuilder(pattern=pattern_str, program=p_str, mutation=m_str)

        # sf = SimpleFormatter(mutation,
        #                      program,
        #                      new_var_map,
        #                      new_array_sizes)

        # wrapper = pb.wrapper_path()
        # sf.write_kernel_wrapper(f'{output_dir}/{wrapper}')
        # core = pb.core_path()
        # sf.write_core(f'{output_dir}/{core}')
        m += 1
    # return (p_str, mutations)

for p in range(n_programs):
    generate_batch(p)
pool = Pool()

pool.map(generate_batch, range(n_programs))

codegen.generate_pattern_file()

# programs = pool.map(generate_batch, range(n_programs))
# patterns = [(pattern_str, programs)]

# # Print out the patterns for the build script to work
# # once this is serializable, then we will be able to iterate through mutations
# from pprint import PrettyPrinter
# with open(f'{output_dir}/patterns.py', 'w') as f:
#     f.write('patterns = ')
#     PrettyPrinter(indent=2, stream=f).pprint(patterns)
