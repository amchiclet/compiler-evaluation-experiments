import argparse
from parser import parse_file
from dependence import analyze_dependence, is_valid
from interchange import Interchange

program, node_id = parse_file('invalid-interchange.loop')
dep_graph_before = analyze_dependence(program)
print('before')
print(program.pprint())

cloned_program = program.clone()
print('after')
cloned_program.loops[0].loop_vars.reverse()
print(cloned_program.pprint())
dep_graph_after = analyze_dependence(cloned_program)
if not is_valid(dep_graph_before, dep_graph_after):
    print('This is not a valid transformation')
