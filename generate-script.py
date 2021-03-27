from skeleton import \
    parse_str as parse_skeleton, \
    parse_stmt_str as parse_statement, \
    parse_seq_str as parse_seq, \
    parse_expr_str as parse_expression

from pattern import generate_patterns_from_skeleton
from skeleton_ast import Var, Op
from random import choice, seed
from instance import create_instance_with_fixed_size
from codelet_generator import generate_codelet_full, name
from populator import PopulateParameters, populate_name, populate_stmt, populate_expr, populate_op

seed(12345)
skeleton_code = """
declare A[][];
declare B[][];
declare C[][];
declare D[][];
declare E[][];
declare a;
declare b;
declare c;

for [i, j] {
  $_:stmt$
  $_:stmt$
}
"""

scalar_names = ['a', 'b', 'c']
array_names = ['A', 'B', 'C', 'D', 'E']
index_names = ['i', 'j']
op_names = ['+', '*']

def create_exploration_factory():
    stmt = ['#_:lhs# = #_:rhs# @_:op@ #_:rhs# @_:op@ #_:rhs#;']
    lhs = ['`_:X_lhs`[`i1:I`][`i2:I`]']
    rhs = ['`_:X_rhs`[`i1:I`][`i2:I`]', '`_:S_rhs`', '1.5']

    stmts = PopulateParameters()
    stmts.add('stmt', [parse_statement(code) for code in stmt])

    exprs = PopulateParameters()
    exprs.add('lhs', [parse_expression(code) for code in lhs])
    exprs.add('rhs', [parse_expression(code) for code in rhs])

    ops = PopulateParameters()
    ops.add('op', list(map(Op, op_names)))

    names = PopulateParameters()
    names.add('X_lhs', list(map(Var, array_names)))
    names.add('X_rhs', list(map(Var, array_names)))
    names.add('S_rhs', list(map(Var, scalar_names)))
    names.add('I', list(map(Var, index_names)), is_finite=True)

    def generate(code):
        code = populate_stmt(code, stmts.populate)
        code = populate_expr(code, exprs.populate)
        code = populate_op(code, ops.populate)
        code = populate_name(code, names.populate)
        return code
    return generate

def create_targeted_factory():
    stmt = [
        '#_:shared# = #_:rhs# @_:op@ #_:rhs# @_:op@ #_:rhs#;',
        '#_:lhs# = #_:shared# @_:op@ #_:rhs# @_:op@ #_:rhs#;',
        '#_:lhs# = #_:rhs# @_:op@ #_:shared# @_:op@ #_:rhs#;',
        '#_:lhs# = #_:rhs# @_:op@ #_:rhs# @_:op@ #_:shared#;',
    ]
    shared = ['`x:X_shared`[`i1:I`][`i2:I`]']
    lhs = ['`_:X_lhs`[`i1:I`][`i2:I`]']
    rhs = ['`_:X_rhs`[`i1:I`][`i2:I`]', '`_:S_rhs`', '1.5']

    stmts = PopulateParameters()
    stmts.add('stmt', [parse_statement(code) for code in stmt])

    exprs = PopulateParameters()
    exprs.add('shared', [parse_expression(code) for code in shared])
    exprs.add('lhs', [parse_expression(code) for code in lhs])
    exprs.add('rhs', [parse_expression(code) for code in rhs])

    ops = PopulateParameters()
    ops.add('op', list(map(Op, op_names)))

    names = PopulateParameters()
    names.add('X_shared', list(map(Var, array_names)))
    names.add('X_lhs', list(map(Var, array_names)))
    names.add('X_rhs', list(map(Var, array_names)))
    names.add('S_rhs', list(map(Var, scalar_names)))
    names.add('I', list(map(Var, index_names)), is_finite=True)

    def generate(code):
        code = populate_stmt(code, stmts.populate)
        code = populate_expr(code, exprs.populate)
        code = populate_op(code, ops.populate)
        code = populate_name(code, names.populate)
        return code
    return generate

skeleton = parse_skeleton(skeleton_code)

generate_exploratory_code = create_exploration_factory()
generate_targeted_code = create_targeted_factory()

patterns = []
hashes = set()

patterns += generate_patterns_from_skeleton(
    generate_targeted_code,
    skeleton,
    n_wanted = 50,
    existing_hashes = hashes)
patterns += generate_patterns_from_skeleton(
    generate_exploratory_code,
    skeleton,
    n_wanted = 250,
    existing_hashes = hashes)

application = 'LoopGen'
size = 2550
n_iterations = 10
for pattern in patterns:
    instance = create_instance_with_fixed_size(pattern, index_names, size)
    print(instance.pattern.pprint())
    code_prefix = f'{name(instance.pattern)}'
    code = f'{code_prefix}.c'
    codelet = f'{code_prefix}_{size}.c_de'

    generate_codelet_full(application, 'two-statements-mixed-2550', code, codelet, n_iterations, instance)
