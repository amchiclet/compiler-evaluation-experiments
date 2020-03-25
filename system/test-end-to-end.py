import argparse
from parser import parse_file
from dependence import analyze_dependence, is_valid
from interchange import Interchange
from simple_gen import get_program_info, MAX_SIZE_PER_ARRAY
from concrete_ast import get_accesses

program, _ = parse_file('valid-interchange.loop')

DEBUG = False
if DEBUG:
    print(f'Original program:\n{program.pprint(1)}')

interchange = Interchange(None)
n_max_mutations = 1
n_mutation = 0
for m in range(n_max_mutations):
    mutation = interchange.mutate(program)
    if not mutation:
        continue
    n_mutation += 1
    if DEBUG:
        print(f'Mutation {n_mutation}\n{mutation.pprint(1)}')

assert(n_mutation > 0)

from simple_formatter import SimpleFormatter, SimpleConcretizer

formatter = SimpleFormatter(program, mutation)
print(formatter.declare_globals())
print(formatter.init())
print(formatter.kernel())
print(formatter.check())
print(formatter.checksum())
print(formatter.run())
print(formatter.main())
