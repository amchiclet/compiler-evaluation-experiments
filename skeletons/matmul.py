from api import Skeleton, Mapping, CodegenConfig
from random import randint, seed, uniform, choices
from codelet_generator import codelet_dir, generate_codelet_files, generate_batch_summary_flex, SourceInfoFlex
from pattern_ast import get_ordered_assignments, get_accesses, count_ops, simplify_0s_and_1s
from itertools import product
from loguru import logger

skeleton_code = """
declare M;
declare N;
declare K;

declare A[M][K];
declare DD[M][K];

declare B[K][N];
declare EE[K][N];

declare C[M][N];

local sum;
for [(i, >=0, <=M-1), (j, >=0, <=N-1)] {
  sum = 0;
  for [(k, >=0, <=K-1)] {
    sum = sum + #_:A# * #_:B#;
  }
  C[i][j] = C[i][j]+sum;
}
"""

class CodeGenerationParameters:
    def __init__(self, n_arrs):
        self.n_stmts = 1
        # 3-5 arrays
        # C = C + (A) * (B)
        # up to
        # C = C + (A_D) * (B_E)
        self.n_arrs = n_arrs

        # since there's only 1 statement, this should simply be n_arrs-1
        self.n_ops = n_arrs-1

        # from C to C across k loops
        self.n_lc_deps = 1

        # from C to C in the same loop
        self.n_li_deps = 1

        # Every array besides C is read-only
        self.n_ro = n_arrs-1

    def __str__(self):
        return (f'# of statements       = {self.n_stmts}\n'
                f'# of arrays           = {self.n_arrs}\n'
                f'# of ops              = {self.n_ops}\n'
                f'loop-carried deps     = {self.n_lc_deps}\n'
                f'loop-independent deps = {self.n_li_deps}\n'
                f'read-only accesses    = {self.n_ro}\n'
        )
    def extract(self):
        return (self.n_stmts,
                self.n_arrs,
                self.n_ops,
                self.n_lc_deps,
                self.n_li_deps,
                self.n_ro
        )

def randomly_create_code_generation_parameters():
    logger.debug('randomly create code generation parameters!')
    n_arrs = randint(3, 5)
    params = CodeGenerationParameters(n_arrs)
    return params

def gen_program(parameters):
    n_stmts, n_arrs, n_ops, n_lc_deps, n_li_deps, n_ro = parameters.extract()
    logger.debug(parameters)

    logger.debug('---- Skeleton ----')
    skeleton = Skeleton(skeleton_code)

    # fill arrays

    # LHS

    n_exprs = n_ops+1

    a_pool = ['A[i][k]+#_:D#', 'A[i][k]*#_:D#']
    b_pool = ['B[k][j]+#_:E#', 'B[k][j]*#_:E#']
    d_pool = ['d', 'DD[i][k]'] # do we want to randomize the access patterns and array dimensions too?
    e_pool = ['e', 'EE[k][j]']

    logger.debug('---- Fill RHS ----')
    skeleton = skeleton.fill_expressions(
        [ Mapping('A', a_pool),
          Mapping('B', b_pool)
        ],
    )
    logger.debug(skeleton)

    logger.debug('---- Fill RHS ----')
    skeleton = skeleton.fill_expressions(
        [ Mapping('D', d_pool),
          Mapping('E', e_pool)
        ],
    )
    logger.debug(skeleton)

    # print debug string

    config = CodegenConfig()
    arrs = ['A', 'B', 'C', 'DD', 'EE', 'd', 'e', 'sum']
    config.possible_values = {
        # **{f'{var}[]': 1000 for var in arrs },
        # **{f'{var}[][]': 1000 for var in arrs },
        'M': 1000,
        'N': 1000,
        'K': 1000,
    }
    config.types = {
        **{ f'{var}': 'double' for var in arrs },
    }
    config.initial_values = {
        **{ f'{var}' : 'drand(0.0, 1.0)' for var in arrs if var != 'sum' },
        'sum': '0.0',
        'M': 'inputs[0]',
        'N': 'inputs[1]',
        'K': 'inputs[2]',
    }
    config.array_as_ptr = True

    logger.debug(skeleton)

    # Gather source information
    si = SourceInfoFlex(source_info_header)
    si['# statements'] = n_stmts
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
    fullness = n_exprs/n_stmts
    si['fullness'] = f'{fullness:.2f}'
    si['# loop-carried deps'] = n_lc_deps
    si['# loop-independent deps'] = n_li_deps
    si['# read-only references'] = n_ro

    # for this codelet, the default M, N, K is 100
    # n_arrs will be whatever was given
    default_inputs = [100, 100, 100]

    return skeleton, si, config, default_inputs

source_info_header = [
    'name',
    'batch',
    'codelet name',
    'generate function',
    'si name',
    '# statements',
    '# arrays',
    '# rhs array refs',
    '# rhs uniq array refs',
    '# rhs ops (excluding indices)',
    'fullness',
    '# loop-carried deps',
    '# loop-independent deps',
    '# read-only references',
]

