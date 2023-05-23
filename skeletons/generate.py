from api import Skeleton, Mapping, CodegenConfig
from random import randint, seed, uniform, choices
from codelet_generator import codelet_dir, generate_codelet_files, generate_batch_summary_flex, SourceInfoFlex
from pattern_ast import get_ordered_assignments, get_accesses, count_ops, simplify_0s_and_1s
from itertools import product
from loguru import logger

skeleton_code = """
declare size;
declare n_arrs;

for [(i, >=1, <=(size-1)/n_arrs)] {
  $_$
  $_$
  $_$
  $_$
  $_$
  $_$
  $_$
  $_$
  $_$
  $_$
}
"""

max_stmts = 10
max_rhs_exprs = 5

def fill_empty_statements(n_empty_stmts, skeleton):
    empty_stmts = [Mapping('_', [';'] * n_empty_stmts, is_finite = True)]
    skeleton = skeleton.fill_statements(empty_stmts)
    return skeleton

def fill_statements(n_ops_dist, skeleton):
    stmts = []
    for i, n_ops in enumerate(n_ops_dist):
        lhs = f'#_:stmt{i}_lhs#'
        n_exprs = n_ops + 1
        rhs_exprs = [f'#_:stmt{i}_rhs#']*n_exprs
        rhs = '@_@'.join(rhs_exprs)
        stmts.append(f'{lhs} = {rhs};')
    mapping = [Mapping('_', stmts, is_finite = True)]
    return skeleton.fill_statements(mapping)

def fill_lhs(lhs_arrs, skeleton):
    exprs = []
    for i, lhs_arr in enumerate(lhs_arrs):
        exprs.append(Mapping(f'stmt{i}_lhs', [f'{lhs_arr}[i]']))
    return skeleton.fill_expressions(exprs)

class CodeGenerationParameters:
    def __init__(self, n_stmts, n_arrs, n_ops, n_lc_deps, n_li_deps, n_ro):
        self.n_stmts = n_stmts
        self.n_arrs = n_arrs
        self.n_ops = n_ops
        self.n_lc_deps = n_lc_deps
        self.n_li_deps = n_li_deps
        self.n_ro = n_ro
    def __str__(self):
        return (f'# of statements       = {n_stmts}\n'
                f'# of arrays           = {n_arrs}\n'
                f'# of ops              = {n_ops}\n'
                f'loop-carried deps     = {n_lc_deps}\n'
                f'loop-independent deps = {n_li_deps}\n'
                f'read-only accesses    = {n_ro}\n'
        )
    def extract(self):
        return (self.n_stmts,
                self.n_arrs,
                self.n_ops,
                self.n_lc_deps,
                self.n_li_deps,
                self.n_ro
        )
    def mutate(self, create_mutations):
        logger.debug('mutating')
        while True:
            mutations = create_mutations(['n_stmts', 'n_arrs', 'n_ops', 'n_lc_deps', 'n_li_deps', 'n_ro'])
            n_stmts = mutations['n_stmts'](self.n_stmts)
            n_arrs = mutations['n_arrs'](self.n_arrs)
            n_ops = mutations['n_ops'](self.n_ops)
            n_lc_deps = mutations['n_lc_deps'](self.n_lc_deps)
            n_li_deps = mutations['n_li_deps'](self.n_li_deps)
            n_ro = mutations['n_ro'](self.n_ro)

            if n_stmts < 3 or n_stmts > 5:
                continue
            if n_ops < n_stmts or n_ops > n_stmts * 5:
                continue
            if n_lc_deps < 0 or n_lc_deps > n_stmts:
                continue
            if n_li_deps < 0 or n_li_deps > n_stmts:
                continue
            if n_ro < 1 or n_ro > 5:
                continue
            if n_arrs < n_stmts+1 or n_arrs > n_stmts + n_ro:
                continue

            return CodeGenerationParameters(n_stmts, n_arrs, n_ops, n_lc_deps, n_li_deps, n_ro)

def randomly_create_code_generation_parameters():
    n_stmts = randint(3, 5)
    n_ops = randint(n_stmts, n_stmts*5)
    n_lc_deps = randint(0, n_stmts)
    n_li_deps = randint(0, n_stmts)
    n_ro = randint(1, 5)
    n_arrs = randint(n_stmts+1, n_stmts+n_ro)
    params = CodeGenerationParameters(n_stmts, n_arrs, n_ops, n_lc_deps, n_li_deps, n_ro)
    return params

