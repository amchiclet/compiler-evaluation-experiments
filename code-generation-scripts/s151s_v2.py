from pattern import parse_str as parse_pattern, generate_patterns_from_skeleton
from instance import create_instance
from constant_assignment import VariableMap
from type_assignment import TypeAssignment
from codegen.c_generator import generate_code
from codelet_generator import generate_codelet_full
from skeleton import \
    parse_str as parse_skeleton, \
    parse_stmt_str as parse_stmt, \
    parse_expr_str as parse_expr, \
    generate_from_skeleton
from skeleton_ast import Op, Var
from populator import PopulateParameters, populate_stmt, populate_expr, populate_op, populate_name, ChoiceRecorder
from random import randint, seed

seed(0)
original_loop = """
declare a[32000];
declare b[32000];
declare m;

for [(i, >=0, <=31998)] {
  a[i] = a[i+m] + b[i];
}
"""

var_map = VariableMap(default_min=0, default_max=32000)
var_map.set_value('m', 1)
types = TypeAssignment(default_types=['int'])
types.set('m', 'int')
types.set('a', 'double')
types.set('b', 'double')
types.set('e', 'double')
init_value_map = {
    'm': '1',
    'a': 'drand(0.0, 1.0)',
    'b': 'drand(0.0, 1.0)',
    'e': 'drand(0.0, 1.0)',
}

application = 'LoopGen'
batch = 'lore'
n_iterations = 10
n_elements = 0

# pattern_orig = parse_pattern(original_loop)
# instance_orig = create_instance(pattern_orig, var_map, types=types, max_tries=1)
# name = f's151s_v2_orig'
# code = f'{name}.c'
# codelet = f'{code}_de'
# generate_codelet_full('LoopGen', batch, code, codelet,
#                       n_iterations, n_elements, instance_orig, init_value_map)

skeleton_loop = """
declare m;
declare a[][32000];
declare b[][32000];
declare e[][][32000];

for [(i, >=0, <=31998)] {
  $_:s0$
  $_:s1$
  $_:s2$
  $_:s3$
}
"""
skeleton = parse_skeleton(skeleton_loop)

def generate(skeleton, n_exprs_list):
    stmt_parameters = PopulateParameters()
    expr_parameters = PopulateParameters()
    for x in range(len(n_exprs_list)):
        n_exprs = n_exprs_list[x]
        stmt_code = (f'a[{x}][i] = a[{x}][i+m] + b[{x}][i] + '
                     f'            #_:e{x}0# + #_:e{x}1# + #_:e{x}2# + '
                     f'            #_:e{x}3# + #_:e{x}4# + #_:e{x}5# + '
                     f'            #_:e{x}6# + #_:e{x}7# + #_:e{x}8#;')
        stmt_parameters.set(f's{x}', [parse_stmt(stmt_code)])
        for y in range(n_exprs):
            expr_parameters.set(f'e{x}{y}', [parse_expr(f'e[{x}][{y}][i]')])
        for y in range(n_exprs, 10):
            expr_parameters.set(f'e{x}{y}', [parse_expr(f'0')])
    for x in range(len(n_exprs_list), 4):
        stmt_parameters.set(f's{x}', [parse_stmt(';')])
    skeleton = populate_stmt(skeleton, stmt_parameters.populate)
    skeleton = populate_expr(skeleton, expr_parameters.populate)
    return skeleton


generated = set()
n_to_generate = 15
while len(generated) < n_to_generate:
    n_exprs_list = [randint(1, 9) for _ in range(randint(1, 4))]
    print(n_exprs_list)
    code_id = tuple(n_exprs_list)
    if code_id in generated:
        continue
    generated.add(code_id)
    generated_skeleton = generate(skeleton.clone(), n_exprs_list)
    pattern = parse_pattern(generated_skeleton.pprint())
    instance = create_instance(pattern, var_map, types=types, max_tries=1)
    print(instance.pprint())
    name = f's151s_v2_' + '_'.join(map(str, n_exprs_list))
    code = f'{name}.c'
    codelet = f'{code}_de'
    generate_codelet_full('LoopGen', batch, code, codelet,
                          n_iterations, n_elements, instance, init_value_map)
