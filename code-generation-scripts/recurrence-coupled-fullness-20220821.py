from api import Skeleton, Mapping, CodegenConfig
from random import randint, seed
from codelet_generator import codelet_dir, generate_codelet_files, generate_batch_summary_flex, SourceInfoFlex
from pattern_ast import get_ordered_assignments, get_accesses, count_ops, simplify_0s_and_1s
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
    # length = 2, max_zeroes = 13
    [
        'A[i] = A[i-#_:order#] + B[i-#_:order#] + #_:coef#*#_:restA# + #_:coef#*#_:restA# + #_:coef#*#_:restA# + #_:coef#*#_:restA#;',
        'B[i] = B[i-#_:order#] + A[i-#_:order#] + #_:coef#*#_:restB# + #_:coef#*#_:restB# + #_:coef#*#_:restB# + #_:coef#*#_:restB#;',
        'C[i] = C[i-#_:order#] + #_:coef#*#_:restC# + #_:coef#*#_:restC# + #_:coef#*#_:restC# + #_:coef#*#_:restC# + #_:coef#*#_:restC#;',
    ],
    # length = 3, max_zeroes = 12
    [
        'A[i] = A[i-#_:order#] + B[i-#_:order#] + #_:coef#*#_:restA# + #_:coef#*#_:restA# + #_:coef#*#_:restA# + #_:coef#*#_:restA#;',
        'B[i] = B[i-#_:order#] + C[i-#_:order#] + #_:coef#*#_:restB# + #_:coef#*#_:restB# + #_:coef#*#_:restB# + #_:coef#*#_:restB#;',
        'C[i] = C[i-#_:order#] + A[i-#_:order#] + #_:coef#*#_:restC# + #_:coef#*#_:restC# + #_:coef#*#_:restC# + #_:coef#*#_:restC#;',
    ],
]

max_zeroes = [15, 13, 12]

rest_array_maps = [
    # length = 1
    { 'A': ['A'],
      'B': ['B'],
      'C': ['C'],
    },
    # length = 2
    { 'A': ['A', 'B'],
      'B': ['B', 'A'],
      'C': ['C'],
    },
    # length = 3
    { 'A': ['A', 'B'],
      'B': ['B', 'C'],
      'C': ['C', 'A'],
    },
]

def get_statements(coupling):
    return stmt_lists[coupling-1]


def get_rest(order, coupling, which):
    rest_arrays = rest_array_maps[coupling-1][which]
    return [ f'{array}[i-{order}]'
             for array, order in product(rest_arrays, range(1, order+1))]

def get_coeffs(coupling, n_zeroes):
    n_ones = max_zeroes[coupling-1]-n_zeroes
    return ['0']*n_zeroes + ['1']*n_ones

def gen_program(order, coupling, n_zeroes):
    stmts = [
        Mapping(
            '_',
            get_statements(coupling),
            is_finite = True,
        )
    ]

    offset = [
        Mapping('order', [str(order)])
    ]

    zeroes = [
        Mapping('coef', get_coeffs(coupling, n_zeroes), is_finite=True)
    ]

    rest = [
        Mapping('restA', get_rest(order, coupling, 'A')),
        Mapping('restB', get_rest(order, coupling, 'B')),
        Mapping('restC', get_rest(order, coupling, 'C')),
    ]
        
    program = Skeleton(skeleton_code)
    program = program.fill_statements(stmts)
    program = program.fill_expressions(offset)
    program = program.fill_expressions(zeroes)
    program = program.fill_expressions(rest)
    return program

seed(0)
application = 'LoopGen'
batch = 'recurrence-coupled-fullness-20220821'

source_info_header = [
    'name',
    '# statements',
    'order',
    'coupling',
    'fullness',
    '# arrays',
    '# rhs array refs',
    '# rhs uniq array refs',
    '# rhs ops (excluding indices)',
]

programs = set()
source_infos = []
n_stmts = 3
n_arrs = n_stmts
for order in range(1, 4):
    for coupling in range(1, 4):
        n_blanks = max_zeroes[coupling-1]
        for n_zeroes in range(n_blanks, -1, -1):
            for v in range(1):
                print(f'order({order}) coupling({coupling}), n_zeroes({n_zeroes})')
                n_terms = n_stmts * 6
                n_atoms = n_terms - n_zeroes
                skeleton = gen_program(order, coupling, n_zeroes)

                code = f'3_stmts_recurrence_{coupling}_coupling_{order}_order_{n_atoms:02d}_atoms'
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
                simplify_0s_and_1s(skeleton.program)
                skeleton.generate_code(config)

                print(skeleton)

                # Gather source information
                si = SourceInfoFlex(source_info_header)
                si['name'] = code
                si['# statements'] = 3
                si['# arrays'] = 3
                si['order'] = order
                si['coupling'] = coupling

                array_refs = []
                n_ops = 0
                for assignment in get_ordered_assignments(skeleton.program):
                    n_ops += count_ops(assignment.rhs, ignore_indices=True)
                    for access in get_accesses(assignment.rhs, ignore_indices=True):
                        if not access.is_scalar():
                            array_refs.append(str(access))
                assert(len(array_refs) == n_atoms)
                si['# rhs array refs'] = n_atoms
                si['# rhs uniq array refs'] = len(set(array_refs))
                si['# rhs ops (excluding indices)'] = n_ops
                fullness = n_atoms/n_stmts
                si['fullness'] = f'{fullness:.2f}'
                source_infos.append(si)
                print(si.header())
                print(si.columns())

generate_batch_summary_flex(application, batch, source_infos, source_info_header)
