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
for i in range(2, 17):
    types.set(f'a{i}', 'double')
    types.set(f'b{i}', 'double')
init_value_map = {
    'm': '1',
    'a': 'drand(0.0, 1.0)',
    'b': 'drand(0.0, 1.0)',
}
for i in range(2, 17):
    init_value_map[f'a{i}'] = 'drand(0.0, 1.0)'
    init_value_map[f'b{i}'] = 'drand(0.0, 1.0)'


application = 'LoopGen'
batch = 'lore'
n_iterations = 10
n_elements = 0

pattern_orig = parse_pattern(original_loop)
instance_orig = create_instance(pattern_orig, var_map, types=types, max_tries=1)
name = f's151s_orig'
code = f'{name}.c'
codelet = f'{code}_de'
generate_codelet_full('LoopGen', batch, code, codelet,
                      n_iterations, n_elements, instance_orig, init_value_map)

exit()

skeleton_loop = """
declare a[32000];
declare a2[];
declare a3[];
declare a4[];
declare a5[];
declare a6[];
declare a7[];
declare a8[];
declare a9[];
declare a10[];
declare a11[];
declare a12[];
declare a13[];
declare a14[];
declare a15[];
declare a16[];
declare b[32000];
declare b2[];
declare b3[];
declare b4[];
declare b5[];
declare b6[];
declare b7[];
declare b8[];
declare b9[];
declare b10[];
declare b11[];
declare b12[];
declare b13[];
declare b14[];
declare b15[];
declare b16[];
declare m;

for [(i, >=0, <=31998)] {
  a[i] = a[i+m] + b[i];
  $_:s2$
  $_:s3$
  $_:s4$
  $_:s5$
  $_:s6$
  $_:s7$
  $_:s8$
  $_:s9$
  $_:s10$
  $_:s11$
  $_:s12$
  $_:s13$
  $_:s14$
  $_:s15$
  $_:s16$
}
"""
skeleton = parse_skeleton(skeleton_loop)

stmt_parameters = PopulateParameters()
name_parameters = PopulateParameters()
stmt = "`_:a`[i] = `_:a`[i+m] + `_:b`[i];"
stmt_skeleton = parse_stmt(stmt)
for i in range(2, 17):
    stmt_parameters.set(f's{i}', [parse_stmt(';')])

for i in range(2, 17):
    name_parameters.set('a', [Var(f'a{i}')])
    name_parameters.set('b', [Var(f'b{i}')])
    stmt_plug = populate_name(stmt_skeleton.clone(), name_parameters.populate)
    stmt_parameters.set(f's{i}', [stmt_plug])
    skeleton_done = populate_stmt(skeleton.clone(), stmt_parameters.populate)
    pattern = parse_pattern(skeleton_done.pprint())
    instance = create_instance(pattern, var_map, types=types, max_tries=1)
    print(instance.pprint())
    name = f's151s_{i:02d}'
    code = f'{name}.c'
    codelet = f'{code}_de'
    print(codelet)
    generate_codelet_full('LoopGen', batch, code, codelet,
                          n_iterations, n_elements, instance, init_value_map)
