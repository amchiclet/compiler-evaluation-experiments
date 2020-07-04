import argparse
from parser import parse_file
from dependence import analyze_dependence, is_valid
from interchange import Interchange

program, _ = parse_file('deeply-nested.loop')
print(f'Original program:\n{program.pprint(1)}')

interchange = Interchange(None)

n_max_mutations = 721
n_mutation = 0
for m in range(n_max_mutations):
    mutation = interchange.mutate(program)
    if not mutation:
        continue
    n_mutation += 1
    print(f'Mutation {n_mutation}\n{mutation.pprint(1)}')
