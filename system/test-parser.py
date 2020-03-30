from parser import parse_file
from loop_analyzer import analyze_loop

program, node_id = parse_file('v2.loop')
print(program.pprint())

loop = program.loops[0]
loop_analysis = analyze_loop(loop)
print(loop_analysis.debug())

#     print(f'Calculating for loop var {loop_var}')
#     min_val = 0
#     max_val = 2 ** 16

#     for array, dimensions in grouped_accesses.items():
#         for indices in dimensions:
#             if not indices:
#                 continue
#             if indices[0].var != loop_var:
#                 continue
#             shuffle(indices)
#             for lesser, greater in zip(indices[:-1], indices[1:]):
#                 # if they're equal then the ranges don't change
#                 if lesser.coeff == greater.coeff and lesser.offset == greater.offset:
#                     print(f'{lesser.pprint()} < {greater.pprint()}: {new_range}')
#                     continue
#                 new_range = find_possible_range([min_val, max_val], lesser, greater)
#                 print(f'{lesser.pprint()} < {greater.pprint()}: {new_range}')
#                 if not new_range:
#                     return false
                        
            

# # now let's sort them and see if they're possible to happen or not
