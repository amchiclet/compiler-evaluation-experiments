from api import Skeleton, Mapping, CodegenConfig
from random import randint, seed
from codelet_generator import codelet_dir, generate_codelet_files, generate_batch_summary, SourceInfo
from pattern_ast import get_ordered_assignments, get_accesses

skeleton_code = """
declare size;

for [(i, >=0, <=size-1)] {
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
            [f'scalar{i} = scalar{i} + #_:e1# + #_:e2# + #_:e3# + #_:e4# + #_:e5#;' for i in range(1, n_stmts + 1)] +
            [';'] * (5 - n_stmts),
            is_finite = True,
        )
    ]
    expr_map = {f'e{i}':[] for i in range(1, 6)}
    for i in range(n_stmts * 5):
        fam = f'e{(i//n_stmts)+1}'
        expr = f'Arr{i+1:02d}[i]' if i+1 <= n_arrs else '0'
        expr_map[fam].append(expr)

    exprs = [Mapping(fam, exprs, is_finite = True) for fam, exprs in expr_map.items()]
    program = Skeleton(skeleton_code)
    program = program.fill_statements(stmts)
    program = program.fill_expressions(exprs)
    return program

seed(0)
application = 'LoopGen'
batch = 'reduction-rs-fe-explore-dbl-scalars'

info = '''Codelet has either 3 or 4 statements
Each statement is s = s + _ + _ + _ + _ + _;
Each hole can be a unique array or 0
The arrays will be filled in a way that no statement can have more than 1 load that other statements.
'''

def gen10(sis, n_stmts=None):
    if n_stmts is None:
        return
    generated = set()
    max_unique_arrs = n_stmts * 5
    n = 0
    while n < 10:
        n_unique_arrs = randint(0, max_unique_arrs)
        if n_unique_arrs in generated:
            continue
        generated.add(n_unique_arrs)

        skeleton = gen_program(n_stmts, n_unique_arrs)
        code = f'{n_stmts}_scalars_{n_unique_arrs:02d}_uniq_arrs_dbl_scalars'
        codelet = f'{code}_de'

        config = CodegenConfig()
        config.possible_values = {
            **{f'Arr{i:02d}[]': 32000 for i in range(1, 26)},
            'size': 32000
        }
        config.types = {
            **{ f'Arr{i:02d}': 'double' for i in range(1, 26) },
            **{ f'scalar{i}': 'double' for i in range(1, 6) },
        }
        config.initial_values = {
            **{ f'Arr{i:02d}' : 'drand(0.0, 1.0)' for i in range(1, 26) },
            'size': '32000',
        }
        config.template_dir = 'codelet-template-int-inputs'
        config.output_dir = generate_codelet_files(application, batch, code, codelet, 10, [])
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

        n += 1

source_infos = []
gen10(source_infos, n_stmts = 3)
gen10(source_infos, n_stmts = 4)
generate_batch_summary(application, batch, source_infos, ['scalar type'])
