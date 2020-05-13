from parser import parse_file
from loguru import logger
from transformers.loop_interchange import LoopInterchange
from variable_map import VariableMap, restrict_var_map

program, _ = parse_file('valid-interchange.loop')
print(program.pprint())

loop = program.loops[0]
    
var_map = VariableMap()
var_map.set_min('h', 5)
var_map.set_max('h', 50)
var_map.set_min('w', 3)
var_map.set_max('w', 33)
var_map.set_min('c', 2)
var_map.set_max('c', 22)
var_map.set_max('x', 200)

restrict_var_map(program, var_map)

def iterate_mutations(program):
    loop_interchange = LoopInterchange()
    for mutation in loop_interchange.transform(program, var_map):
        yield mutation

for mutation in iterate_mutations(program):
    print('printing mutation')
    print(mutation.pprint())
