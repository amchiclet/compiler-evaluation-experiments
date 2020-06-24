from parser import parse_file
from loguru import logger
from transformers.loop_interchange import LoopInterchangeV2
from variable_map import VariableMap, restrict_var_map, calculate_array_sizes
from simple_formatter import SimpleFormatter
from multiprocessing import Pool
from build import PathBuilder

n_programs = 1
n_mutations = 72
output_dir = 'temp2'
logger.remove()
import sys
logger.add(sys.stdout, level='INFO')
logger.add(sink = 'multiple.log',
           level = 'INFO',
           format = ('{process.name} | '
                     '{time:YYYYMMDD_HH:mm:ss.SSS} | '
                     '{file}:{function}:{line} | '
                     '{message}'),
           enqueue = True)

program, _ = parse_file('multiple.loops')
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

from pathlib import Path
Path(output_dir).mkdir(parents=True, exist_ok=True)

def program_str(p):
    return f'p{p:04d}'

def mutation_str(m):
    return f'm{m:04d}'

def generate_batch(p):
    m = 0
    for (mutation, new_var_map, new_array_sizes) in iterate_programs(program, var_map, n_mutations):
        pattern_str = 'multiple'
        p_str = program_str(p)
        m_str = mutation_str(m)
        pb = PathBuilder(pattern=pattern_str, program=p_str, mutation=m_str)
        f = pb.source_code_path()
        print(f)
        # SimpleFormatter(mutation,
        #                 program,
        #                 new_var_map,
        #                 new_array_sizes).write_to_file(f'{output_dir}/{f}')
        m += 1

for p in range(n_programs):
    generate_batch(p)
# pool = Pool()
# pool.map(generate_batch, range(n_programs))

# # Print out the patterns for the build script to work
# # once this is serializable, then we will be able to iterate through mutations
# from pprint import PrettyPrinter
# with open(f'{output_dir}/patterns.py', 'w') as f:
#     f.write('patterns = ')
#     pp = PrettyPrinter(indent=2, stream=f)
#     patterns = []

#     pattern = 'convolution'
#     programs = []
#     for p in range(n_programs):
#         program = program_str(p)
#         mutations = [mutation_str(m) for m in range(n_mutations)]
#         programs.append((program, mutations))
#     patterns.append((pattern, programs))
#     pp.pprint(patterns)