# TODO: parameters should include
# 1) number of arrays
# 2) number of ALU instructions
# 3) number of statements
# 4) % vector instruction type
# 5) indexing type: stride=1, regular, indirect
# 6) cycles: self, cross-statement
# 7) datasize
def gen_program(parameters):
    n_stmts, n_arrs, n_ops, n_lc_deps, n_li_deps, n_ro = parameters.extract()
    logger.debug(f'n_stmts({n_stmts}) '
                 f'n_arrs({n_arrs}) '
                 f'n_ops({n_ops}) '
                 f'n_lc_deps({n_lc_deps}) '
                 f'n_li_deps({n_li_deps}) '
                 f'n_ro({n_ro})')
    logger.debug('---- Skeleton ----')
    skeleton = Skeleton(skeleton_code)
    n_empty_stmts = max_stmts - n_stmts
    if n_empty_stmts < 0:
        logger.debug("n_empty_stmts < 0")
        return None
    skeleton = fill_empty_statements(n_empty_stmts, skeleton)

    def distribute(iterator):
        dist = []
        for _ in range(n_stmts):
            dist.append([])
        for item in iterator:
            ith_stmt = randint(0, n_stmts-1)
            assign_to = ith_stmt
            dist[assign_to].append(item)
        return dist

    # distribute ops per statement
    n_ops_dist = [len(ops) for ops in distribute(range(n_ops))]
    logger.debug('---- Fill statements ----')
    skeleton = fill_statements(n_ops_dist, skeleton)
    logger.debug(skeleton)

    # fill arrays
    arrs = [f'Arr{i:02d}' for i in range(n_arrs)]

    # LHS
    logger.debug('---- Fill LHS ----')

    lhs_arrs = arrs[:n_stmts]
    skeleton = fill_lhs(lhs_arrs, skeleton)
    logger.debug(skeleton)

    n_exprs = sum([n_ops+1 for n_ops in n_ops_dist])
    if n_exprs < n_lc_deps + n_lc_deps + n_ro:
        logger.debug("n_exprs < n_lc_deps + n_lc_deps + n_ro:")
        return None

    rhs_pool = []

    # loop carried dependencies with index [i-1]
    candidates = choices(lhs_arrs, k=n_lc_deps)
    rhs_pool += [f'{arr}[i-1]' for arr in candidates]

    # loop independent dependencies with index [i]
    candidates = choices(lhs_arrs, k=n_li_deps)
    rhs_pool += [f'{arr}[i]' for arr in candidates]

    # Read-only arrays (not part of the dependency)
    ro_arrs = arrs[n_stmts:]
    candidates = ro_arrs + choices(ro_arrs, k=n_ro-len(ro_arrs))
    rhs_pool += [f'{arr}[i]' for arr in candidates]

    # fill literals
    n_remaining_exprs = n_exprs - n_lc_deps - n_li_deps - n_ro
    rhs_pool += [f'{0.99-0.01*i}' for i in range(n_remaining_exprs)]

    def partial_match(node_family, mapping_family):
        return mapping_family in node_family

    logger.debug('---- Fill RHS ----')
    skeleton = skeleton.fill_expressions(
        [ Mapping('rhs', rhs_pool, is_finite=True), ],
        matching_function=partial_match
    )
    logger.debug(skeleton)

    # fill operations
    logger.debug('---- Fill operations ----')
    skeleton = skeleton.fill_operations([Mapping('_', ['*', '+'])])
    logger.debug(skeleton)

    # print debug string

    config = CodegenConfig()
    config.possible_values = {
        **{f'{var}[]': 8388608 for var in arrs},
        'size': 8388608,
        'n_arrs': n_arrs,
    }
    config.types = {
        **{ f'{var}': 'double' for var in arrs },
    }
    config.initial_values = {
        **{ f'{var}' : 'drand(0.0, 1.0)' for var in arrs },
        'size': 'inputs[0]',
        'n_arrs': 'inputs[1]',
    }
    config.array_as_ptr = True

    logger.debug(skeleton)

    # Gather source information
    si = SourceInfoFlex(source_info_header)
    # si['batch'] = None
    # si['name'] = None
    # si['codelet name'] = None
    # si['generate function'] = None
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

    # for this codelet, the default size is 32000
    # n_arrs will be whatever was given
    default_inputs = [32000, n_arrs]

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

# Here's an example
# n_stmts = 3
# n_arrs = 5
# n_ops = 8
# n_lc_deps = 3
# n_li_deps = 3
# n_ro = 3
# skeleton, si, config, default_inputs = gen_program(n_stmts, n_arrs, n_ops, n_lc_deps, n_li_deps, n_ro)
# print(skeleton)
# print(si)
# print(config)
# print(default_inputs)
