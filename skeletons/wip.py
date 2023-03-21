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
max_exprs = 10

def gen_program():
    n_stmts = randint(1, max_stmts)
    n_empty_stmts = max_stmts - n_stmts

    empty_stmts = [
        Mapping(
            '_', [';'] * n_empty_stmts, is_finite = True,
        )
    ]

    program = Skeleton(skeleton_code)
    program = program.fill_statements(empty_stmts)

    stmts = [
        Mapping(
            '_', ['#_:lhs# = #_:rhs#;'],
        )
    ]
    program = program.fill_statements(stmts)
    
    print(program)

gen_program()
