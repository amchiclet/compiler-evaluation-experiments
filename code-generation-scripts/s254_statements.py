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
declare x;

for [(i, >=0, <=31999)] {
  a[i] = (b[i]+x) * .5;
  x = b[i];
}
"""

var_map = VariableMap(default_min=0, default_max=32000)
types = TypeAssignment(default_types=['int'])
types.set('a', 'double')
types.set('b', 'double')
types.set('x', 'double')
for i in range(2, 17):
    types.set(f'a{i}', 'double')
    types.set(f'b{i}', 'double')
    types.set(f'x{i}', 'double')
init_value_map = {
    'a': 'drand(0.0, 1.0)',
    'b': 'drand(0.0, 1.0)',
    'x': 'drand(0.0, 1.0)',
}
for i in range(2, 17):
    init_value_map[f'a{i}'] = 'drand(0.0, 1.0)'
    init_value_map[f'b{i}'] = 'drand(0.0, 1.0)'
    init_value_map[f'x{i}'] = 'drand(0.0, 1.0)'

application = 'LoopGen'
batch = 'lore'
n_iterations = 10
n_elements = 0

pattern_orig = parse_pattern(original_loop)
print(pattern_orig.pprint())
instance_orig = create_instance(pattern_orig, var_map, types=types, max_tries=1)
name = f's254_orig'
code = f'{name}.c'
codelet = f'{code}_de'
generate_codelet_full('LoopGen', batch, code, codelet,
                      n_iterations, n_elements, instance_orig, init_value_map)

skeleton_loop = """
declare a[32000];
declare a2[];
declare a3[];
declare a4[];
declare a5[];
declare a6[];
declare a7[];
declare a8[];
declare b[32000];
declare b2[];
declare b3[];
declare b4[];
declare b5[];
declare b6[];
declare b7[];
declare b8[];
declare x;
declare x2;
declare x3;
declare x4;
declare x5;
declare x6;
declare x7;
declare x8;

for [(i, >=0, <=31999)] {
  a[i] = (b[i]+x) * (0.5);
  $_:a2$
  $_:a3$
  $_:a4$
  $_:a5$
  $_:a6$
  $_:a7$
  $_:a8$
  x = b[i];
  $_:x2$
  $_:x3$
  $_:x4$
  $_:x5$
  $_:x6$
  $_:x7$
  $_:x8$
}
"""
skeleton = parse_skeleton(skeleton_loop)

def generate(skeleton, n_a, n_x):
    stmt_parameters = PopulateParameters()

    stmt_a = "`_:a`[i] = (`_:b`[i] + `_:x`) * (0.5);"
    for i in range(2, 2 + n_a):
        name_parameters = PopulateParameters()
        name_parameters.add('a', [Var(f'a{i}')])
        name_parameters.add('b', [Var(f'b{i}')])
        name_parameters.add('x', [Var(f'x{i}')])
        stmt_a_plug = populate_name(parse_stmt(stmt_a), name_parameters.populate)
        stmt_parameters.add(f'a{i}', [stmt_a_plug])
    for i in range(2 + n_a, 9):
        stmt_parameters.add(f'a{i}', [parse_stmt(';')])

    stmt_x = "`_:x` = `_:b`[i];"
    for i in range(2, 2 + n_x):
        name_parameters = PopulateParameters()
        name_parameters.add('a', [Var(f'a{i}')])
        name_parameters.add('b', [Var(f'b{i}')])
        name_parameters.add('x', [Var(f'x{i}')])
        stmt_x_plug = populate_name(parse_stmt(stmt_x), name_parameters.populate)
        stmt_parameters.add(f'x{i}', [stmt_x_plug])
    for i in range(2 + n_x, 9):
        stmt_parameters.add(f'x{i}', [parse_stmt(';')])
    skeleton_done = populate_stmt(skeleton, stmt_parameters.populate)
    return skeleton_done

generated = set()
n_to_generate = 15
while len(generated) < n_to_generate:
    n_a = randint(1, 7)
    n_x = randint(1, 7)
    if (n_a, n_x) in generated:
        continue
    generated.add((n_a, n_x))
    generated_skeleton = generate(skeleton.clone(), n_a, n_x)
    pattern = parse_pattern(generated_skeleton.pprint())
    instance = create_instance(pattern, var_map, types=types, max_tries=1)
    name = f's254_{n_a+1}_{n_x+1}'
    code = f'{name}.c'
    codelet = f'{code}_de'
    generate_codelet_full('LoopGen', batch, code, codelet,
                          n_iterations, n_elements, instance, init_value_map)
