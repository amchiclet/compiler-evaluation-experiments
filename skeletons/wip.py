from api import Skeleton, Mapping, CodegenConfig
from random import randint, seed, uniform
from codelet_generator import codelet_dir, generate_codelet_files, generate_batch_summary_flex, SourceInfoFlex
from pattern_ast import get_ordered_assignments, get_accesses, count_ops, simplify_0s_and_1s
from itertools import product

skeleton_code = """
declare size;
declare n_arrs;

for [(i, >=#_:order#, <=(size-1)/n_arrs)] {
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

def lhs_arr(ith_stmt):
    return f'stmt_{ith_stmt}_lhs_arr'

def rhs_arr(ith_stmt):
    return f'stmt_{ith_stmt}_rhs_arr'

def rhs_coef(ith_stmt):
    return f'stmt_{ith_stmt}_coef'

def fill_empty_statements(n_empty_stmts, family_name, skeleton):
    empty_stmts = [Mapping(family_name, [';'] * n_empty_stmts, is_finite = True)]
    skeleton = skeleton.fill_statements(empty_stmts)
    return skeleton


def stmt_skeleton(n_rhs_exprs, ith_stmt):
    def term(ith_stmt):
        return f'#_:coef# * #_:{rhs_arr(ith_stmt)}#'

    rhs_expr = ' + '.join([term(ith_stmt) for _ in range(n_rhs_exprs)])
    lhs_expr = f'#_:{lhs_arr(ith_stmt)}#'
    return f'{lhs_expr} = {rhs_expr};'

def fill_linear_statements(n_stmts, n_total_zeroes, skeleton):
    stmts = []

    # Determine how many exprs each statement will have
    rhs_exprs = [max_rhs_exprs] * n_stmts
    n_zero_count = 0
    while n_zero_count < n_total_zeroes:
        which_stmt = randint(0, n_stmts-1)
        if rhs_exprs[which_stmt] == 1:
            continue
        rhs_exprs[which_stmt] -= 1
        n_zero_count += 1

    for ith_stmt in range(n_stmts):
        stmts.append(stmt_skeleton(rhs_exprs[ith_stmt], ith_stmt))
    stmts = [Mapping('_', stmts, is_finite=True)]
    return skeleton.fill_statements(stmts)

def fill_coefs(n_coefs, skeleton):
    coefs = [f'{uniform(1.1, 9.9):.1f}' for _ in range(n_coefs)]
    exprs = [Mapping('coef', coefs, is_finite=True)]
    return skeleton.fill_expressions(exprs)

def fill_lhs(n_stmts, skeleton):
    exprs = [
        Mapping(lhs_arr(i), [f'Arr{i+1:02d}'])
        for i in range(n_stmts)
    ]
    return skeleton.fill_expressions(exprs)

def fill_rhs_loop(loop_size, skeleton):
    exprs = [
        Mapping(rhs_arr(i), [f'Arr{((i+1)%loop_size)+1:02d}[#_:index#]'], is_finite=True)
        for i in range(loop_size)
    ]
    return skeleton.fill_expressions(exprs)

def fill_rhs(loop_size, skeleton):
    exprs = [
        Mapping(rhs_arr(i), [f'Arr{i+1:02d}[#_:index#]'])
        for i in range(loop_size)
    ]
    return skeleton.fill_expressions(exprs)

def fill_index(skeleton):
    exprs = [
        Mapping('index', ['i-1', 'i-2', 'i-3'])
    ]
    return skeleton.fill_expressions(exprs)

def gen_program():
    n_stmts = randint(1, max_stmts)

    skeleton = Skeleton(skeleton_code)

    skeleton = fill_empty_statements(max_stmts - n_stmts, '_', skeleton)
    print(skeleton)

    max_total_exprs = max_rhs_exprs * n_stmts

    # We want the rhs to have at least one non-zero atom
    n_total_zeroes = randint(0, max_total_exprs - n_stmts)

    skeleton = fill_linear_statements(n_stmts, n_total_zeroes, skeleton)
    print(skeleton)

    n_coefs = max_total_exprs - n_total_zeroes
    skeleton = fill_coefs(n_coefs, skeleton)
    print(skeleton)

    skeleton = fill_lhs(n_stmts, skeleton)
    print(skeleton)

    skeleton = fill_rhs_loop(n_stmts, skeleton)
    print(skeleton)

    skeleton = fill_rhs(n_stmts, skeleton)
    print(skeleton)

    skeleton = fill_index(skeleton)
    print(skeleton)

gen_program()
