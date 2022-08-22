from api import Skeleton, Mapping, CodegenConfig
from random import randint, seed
from codelet_generator import codelet_dir, generate_codelet_files, generate_batch_summary, SourceInfo
from pattern_ast import get_ordered_assignments, get_accesses, count_ops
from itertools import product

skeleton_code = """
declare size;
declare n_arrs;

for [(i, >=#_:order#, <=(size-1)/n_arrs)] {
  $_$
  $_$
  $_$
}
"""

stmt_lists = [
    # length = 1, max_zeroes = 15
    [
        'A[i] = A[i-#_:order#] + #_:coef#*#_:restA# + #_:coef#*#_:restA# + #_:coef#*#_:restA# + #_:coef#*#_:restA# + #_:coef#*#_:restA#;',
        'B[i] = B[i-#_:order#] + #_:coef#*#_:restB# + #_:coef#*#_:restB# + #_:coef#*#_:restB# + #_:coef#*#_:restB# + #_:coef#*#_:restB#;',
        'C[i] = C[i-#_:order#] + #_:coef#*#_:restC# + #_:coef#*#_:restC# + #_:coef#*#_:restC# + #_:coef#*#_:restC# + #_:coef#*#_:restC#;',
    ],
    # length = 2, max_zeroes = 14
    [
        'A[i] = A[i-#_:order#] + B[i-#_:order#] + #_:coef#*#_:restA# + #_:coef#*#_:restA# + #_:coef#*#_:restA# + #_:coef#*#_:restA#;',
        'B[i] = B[i-#_:order#] + #_:coef#*#_:restB# + #_:coef#*#_:restB# + #_:coef#*#_:restB# + #_:coef#*#_:restB# + #_:coef#*#_:restB#;',
        'C[i] = C[i-#_:order#] + #_:coef#*#_:restC# + #_:coef#*#_:restC# + #_:coef#*#_:restC# + #_:coef#*#_:restC# + #_:coef#*#_:restC#;',
    ],
    # length = 3, max_zeroes = 13
    [
        'A[i] = A[i-#_:order#] + B[i-#_:order#] + #_:coef#*#_:restA# + #_:coef#*#_:restA# + #_:coef#*#_:restA# + #_:coef#*#_:restA#;',
        'B[i] = B[i-#_:order#] + C[i-#_:order#] + #_:coef#*#_:restB# + #_:coef#*#_:restB# + #_:coef#*#_:restB# + #_:coef#*#_:restB#;',
        'C[i] = C[i-#_:order#] + #_:coef#*#_:restC# + #_:coef#*#_:restC# + #_:coef#*#_:restC# + #_:coef#*#_:restC# + #_:coef#*#_:restC#;',
    ],
]

max_zeroes = [15, 14, 13]

rest_array_maps = [
    # length = 1
    { 'A': ['A'],
      'B': ['B'],
      'C': ['C'],
    },
    # length = 2
    { 'A': ['A', 'B'],
      'B': ['B'],
      'C': ['C'],
    },
    # length = 2
    { 'A': ['A', 'B'],
      'B': ['B', 'C'],
      'C': ['C'],
    },
]

def get_statements(chain_length):
    return stmt_lists[chain_length-1]


def get_rest(order, chain_length, which):
    rest_arrays = rest_array_maps[chain_length-1][which]
    return [ f'{array}[i-{order}]'
             for array, order in product(rest_arrays, range(1, order+1))]

def get_coeffs(chain_length, n_zeroes):
    n_ones = max_zeroes[chain_length-1]-n_zeroes
    return ['0']*n_zeroes + ['1']*n_ones

def gen_program(order, chain_length, n_zeroes):
    stmts = [
        Mapping(
            '_',
            get_statements(chain_length),
            is_finite = True,
        )
    ]

    offset = [
        Mapping('order', [str(order)])
    ]

    zeroes = [
        Mapping('coef', get_coeffs(chain_length, n_zeroes), is_finite=True)
    ]

    rest = [
        Mapping('restA', get_rest(order, chain_length, 'A')),
        Mapping('restB', get_rest(order, chain_length, 'B')),
        Mapping('restC', get_rest(order, chain_length, 'C')),
    ]
        
    program = Skeleton(skeleton_code)
    program = program.fill_statements(stmts)
    program = program.fill_expressions(offset)
    program = program.fill_expressions(zeroes)
    program = program.fill_expressions(rest)
    return program

seed(0)
application = 'LoopGen'
batch = 'recurrence-chained-fullness-20220821'

programs = set()
source_infos = []
n_stmts = 3
n_arrs = n_stmts
for order in range(1, 4):
    for chain_length in range(1, 4):
        n_blanks = max_zeroes[chain_length-1]
        for n_zeroes in range(n_blanks, -1, -1):
            for v in range(1):
                print(f'order({order}) chain_length({chain_length}), n_zeroes({n_zeroes})')
                n_terms = n_stmts * 6
                n_atoms = n_terms - n_zeroes
                skeleton = gen_program(order, chain_length, n_zeroes)

                code = f'3_stmts_recurrence_{chain_length}_chained_{order}_order_{n_atoms:02d}_atoms'
                codelet = f'{code}_de'

                config = CodegenConfig()
                config.possible_values = {
                    **{f'{var}[]': 8388608 for var in ['A', 'B', 'C']},
                    'size': 8388608,
                    'n_arrs': n_arrs,
                }
                config.types = {
                    **{ f'{var}': 'double' for var in ['A', 'B', 'C'] },
                }
                config.initial_values = {
                    **{ f'{var}' : 'drand(0.0, 1.0)' for var in ['A', 'B', 'C'] },
                    'size': 'inputs[0]',
                    'n_arrs': 'inputs[1]',
                }
                config.template_dir = 'codelet-template-int-inputs'
                config.output_dir = generate_codelet_files(application,
                                                           batch,
                                                           code,
                                                           codelet,
                                                           10,
                                                           [32000, n_arrs])
                config.array_as_ptr = True
                skeleton.generate_code(config)

                print(skeleton)
        
                # Gather source information
                si = SourceInfo()
                si.name = code
                si.n_stmts = n_arrs
                uniq_atoms = set()
                graph = {}
                for assignment in get_ordered_assignments(skeleton.program):
                    n_arrays = 0
                    n_scalars = 0

                    for access in get_accesses(assignment, ignore_indices=False):
                        if access.is_scalar():
                            n_scalars += 1
                        else:
                            n_arrays += 1

                    # extra RHS counting
                    lhs = assignment.lhs.var
                    for access in get_accesses(assignment.rhs, ignore_indices=True):
                        # count unique aroms
                        uniq_atoms.add(str(access))
            
                    si.scalars.append(n_scalars)
                    si.arrays.append(n_arrays)
                    si.ops.append(count_ops(assignment))

                fullness = n_atoms/n_stmts
                si.extra_columns.append('recurrence')
                si.extra_columns.append(3) # distinct arrays
                si.extra_columns.append(order)
                si.extra_columns.append(n_atoms) # number of atoms
                si.extra_columns.append(len(uniq_atoms)) # number of unique atoms
                si.extra_columns.append(chain_length)
                si.extra_columns.append(f'{fullness:.2f}')
                source_infos.append(si)

generate_batch_summary(application, batch, source_infos, ['computation', '# distinct arrays', 'order', '# atoms', '# uniq atoms', 'chain length', 'fullness'])
