from skeleton import \
    parse_str as parse_skeleton, \
    parse_stmt_str as parse_statement, \
    parse_seq_str as parse_seq, \
    parse_expr_str as parse_expression

from pattern import generate_patterns_from_skeleton
from skeleton_ast import Var, Op
from random import choice, seed, getstate, setstate
from constant_assignment import VariableMap
from type_assignment import TypeAssignment

from instance import create_instance
# from codelet_generator import generate_codelet_full, name
from populator import PopulateParameters, populate_name, populate_stmt, populate_expr, populate_op

seed(0)

skeleton_code = """
declare A[][];
declare B[][];
declare C[][];
declare D[][];
declare a;
declare b;
declare n;

for [(i, >=0, <=n), (j, >=0, <=n)] {
  $_$
  $_$
}
"""

scalar_names = ['a', 'b']
array_names = ['A', 'B', 'C', 'D']
index_names = ['i', 'j']
op_names = ['+', '*']

def generate_statement_with_two_array_operands():
    code = '#_:lhs# = #_:rhs# @_:op@ #_:rhs# @_:op@ #_:rhs#;'
    code = parse_statement(code)
    lhs = ['#_:array#']
    rhs = ['#_:array#', '#_:array#', '#_:array#', '#_:non_array#']

    exprs = PopulateParameters()
    exprs.add('lhs', [parse_expression(code) for code in lhs])
    exprs.add('rhs', [parse_expression(code) for code in rhs], is_finite=True)
    code = populate_expr(code, exprs.populate)
    return code

def generate(skeleton):
    code = skeleton.clone()
    stmts = PopulateParameters(
        [generate_statement_with_two_array_operands() for _ in range(2)],
        is_finite=True
    )
    code = populate_stmt(code, stmts.populate)

    exprs = PopulateParameters()
    exprs.add('array', [parse_expression(code) for code in [f'{name}[i][j]' for name in array_names]])
    exprs.add('non_array', [parse_expression(code) for code in ['#_:scalar#', '#_:literal#']])
    code = populate_expr(code, exprs.populate)

    exprs = PopulateParameters()
    exprs.add('scalar', [parse_expression(code) for code in scalar_names])
    exprs.add('literal', [parse_expression('1.5')])
    code = populate_expr(code, exprs.populate)

    ops = PopulateParameters()
    ops.add('op', list(map(Op, op_names)))
    code = populate_op(code, ops.populate)

    return code

skeleton = parse_skeleton(skeleton_code)
# print(skeleton.pprint())
# exit()
patterns = []
hashes = set()

patterns += generate_patterns_from_skeleton(
    generate,
    skeleton,
    n_wanted = 10,
    existing_hashes = hashes)

for pattern in patterns:
    print(pattern.pprint())

types = TypeAssignment()
for v in array_names + scalar_names:
    types.set(v, 'double')
types.set('n', 'int')

def create_value_map(size):
    init_value_map = VariableMap()
    for v in array_names + scalar_names:
        init_value_map.set_range(v, 0.0, 1.0)
    init_value_map.set_value('n', size-1)
    return init_value_map

def create_var_map(size):
    var_map = VariableMap(size, size)
    var_map.set_value('n', size-1)
    return var_map

from codelet_generator import name, generate_codelet_full

application = 'LoopGen'
sizes = [420, 600, 850, 2550]
n_iterations = 10

for size in sizes:
    for pattern in patterns:
        var_map = create_var_map(size)
        value_map = create_value_map(size)
        instance = create_instance(pattern, var_map, types=types)
        print(instance.pattern.pprint())
        code_prefix = f'{name(instance.pattern)}'
        code = f'{code_prefix}.c'
        codelet = f'{code_prefix}_{size}.c_de'

        generate_codelet_full(application, f'2-2-ops-{size}', code, codelet, n_iterations, instance, value_map)
