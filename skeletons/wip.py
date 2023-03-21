from api import Skeleton, Mapping, CodegenConfig
from random import randint, seed
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

def fill_empty_statements(n_empty_stmts, family_name, skeleton):
    print(n_empty_stmts)
    empty_stmts = [Mapping(family_name, [';'] * n_empty_stmts, is_finite = True)]
    skeleton = skeleton.fill_statements(empty_stmts)
    return skeleton

def stmt_skeleton(n_rhs_exprs, family_name):
    rhs_exprs = []
    for i in range(n_rhs_exprs):
        rhs_exprs.append(f'#_:{family_name}_coef# * #_:{family_name}_rhs_arr#')
    rhs = ' + '.join(rhs_exprs)
    lhs = f'#_:{family_name}_lhs_arr#'
    return f'{lhs} = {rhs};'

def fill_linear_statements(n_stmts, family_prefix, skeleton):
    stmts = []
    for i in range(n_stmts):
        family_name = f'{family_prefix}_{i}'
        print(family_name)
        stmts.append(stmt_skeleton(max_rhs_exprs, family_name))
    stmts = [Mapping('_', stmts, is_finite = True)]
    return skeleton.fill_statements(stmts)

def gen_program():
    n_stmts = randint(1, max_stmts)

    skeleton = Skeleton(skeleton_code)
    skeleton = fill_empty_statements(max_stmts - n_stmts, '_', skeleton)
    print(skeleton)
    skeleton = fill_linear_statements(n_stmts, 'stmt', skeleton)
    print(skeleton)

gen_program()
