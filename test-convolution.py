from parser import parse_file
from loguru import logger
from transformers.loop_interchange import LoopInterchange
from variable_map import VariableMap, restrict_var_map, calculate_array_sizes
from simple_formatter import SimpleFormatter

program, _ = parse_file('convolution.loop')
print(program.pprint())

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
    array_sizes = calculate_array_sizes(program.decls, restricted)

    yield (program, restricted, array_sizes)
    count += 1

    # print(var_map.pprint())
    # print(restricted.pprint())
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
output_dir = 'conv'
Path(output_dir).mkdir(parents=True, exist_ok=True)

generated_file_names = []
n_programs = 100
n_mutations = 12
for p in range(n_programs):
    m = 0
    for (mutation, restricted, array_sizes) in iterate_programs(program, var_map, n_mutations):
        file_name = f'convolution.p{p:04d}.m{m:04d}.c'
        generated_file_names.append(file_name)
        SimpleFormatter(program,
                        mutation,
                        restricted,
                        array_sizes).write_to_file(f'{output_dir}/{file_name}')
        m += 1

with open(f'{output_dir}/tests.py', 'w') as f:
    f.write('tests = [\n')
    for file_name in generated_file_names:
        f.write(f'    "{file_name}",\n')
    f.write(']\n')
