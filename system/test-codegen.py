import argparse
from parser import parse_file
from dependence import analyze_dependence, is_valid
from interchange import Interchange
from simple_gen import get_program_info, MAX_SIZE_PER_ARRAY

program, _ = parse_file('test.loop')
print(f'Original program:\n{program.pprint(1)}')


arrays, loop_vars = get_program_info(program)

from simple_formatter import SimpleFormatter, SimpleConcretizer
concretizer = SimpleConcretizer()
cprogram = concretizer.concretize(program)
print(cprogram.pprint())
formatter = SimpleFormatter(arrays, loop_vars, MAX_SIZE_PER_ARRAY, program)
# print(formatter.declare())
# print(formatter.init())
# for var, mentioned_loop_vars in arrays.items():
#     print(array_decl(var))

# print(dimension_size ** depth_of_deepest_array, 'vs', MAX_SIZE_PER_ARRAY)
# for l in program.loops:
#     print(loop(l))
