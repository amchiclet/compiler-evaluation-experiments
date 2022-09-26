from api import Skeleton, Mapping, CodegenConfig
from random import randint, seed
from codelet_generator import codelet_dir, generate_codelet_files, generate_batch_summary, SourceInfo
from pattern_ast import get_ordered_assignments, get_accesses, count_ops
from itertools import product

skeleton_code = """
declare size;
declare n_arrs;
declare M;
declare a[][];
declare b[][];
declare c[][];
declare d[][][];

for [
  (m, >=0, <=M-1),
  (n, >=0, <=#_:N#-1),
  (k, >=0, <=#_:K#-1)
] {
  c[m][n] = (c[m][n] + a[m][k] * b[k][n]) / d[m][n][k];
}
"""

def gen_program(n, k):
    nk = [
        Mapping('K', [str(k)]),
        Mapping('N', [str(n)]),
    ]
        
    program = Skeleton(skeleton_code)
    program = program.fill_expressions(nk)
    return program

seed(0)
application = 'LoopGen'
batch = 'matmul-hardcode-nk-20220925'

max_n = 100
max_k = 20
programs = set()
source_infos = []
for n in range(20, max_n+1, 20):
    for k in range(1, max_k+1):
        print(f'n({n}) k({k})')
        skeleton = gen_program(n, k)
        code = f'matmul_M_{n:03d}_{k:03d}'
        codelet = f'{code}_de'

        config = CodegenConfig()
        config.possible_values = {
            **{ f'{var}[]': 8000000 for var in ['a', 'b', 'c', 'd'] },
            'M': 10000,
            'size': 8000000,
            'n_arrs': 0,
        }
        config.types = {
            **{ f'{var}': 'double' for var in ['a', 'b', 'c', 'd'] },
        }
        config.initial_values = {
            **{ f'{var}' : 'drand(0.0, 1.0)' for var in ['a', 'b', 'c'] },
            'd': 'drand(0.5, 2.0)',
            'size': 'inputs[0]',
            'n_arrs': 'inputs[1]',

            # size = mn + mk + nk + mnk
            # size - nk = m(n+k) + mnk
            # size - nk = m(n+k+nk)
            # (size - nk) / (n+k+nk) = m
            # m = (size-nk)/(n+k+nk)
            'M': f'(inputs[0] - {n}*{k}) / ({n}+{k}+{n}*{k}) /* n={n}, k={k}*/',
        }
        config.template_dir = 'codelet-template-int-inputs'
        config.output_dir = generate_codelet_files(application,
                                                   batch,
                                                   code,
                                                   codelet,
                                                   10,
                                                   [32000, 0])
        config.array_as_ptr = True
        skeleton.generate_code(config)

        print(skeleton)

        # Gather source information
        si = SourceInfo()
        si.name = code
        si.n_stmts = 1
        si.scalars.append(9)
        si.arrays.append(4)
        si.ops.append(3)
        si.extra_columns.append(4) # num arrays
        si.extra_columns.append(n)
        si.extra_columns.append(k)
        source_infos.append(si)

generate_batch_summary(application, batch, source_infos, ['# arrays', 'N', 'K'])
