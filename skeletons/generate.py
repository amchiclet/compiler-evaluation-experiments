from api import Skeleton, Mapping, CodegenConfig
from random import randint, seed, uniform, choices
from codelet_generator import codelet_dir, generate_codelet_files, generate_batch_summary_flex, SourceInfoFlex
from pattern_ast import get_ordered_assignments, get_accesses, count_ops, simplify_0s_and_1s
from itertools import product

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

# TODO: parameters should include
# 1) number of arrays
# 2) number of ALU instructions
# 3) number of statements
# 4) % vector instruction type
# 5) indexing type: stride=1, regular, indirect
# 6) cycles: self, cross-statement
# 7) datasize
def gen_program(n_stmts, n_arrs, n_ops, n_lc_deps, n_li_deps, n_ro):
    print('---- Skeleton ----')
    skeleton = Skeleton(skeleton_code)
    n_empty_stmts = max_stmts - n_stmts
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
    print('---- Fill statements ----')
    skeleton = fill_statements(n_ops_dist, skeleton)
    print(skeleton)
    print()

    # fill arrays
    arrs = [f'Arr{i:02d}' for i in range(n_arrs)]

    # LHS
    print('---- Fill LHS ----')

    lhs_arrs = arrs[:n_stmts]
    skeleton = fill_lhs(lhs_arrs, skeleton)
    print(skeleton)
    print()

    n_exprs = sum([n_ops+1 for n_ops in n_ops_dist])
    assert(n_exprs >= n_lc_deps + n_lc_deps + n_ro)

    rhs_pool = []

    # loop carried dependencies with index [i-1]
    candidates = choices(lhs_arrs, k=n_lc_deps)
    rhs_pool += [f'{arr}[i-1]' for arr in candidates]

    # loop independent dependencies with index [i]
    candidates = choices(lhs_arrs, k=n_li_deps)
    rhs_pool += [f'{arr}[i]' for arr in candidates]

    # Read-only arrays (not part of the dependency)
    ro_arrs = arrs[:n_stmts]
    candidates = ro_arrs + choices(ro_arrs, k=n_ro-len(ro_arrs))
    rhs_pool += [f'{arr}[i]' for arr in candidates]

    # fill literals
    n_remaining_exprs = n_exprs - n_lc_deps - n_li_deps - n_ro
    rhs_pool += [f'{0.99-0.01*i}' for i in range(n_remaining_exprs)]

    def partial_match(node_family, mapping_family):
        return mapping_family in node_family

    print('---- Fill RHS ----')
    skeleton = skeleton.fill_expressions(
        [ Mapping('rhs', rhs_pool, is_finite=True), ],
        matching_function=partial_match
    )
    print(skeleton)
    print()

    # fill operations
    print('---- Fill operations ----')
    skeleton = skeleton.fill_operations([Mapping('_', ['*', '+'])])
    print(skeleton)

    print(f'# of statements       = {n_stmts}\n'
          f'# of arrays           = {n_arrs}\n'
          f'# of ops              = {n_ops}\n'
          f'loop-carried deps     = {n_lc_deps}\n'
          f'loop-independent deps = {n_li_deps}\n'
          f'read-only accesses    = {n_ro}\n'
    )

    return skeleton

# Here's an example
n_stmts = 3
n_arrs = 5
n_ops = 8
n_lc_deps = 3
n_li_deps = 3
n_ro = 3
skeleton = gen_program(n_stmts, n_arrs, n_ops, n_lc_deps, n_li_deps, n_ro)