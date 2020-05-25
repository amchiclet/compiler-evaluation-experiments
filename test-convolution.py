from parser import parse_file
from loguru import logger
from transformers.loop_interchange import LoopInterchange
from variable_map import VariableMap, restrict_var_map, calculate_array_sizes
from simple_formatter import SimpleFormatter

program, _ = parse_file('convolution.loop')
print(program.pprint())

loop = program.loops[0]

default_min = 1
default_max = 100
var_map = VariableMap(default_min, default_max)
var_map.set_max('H', 50)
var_map.set_max('W', 50)
var_map.set_max('C', 50)
var_map.set_max('HH', 50)
var_map.set_max('WW', 50)
var_map.set_max('CC', 50)

restricted = restrict_var_map(program, var_map)
array_sizes = calculate_array_sizes(program.decls, restricted)
print(var_map.pprint())
print(restricted.pprint())
def iterate_mutations(program):
    loop_interchange = LoopInterchange()
    loop_interchange.batch_size = 20
    for mutation in loop_interchange.transform(program, restricted):
        yield mutation

generated_c_files = []
mutation_number = 0

from pathlib import Path
output_dir = 'output2'
Path(output_dir).mkdir(parents=True, exist_ok=True)
file_name = f'convolution.{mutation_number:04d}.c'
generated_c_files.append(file_name)
SimpleFormatter(program,
                program,
                restricted,
                array_sizes).write_to_file(f'{output_dir}/{file_name}')

for mutation in iterate_mutations(program):
    mutation_number += 1
    file_name = f'convolution.{mutation_number:04d}.c'
    generated_c_files.append(file_name)
    SimpleFormatter(mutation,
                    program,
                    restricted,
                    array_sizes).write_to_file(f'{output_dir}/{file_name}')

with open(f'{output_dir}/tests.py', 'w') as f:
    f.write('tests = [\n')
    for file_name in generated_c_files:
        f.write(f'    "{file_name}",\n')
    f.write(']\n')
