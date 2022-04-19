from api import Skeleton, Mapping, CodegenConfig
from random import randint, seed
from codelet_generator import codelet_dir, generate_codelet_files, generate_batch_summary, SourceInfo
from pattern_ast import get_ordered_assignments, get_accesses

skeleton_code = """
declare size;
declare n_unique_arrs;

for [(i, >=0, <=(size-1)/n_unique_arrs)] {
  $_$
  $_$
  $_$
  $_$
  $_$
}
"""

def gen_program(n_stmts, n_arrs):
    stmts = [
        Mapping(
            '_',
            [f'scalar{i} = scalar{i} + #_# + #_# + #_# + #_# + #_#;' for i in range(1, n_stmts + 1)] +
            [';'] * (5 - n_stmts),
            is_finite = True,
        )
    ]
    exprs = [
        Mapping(
            '_',
            [f'Arr{i:02d}[i]' for i in range(1, n_arrs + 1)] +
            ['0'] * (5 * n_stmts - n_arrs),
            is_finite = True
        )
    ]
        
    program = Skeleton(skeleton_code)
    program = program.fill_statements(stmts)
    program = program.fill_expressions(exprs)
    return program

seed(0)
application = 'LoopGen'
batch = 'reduction-fix-dsize'

info = '''Each statement is s = s + _ + _ + _ + _ + _;
Each hole can be a unique array or 0
There can be up to 5 statements, each statement will have a unique scalar.
'''

programs = set()
source_infos = []
for n_stmts in range(1, 6):
    max_unique_arrs = n_stmts * 5
    n_unique_arrs_begin = max_unique_arrs - 5 + 1
    n_unique_arrs_end = max_unique_arrs + 1
    for n_unique_arrs in range(n_unique_arrs_begin, n_unique_arrs_end):
        skeleton = gen_program(n_stmts, n_unique_arrs)
        code = f'{n_stmts}_scalars_{n_unique_arrs:02d}_uniq_arrs'
        codelet = f'{code}_de'

        config = CodegenConfig()
        config.possible_values = {
            **{f'Arr{i:02d}[]': 8000000 for i in range(1, 26)},
            'size': 8000000,
            'n_unique_arrs': n_unique_arrs,
        }
        config.types = {
            **{ f'Arr{i:02d}': 'double' for i in range(1, 26) },
            **{ f'scalar{i}': 'double' for i in range(1, 6) },
        }
        config.initial_values = {
            **{ f'Arr{i:02d}' : 'drand(0.0, 1.0)' for i in range(1, 26) },
            'size': 'inputs[0]',
            'n_unique_arrs': 'inputs[1]',
        }
        config.template_dir = 'codelet-template-int-inputs'
        config.output_dir = generate_codelet_files(application, batch, code, codelet, 10, [32000, n_unique_arrs])
        config.array_as_ptr = True
        skeleton.generate_code(config)

        # Gather source information
        si = SourceInfo()
        si.name = code
        si.n_stmts = n_stmts
        for assignment in get_ordered_assignments(skeleton.program):
            n_arrays = 0
            for access in get_accesses(assignment, ignore_indices=True):
                if not access.is_scalar():
                    n_arrays += 1
            # All statement looks like: scalar = scalar x A[] x B[] x C[] ...
            # One unique scalar per statement. All arrays are unique.
            # And n_ops actually matches n_arrays
            si.scalars.append(1)
            si.arrays.append(n_arrays)
            si.ops.append(n_arrays)
        si.extra_columns.append('double')
        source_infos.append(si)

generate_batch_summary(application, batch, source_infos, ['scalar type'])
