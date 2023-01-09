from api import Skeleton, Mapping, CodegenConfig
from random import randint, seed
from codelet_generator import codelet_dir, generate_codelet_files, generate_batch_summary_flex, SourceInfoFlex
from pattern_ast import get_ordered_assignments, get_accesses, count_ops, simplify_0s_and_1s

skeleton_code = """
declare size;
declare n_arrs;

for [(i, >=0, <=(size-1)/n_arrs)] {
  $_$
  $_$
  $_$
  $_$
  $_$
}
"""

def gen_program(n_arrs):
    stmts = [
        Mapping(
            '_',
            ['scalar1 = scalar1 + #_# + #_# + #_# + #_# + #_#;',
             'scalar2 = scalar2 + #_# + #_# + #_# + #_# + #_#;',
             'scalar3 = scalar3 + #_# + #_# + #_# + #_# + #_#;',
             'scalar4 = scalar4 + #_# + #_# + #_# + #_# + #_#;',
             'scalar5 = scalar5 + #_# + #_# + #_# + #_# + #_#;',
            ],
            is_finite = True,
        )
    ]
    initial_exprs = [
        Mapping(
            '_',
            [f'Arr{i:02d}[i]' for i in range(1, n_arrs + 1)],
            is_finite=True
        )
    ]
    the_rest_exprs = [
        Mapping(
            '_',
            [f'Arr{i:02d}[i]' for i in range(1, n_arrs + 1)],
        )
    ]
    program = Skeleton(skeleton_code)
    program = program.fill_statements(stmts)
    program = program.fill_expressions(initial_exprs)
    program = program.fill_expressions(the_rest_exprs)
    return program

seed(0)
application = 'LoopGen'
batch = 'reduction-no-coupling-20220730'

source_info_header = [
    'name',
    '# statements',
    'fullness',
    '# arrays',
    '# rhs array refs',
    '# rhs uniq array refs',
    '# rhs ops (excluding indices)',
]

programs = set()
source_infos = []
for n_arrs in range(1, 26):
    skeleton = gen_program(n_arrs)
    code = f'5_stmts_{n_arrs:02d}_arrs_no_coupling'
    codelet = f'{code}_de'

    config = CodegenConfig()
    config.possible_values = {
        **{f'Arr{i:02d}[]': 8388608 for i in range(1, 26)},
        'size': 8388608,
        'n_arrs': n_arrs,
    }
    config.types = {
        **{ f'Arr{i:02d}': 'double' for i in range(1, 26) },
        **{ f'scalar{i}': 'double' for i in range(1, 6) },
    }
    config.initial_values = {
        **{ f'Arr{i:02d}' : 'drand(0.0, 1.0)' for i in range(1, 26) },
        'size': 'inputs[0]',
        'n_arrs': 'inputs[1]',
    }
    config.template_dir = 'codelet-template-int-inputs'
    config.output_dir = generate_codelet_files(application, batch, code, codelet, 10, [32000, n_arrs])
    config.array_as_ptr = True
    simplify_0s_and_1s(skeleton.program)
    skeleton.generate_code(config)

    # Gather source information
    si = SourceInfoFlex(source_info_header)
    si['name'] = code
    si['# statements'] = 5
    si['# arrays'] = n_arrs

    array_refs = []
    n_ops = 0
    for assignment in get_ordered_assignments(skeleton.program):
        n_ops += count_ops(assignment.rhs, ignore_indices=True)
        for access in get_accesses(assignment.rhs, ignore_indices=True):
            if not access.is_scalar():
                array_refs.append(str(access))
    n_atoms = len(array_refs)
    si['# rhs array refs'] = n_atoms
    si['# rhs uniq array refs'] = len(set(array_refs))
    si['# rhs ops (excluding indices)'] = n_ops
    fullness = n_atoms/5
    si['fullness'] = f'{fullness:.2f}'
    source_infos.append(si)
    print(si.header())
    print(si.columns())

generate_batch_summary_flex(application, batch, source_infos, source_info_header)
