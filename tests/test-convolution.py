from parser import parse_file
from loguru import logger
from transformers.loop_interchange import LoopInterchange
from variable_map import VariableMap, restrict_var_map, calculate_array_sizes
from simple_formatter import SimpleFormatter
from multiprocessing import Pool
from build import PathBuilder

n_programs = 10
n_mutations = 72
output_dir = 'temp'

logger.add(sink = 'convolution.log',
           level = 'INFO',
           format = '{process.name} | {time:YYYYMMDD_HH:mm:ss.SSS} | {file}:{function}:{line} | {message}',
           enqueue = True
)
program, _ = parse_file('convolution.loop')
logger.info(program.pprint())

default_min = 0
default_max = 64
var_map = VariableMap(default_min, default_max)
var_map.set_max('H', 64)
var_map.set_max('W', 64)
var_map.set_max('C', 64)
var_map.set_max('HH', 16)
var_map.set_max('WW', 16)
var_map.set_max('CC', 16)

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
    def iterate_mutations():
        nonlocal count
        loop_interchange = LoopInterchange()
        loop_interchange.batch_size = n
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
        pattern_str = 'convolution'
        pb = PathBuilder(pattern=pattern_str, program=program_str(p), mutation=mutation_str(m))
        f = pb.source_code_path()
        SimpleFormatter(mutation,
                        program,
                        new_var_map,
                        new_array_sizes).write_to_file(f'{output_dir}/{f}')
        m += 1

pool = Pool()
pool.map(generate_batch, range(n_programs))

def list_mutations():
    return [mutation_str(m) for m in range(n_mutations)]
def list_programs():
    return [(program_str(p), list_mutations()) for p in range(n_programs)]

# once this is serializable, then we will be able to iterate through mutations
from pprint import PrettyPrinter
with open(f'{output_dir}/patterns.py', 'w') as f:
    f.write('patterns = ')
    pp = PrettyPrinter(indent=2, stream=f)
    patterns = []

    pattern = 'convolution'
    programs = []
    for p in range(n_programs):
        program = program_str(p)
        mutations = [mutation_str(m) for m in range(n_mutations)]
        programs.append((program, mutations))
    patterns.append((pattern, programs))
    pp.pprint(patterns)

    # f.write('tests = [\n')
    # for p in range(n_programs):
    #     for m in range(n_mutations):
    #         f.write(f'    "{filename("convolution", p, m)}",\n')
    # f.write(']\n')
