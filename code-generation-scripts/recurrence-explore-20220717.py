from api import Skeleton, Mapping, CodegenConfig
from random import randint, seed
from codelet_generator import codelet_dir, generate_codelet_files, generate_batch_summary, SourceInfo
from pattern_ast import get_ordered_assignments, get_accesses, count_ops

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

def gen_program(order, coupling):
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
        rec = ' + '.join([f'#_:coef#*{var}[i-{offset}]' for offset in range(1, order+1)])
        return rec

    rest_exprs = [
        Mapping(f'rest{var}', [create_recurrence(var, order)])
        for var in ['A', 'B', 'C', 'D']
    ]

    if coupling == 1:
        next_exprs = [
            Mapping('next1', ['0']),
            Mapping('next2', ['0']),
            Mapping('next3', ['0']),                      
        ]
    elif coupling == 2:
        next_exprs = [
            Mapping('next1', [create_recurrence('B', order)]),
            Mapping('next2', [create_recurrence('A', order)]),
            Mapping('next3', ['0']),                      
        ]
    elif coupling == 3:
        next_exprs = [
            Mapping('next1', [create_recurrence('B', order)]),
            Mapping('next2', [create_recurrence('C', order)]),
            Mapping('next3', [create_recurrence('A', order)]),
        ]
    else:
        print(f'Unsupported coupling: {coupling}')
        exit(1)

    coef_exprs = [Mapping('coef', ['0', '1', '2'])]
    order_expr = [Mapping('order', [f'{order}'])]
        
    program = Skeleton(skeleton_code)
    program = program.fill_statements(stmts)
    program = program.fill_expressions(order_expr)
    program = program.fill_expressions(rest_exprs)
    program = program.fill_expressions(next_exprs)
    program = program.fill_expressions(coef_exprs)
    return program

def calc_not_in_coupling(order):
    if order == 1:
        return 1
    return calc_in_coupling(order-1)

def calc_in_coupling(order):
    return 2*calc_not_in_coupling(order) + 1

def calc_ops(n_total_stmts, order, n_coupling_stmts):
    ops_in_coupling = n_coupling_stmts * calc_in_coupling(order)
    ops_not_in_coupling = (n_total_stmts-n_coupling_stmts) * calc_not_in_coupling(order)
    return ops_in_coupling + ops_not_in_coupling

seed(0)
application = 'LoopGen'
batch = 'recurrence-explore-20220717'

programs = set()
source_infos = []
n_arrs = 4
for order in range(1, 4):
    for coupling in range(1, 4):
        for version in range(1, 11):
            print(order, coupling, version)
            skeleton = gen_program(order, coupling)
            code = f'4_stmts_recurrence_{order}_order_{coupling}_coupling_v{version:02d}'
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
            # config.output_dir = generate_codelet_files(application, batch, code, codelet, 10, [32000, n_arrs])
            # config.array_as_ptr = True
            # skeleton.generate_code(config)

            # Gather source information
            si = SourceInfo()
            si.name = code
            si.n_stmts = 4
            uniq_arrays = set()
            for assignment in get_ordered_assignments(skeleton.program):
                n_scalars = 0
                n_arrays = 0
                for access in get_accesses(assignment, ignore_indices=False):
                    if access.is_scalar():
                        n_scalars += 1
                    else:
                        n_arrays += 1
                        uniq_arrays.add(str(access.var))
                si.scalars.append(n_scalars)
                si.arrays.append(n_arrays)
                si.ops.append(count_ops(assignment))
            si.extra_columns.append(len(uniq_arrays)) # num arrays
            # order==1
            # * op/stmt not in coupling = 1
            # * op/stmt in coupling = 2*one_line_above+1
            # order==2
            # * op/stmt not in coupling = one_line_above
            # * op/stmt in coupling = 2*one_line_above+1
            # order==3
            # * ... and so on ...
            si.extra_columns.append(calc_ops(n_arrs, order, coupling)) # total ops
            si.extra_columns.append(order)
            si.extra_columns.append(coupling)
            source_infos.append(si)

generate_batch_summary(application, batch, source_infos, ['# arrays', '# approx fp ops', 'order', 'coupling'])
