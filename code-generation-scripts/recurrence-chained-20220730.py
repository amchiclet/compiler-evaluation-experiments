from api import Skeleton, Mapping, CodegenConfig
from random import randint, seed
from codelet_generator import codelet_dir, generate_codelet_files, generate_batch_summary_flex, SourceInfoFlex
from pattern_ast import get_ordered_assignments, get_accesses, count_ops, simplify_0s_and_1s

skeleton_code = """
declare size;
declare n_arrs;

for [(i, >=#_:order#, <=(size-1)/n_arrs)] {
  $_$
  $_$
  $_$
  $_$
}
"""

# We want something with 4 statements
# Dependencies are chained:
#   A[i] = ... + B[...]
#   B[i] = ... + C[...]
#   C[i] = ... + D[...]
#   D[i] = D[...]
# Each statement will always have A[i] = A[i-order] present
# The rest of the coefficients are in {0, 1, 2}
def gen_program(order, chain_length, zeroes):
    stmts = [
        Mapping(
            '_',
            ['A[i] = #_:restA# + #_:next1#;',
             'B[i] = #_:restB# + #_:next2#;',
             'C[i] = #_:restC# + #_:next3#;',
             'D[i] = #_:restD#;',
            ],
            is_finite = True,
        )
    ]
    def create_recurrence(var, order):
        terms = [f'#_:coef#*{var}[i-{offset}]' for offset in range(1, order)]
        terms.append(f'{var}[i-{order}]')
        rec = ' + '.join(terms)
        return rec

    rest_exprs = [
        Mapping(f'rest{var}', [create_recurrence(var, order)])
        for var in ['A', 'B', 'C', 'D']
    ]

    if chain_length == 1:
        next_exprs = [
            Mapping('next1', ['0']),
            Mapping('next2', ['0']),
            Mapping('next3', ['0']),                      
        ]
    elif chain_length == 2:
        next_exprs = [
            Mapping('next1', [create_recurrence('B', order)]),
            Mapping('next2', ['0']),
            Mapping('next3', ['0']),                      
        ]
    elif chain_length == 3:
        next_exprs = [
            Mapping('next1', [create_recurrence('B', order)]),
            Mapping('next2', [create_recurrence('C', order)]),
            Mapping('next3', ['0']),                      
        ]
    elif chain_length == 4:
        next_exprs = [
            Mapping('next1', [create_recurrence('B', order)]),
            Mapping('next2', [create_recurrence('C', order)]),
            Mapping('next3', [create_recurrence('D', order)]),
        ]
    else:
        print(f'Unsupported chain_length: {chain_length}')
        exit(1)

    zero_coef_exprs = [Mapping('coef', ['0']*zeroes, is_finite=True)]
    rest_coef_exprs = [Mapping('coef', ['1', '2'])]
    order_expr = [Mapping('order', [f'{order}'])]
        
    program = Skeleton(skeleton_code)
    program = program.fill_statements(stmts)
    program = program.fill_expressions(order_expr)
    program = program.fill_expressions(rest_exprs)
    program = program.fill_expressions(next_exprs)
    program = program.fill_expressions(zero_coef_exprs)
    program = program.fill_expressions(rest_coef_exprs)
    return program

seed(0)
application = 'LoopGen'
batch = 'recurrence-chained-20220730'

source_info_header = [
    'name',
    '# statements',
    'order',
    'chain length',
    '# arrays',
    '# rhs array refs',
    '# rhs uniq array refs',
    '# rhs ops (excluding indices)',
    'fullness',
]

programs = set()
source_infos = []
n_arrs = 4
for order in range(1, 4):
    for chain_length in range(1, 5):
        n_terms = (4+chain_length-1)*order
        n_possibly_zero_coeffs = n_terms - 4 - (chain_length-1)
        for zeroes in range(n_possibly_zero_coeffs+1):
            print(n_terms, n_possibly_zero_coeffs, order, chain_length, zeroes)
            skeleton = gen_program(order, chain_length, zeroes)
            simplify_0s_and_1s(skeleton.program)

            n_atoms = n_terms-zeroes
            code = f'4_stmts_recurrence_{order}_order_{chain_length}_chain_length_{n_atoms:02d}_atoms'
            codelet = f'{code}_de'

            config = CodegenConfig()
            config.possible_values = {
                **{f'{var}[]': 8388608 for var in ['A', 'B', 'C', 'D']},
                'size': 8388608,
                'n_arrs': n_arrs,
            }
            config.types = {
                **{ f'{var}': 'double' for var in ['A', 'B', 'C', 'D'] },
            }
            config.initial_values = {
                **{ f'{var}' : 'drand(0.0, 1.0)' for var in ['A', 'B', 'C', 'D'] },
                'size': 'inputs[0]',
                'n_arrs': 'inputs[1]',
            }
            config.template_dir = 'codelet-template-int-inputs'
            config.output_dir = generate_codelet_files(application, batch, code, codelet, 10, [32000, n_arrs])
            config.array_as_ptr = True
            skeleton.generate_code(config)

            print(code)
            print(skeleton)
            print('-----------------------')

            # Gather source information
            si = SourceInfoFlex(source_info_header)
            si['name'] = code
            si['# statements'] = 4
            si['order'] = order
            si['# arrays'] = 4
            si['chain length'] = chain_length
            si['# rhs array refs'] = n_atoms

            array_refs = []
            n_ops = 0
            for assignment in get_ordered_assignments(skeleton.program):
                n_ops += count_ops(assignment.rhs, ignore_indices=True)
                for access in get_accesses(assignment.rhs, ignore_indices=True):
                    if not access.is_scalar():
                        array_refs.append(str(access))
            assert(len(array_refs) == n_atoms)
            si['# rhs uniq array refs'] = len(set(array_refs))
            si['# rhs ops (excluding indices)'] = n_ops
            fullness = n_atoms / 4
            si['fullness'] = f'{fullness:.2f}'
            source_infos.append(si)
            print(si.header())
            print(si.columns())

generate_batch_summary_flex(application, batch, source_infos, source_info_header)
