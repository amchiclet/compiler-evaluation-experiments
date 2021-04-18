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
from populator import PopulateParameters, populate_name, populate_stmt, populate_expr, populate_op

seed(0)

skeleton_code = """
declare A[][];
declare B[][];
declare C[][];
declare D[][];
declare E[][];
declare a;
declare b;
declare n;

for [(i, >=0, <=n), (j, >=0, <=n)] {
  $_$
}
"""

scalar_names = ['a', 'b']
array_names = ['A', 'B', 'C', 'D']
index_names = ['i', 'j']
op_names = ['+', '*']

def generate_statement_with_two_array_operands():
    code = '#_:lhs# = #_:rhs# @_:op@ #_:rhs# @_:op@ #_:rhs# @_:op@ #_:rhs#;'
    code = parse_statement(code)
    lhs = ['#_:array#']
    rhs = ['#_:array#', '#_:array#', '#_:array#', '#_:array#', '#_:non_array#', '#_:non_array#']

    exprs = PopulateParameters()
    exprs.add('lhs', [parse_expression(code) for code in lhs])
    exprs.add('rhs', [parse_expression(code) for code in rhs], is_finite=True)
    code = populate_expr(code, exprs.populate)
    return code

def generate(skeleton):
    code = skeleton.clone()
    stmts = PopulateParameters(
        [generate_statement_with_two_array_operands() for _ in range(1)],
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

patterns = []
hashes = set()

patterns += generate_patterns_from_skeleton(
    generate,
    skeleton,
    n_wanted = 1,
    existing_hashes = hashes)

for pattern in patterns:
    print(pattern.pprint())

def create_type_assignment():
    types = TypeAssignment()
    for v in array_names + scalar_names:
        types.set(v, 'double')
    types.set('n', 'int')
    return types

def create_init_value_map():
    init_value_map = {}
    for v in array_names + scalar_names:
        init_value_map[v] = 'drand(0.0, 1.0)'
    init_value_map['n'] = 'n_elements'
    return init_value_map

def create_var_map(size):
    var_map = VariableMap(size, size)
    var_map.set_value('n', size-1)
    return var_map

from codelet_generator import name, generate_codelet_full

application = 'LoopGen'

n_iterations = 1
n_elements = 850

types = create_type_assignment()
var_map = create_var_map(n_elements)
value_map = create_init_value_map()

for pattern in patterns:
    instance = create_instance(pattern, var_map, types=types)
    print(instance.pattern.pprint())
    code_prefix = f'{name(instance.pattern)}'
    code = f'{code_prefix}.c'
    codelet = f'{code_prefix}.c_de'

    generate_codelet_full(application, '3-ops-n', code, codelet,
                          n_iterations, n_elements, instance, value_map)
