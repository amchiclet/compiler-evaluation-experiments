import argparse
from parser import parse_file
from dependence import analyze_dependence, is_valid
from interchange import Interchange
from simple_gen import get_program_info, MAX_SIZE_PER_ARRAY
from concrete_ast import get_accesses

program, _ = parse_file('test.loop')
print(f'Original program:\n{program.pprint(1)}')


from simple_formatter import SimpleFormatter, SimpleConcretizer
# print(cloned.pprint())

formatter = SimpleFormatter(program, program)
print(formatter.declare_globals())
print(formatter.init())
print(formatter.run())
print(formatter.check())
# for var, mentioned_loop_vars in arrays.items():
#     print(array_decl(var))

# print(dimension_size ** depth_of_deepest_array, 'vs', MAX_SIZE_PER_ARRAY)
# for l in program.loops:
#     print(loop(l))
