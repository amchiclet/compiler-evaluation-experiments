import argparse
from parser import parse_file
from dependence import analyze_dependence, is_valid

program, node_id = parse_file('valid-interchange.loop')
analyze_dependence(program)
cloned_program = program.clone()
print('before')
print(program.pprint())
dep_graph_before = analyze_dependence(program)
print('after')
cloned_program.loops[0].loop_vars.reverse()
print(cloned_program.pprint())
dep_graph_after = analyze_dependence(cloned_program)
is_valid(dep_graph_before, dep_graph_after)
