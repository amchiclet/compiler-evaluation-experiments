from api import Skeleton, Mapping, CodegenConfig
from random import randint, seed
from codelet_generator import codelet_dir, generate_codelet_files, generate_batch_summary, SourceInfo
from pattern_ast import get_ordered_assignments, get_accesses

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
            ['scalar1 = scalar1 + scalar2 + #_# + #_# + #_# + #_#;',
             'scalar2 = scalar2 + scalar1 + #_# + #_# + #_# + #_#;',
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
batch = 'reduction-dbl-cycle'

programs = set()
source_infos = []
for n_arrs in range(1, 21):
    skeleton = gen_program(n_arrs)
    code = f'5_stmts_{n_arrs:02d}_arrs_dbl_cycle_dep'
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
    skeleton.generate_code(config)

    # Gather source information
    si = SourceInfo()
    si.name = code
    si.n_stmts = 5
    uniq_arrays = set()
    for assignment in get_ordered_assignments(skeleton.program):
        n_scalars = 0
        n_arrays = 0
        for access in get_accesses(assignment, ignore_indices=True):
            if access.is_scalar():
                n_scalars += 1
            else:
                n_arrays += 1
                uniq_arrays.add(str(access.var))
        si.scalars.append(n_scalars - 1)
        si.arrays.append(n_arrays)
        si.ops.append(5)
    si.extra_columns.append('double')
    si.extra_columns.append(5) # num scalars
    si.extra_columns.append(len(uniq_arrays)) # num arrays
    si.extra_columns.append(2) # additional deps
    si.extra_columns.append(2) # max dep cycle size
    source_infos.append(si)

generate_batch_summary(application, batch, source_infos, ['scalar type', '# scalars', '# arrays', '# additional deps', 'max dep cycle size'])
