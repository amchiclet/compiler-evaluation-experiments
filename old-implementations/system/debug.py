import os.path
from loguru import logger
from parser import parse_file
from loop_analyzer import analyze_loops
from dependence import analyze_dependence, is_valid, get_statement_relations
from interchange import Interchange
from simple_formatter_v2 import SimpleFormatter
import sys

def init_logging():
    logger.remove()
    script_name_py = os.path.basename(__file__)
    script_name = script_name_py[:script_name_py.find('.')]
    log_name = script_name + '.log'
    logger.add(sys.stdout,
               colorize=True,
               format='<green>[{elapsed} {file}:{line}]</green> <level>{message}</level>',
               level='INFO')
    logger.add(log_name,
               format='[{time:YYYY-MM-DD HH:MM:ss.SSSSS} {level} {file}:{line}]\n{message}',
               level='DEBUG',
               retention=0)

init_logging()
program, node_id = parse_file('v3.loop')
# print(program.pprint())

# loop = program.loops[0]
n_max_loop_analysis = 1
mutations = []
found_mutation = False
for _ in range(n_max_loop_analysis):
    loop_analysis = analyze_loops(program)
    loop = program.loops[0]
    loop_id = loop.node_id
    loop_var_analysis = loop_analysis[loop_id].loop_var_analysis
    array_analysis = loop_analysis[loop_id].array_analysis
    groups = loop_analysis[loop_id].groups
    logger.info(f'Loop range analysis')
    for i, group in enumerate(groups):
        logger.info(f'Group {i+1}:\n' + group.pprint())
    logger.info('\n' + array_analysis.pprint())

    logger.info('\n' + loop_var_analysis.pprint())
    dep = analyze_dependence(program, loop_analysis)
    relations = get_statement_relations(program)
    logger.info('\n' + loop.pprint())
    logger.info('\n' + dep.pprint(relations.statement_map))
    # interchange = Interchange()
    # n_max_mutations = 10
    # for m in range(n_max_mutations):
    #     mutation = interchange.mutate(program, loop_analysis)
    #     if not mutation:
    #         logger.info('No mutations!!!')
    #         break
    #     mutations.append((mutation, loop_analysis))
    #     logger.info(f'Mutation {len(mutations)}\n{mutation.pprint(1)}')
    # if len(mutations) > 0:
    #     break

# if len(mutations) > 0:
#     for (mutation, loop_analysis) in mutations:
#         for analysis in loop_analysis.values():
#             print(analysis.info())
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

# print(loop0_analysis.pprint())
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
