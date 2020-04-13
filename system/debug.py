from parser import parse_file
from loop_analyzer import analyze_loops
from dependence import analyze_dependence, is_valid
from interchange import Interchange
from simple_formatter_v2 import SimpleFormatter

program, node_id = parse_file('v2.loop')
print(program.pprint())

# loop = program.loops[0]
n_max_loop_analysis = 1
mutations = []
found_mutation = False
for _ in range(n_max_loop_analysis):
    loop_analysis = analyze_loops(program)
    # dep = analyze_dependence(program, loop_analysis)
    interchange = Interchange()
    n_max_mutations = 10
    for m in range(n_max_mutations):
        mutation = interchange.mutate(program, loop_analysis)
        if not mutation:
            print('No mutations!!!')
            break
        mutations.append((mutation, loop_analysis))
        print(f'Mutation {len(mutations)}\n{mutation.pprint(1)}')
    if len(mutations) > 0:
        break

# if len(mutations) > 0:
#     for (mutation, loop_analysis) in mutations:
#         for analysis in loop_analysis.values():
#             print(analysis.debug())
#             formatter = SimpleFormatter(program, mutation, loop_analysis)
#             print(formatter.declare_globals())
#             print(formatter.init())
#             print(formatter.kernel())
#             print(formatter.check())
#             print(formatter.checksum())
#             print(formatter.run())
#             print(formatter.main())
#             break

# loop_analysis = {}
# loop_analysis[program.loops[0].node_id] = loop0_analysis

# print(loop0_analysis.debug())
# dep_graph_before = analyze_dependence(program, loop_analysis)

# cloned_program = program.clone()
# print('after')
# cloned_program.loops[0].loop_vars.reverse()
# cloned_program.loops[0].analysis = loop_analysis
# print(cloned_program.pprint())
# dep_graph_after = analyze_dependence(cloned_program, loop_analysis)
# if is_valid(dep_graph_before, dep_graph_after):
#     print('valid transformation!')
# else:
#     print('invalid transformation!')
# # now that we have loop analysis, we need to be able to use this to build the dependency graph
