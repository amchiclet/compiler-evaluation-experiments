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
from populator import PopulateParameters, populate_stmt, FixedChoice
from random import randint, seed

seed(0)
original_loop = """
declare inner_loops;
declare Vx[1001];
declare Ex1[1001];
declare Xx[1001];
declare Xi[1001];
declare Dex1[1001];
declare Xtra[40];
declare Ir[1001];
declare Rx[1001];

for [(k, >=0, <=inner_loops)] {
  Vx[k] = Vx[k] + Ex1[k] + (Xx[k] - Xi[k]) * Dex1[k];
  Xx[k] = Xx[k] + Vx[k] + Xtra[27];
  Ir[k] = Xx[k];
  Rx[k] = Xx[k] - Ir[k];
  Ir[k] = (Ir[k] & (2048 - 1)) + 1;
  Xx[k] = Rx[k] + Ir[k];
}
"""

var_map = VariableMap(default_min=0, default_max=1200)
var_map.set_value('inner_loops', 1000)

types = TypeAssignment(default_types=['int'])
types.set('Vx', 'double')
types.set('Ex1', 'double')
types.set('Xx', 'double')
types.set('Xi', 'double')
types.set('Dex1', 'double')
types.set('Xtra', 'double')
types.set('Ir', 'int')
types.set('Rx', 'double')

for i in range(2, 3):
    types.set(f'Vx{i}', 'double')
    types.set(f'Ex1{i}', 'double')
    types.set(f'Xx{i}', 'double')
    types.set(f'Xi{i}', 'double')
    types.set(f'Dex1{i}', 'double')
    types.set(f'Xtra{i}', 'double')
    types.set(f'Ir{i}', 'int')
    types.set(f'Rx{i}', 'double')
init_value_map = {
    'Vx': 'drand(0.0, 1.0)',
    'Ex1': 'drand(0.0, 1.0)',
    'Xx': 'drand(0.0, 1.0)',
    'Xi': 'drand(0.0, 1.0)',
    'Dex1': 'drand(0.0, 1.0)',
    'Xtra': 'drand(0.0, 1.0)',
    'Ir': 'irand(0, 10)',
    'Rx': 'drand(0.0, 1.0)',
    'inner_loops': '1000',
}
for i in range(2, 3):
    init_value_map[f'Vx{i}'] = 'drand(0.0, 1.0)'
    init_value_map[f'Ex1{i}'] = 'drand(0.0, 1.0)'
    init_value_map[f'Xx{i}'] = 'drand(0.0, 1.0)'
    init_value_map[f'Xi{i}'] = 'drand(0.0, 1.0)'
    init_value_map[f'Dex1{i}'] = 'drand(0.0, 1.0)'
    init_value_map[f'Xtra{i}'] = 'drand(0.0, 1.0)'
    init_value_map[f'Ir{i}'] = 'irand(0, 10)'
    init_value_map[f'Rx{i}'] = 'drand(0.0, 1.0)'

application = 'LoopGen'
batch = 'lore'
n_iterations = 10
n_elements = 0

# pattern_orig = parse_pattern(original_loop)
# print(pattern_orig.pprint())
# instance_orig = create_instance(pattern_orig, var_map, types=types, max_tries=1)
# print(instance_orig.pprint())

# name = f'liv1113_orig'
# code = f'{name}.c'
# codelet = f'{code}_de'
# generate_codelet_full('LoopGen', batch, code, codelet,
#                       n_iterations, n_elements, instance_orig, init_value_map)

skeleton_loop = """
declare inner_loops;
declare Vx[1001];
declare Vx2[];
declare Ex1[1001];
declare Ex12[];
declare Xx[1001];
declare Xx2[];
declare Xi[1001];
declare Xi2[];
declare Dex1[1001];
declare Dex12[];
declare Xtra[40];
declare Xtra2[];
declare Ir[1001];
declare Ir2[];
declare Rx[1001];
declare Rx2[];

for [(k, >=0, <=inner_loops)] {
  Vx[k] = Vx[k] + Ex1[k] + (Xx[k] - Xi[k]) * Dex1[k];
  $_:s1$
  Xx[k] = Xx[k] + Vx[k] + Xtra[27];
  $_:s2$
  Ir[k] = Xx[k];
  $_:s3$
  Rx[k] = Xx[k] - Ir[k];
  $_:s4$
  Ir[k] = (Ir[k] & (2048 - 1)) + 1;
  $_:s5$
  Xx[k] = Rx[k] + Ir[k];
  $_:s6$
}
"""
skeleton = parse_skeleton(skeleton_loop)

def generate(skeleton, choice):
    stmt_parameters = PopulateParameters()
    stmt_parameters.add(
        's1',
        [ parse_stmt(f'Vx2[k] = Vx2[k] + Ex12[k] + (Xx2[k] - Xi2[k]) * Dex12[k];'),
          parse_stmt(';')
        ],
        choice
    )
    stmt_parameters.add(
        's2',
        [ parse_stmt(f'Xx2[k] = Xx2[k] + Vx2[k] + Xtra2[27];'),
          parse_stmt(';')
        ],
        choice
    )
    stmt_parameters.add(
        's3',
        [ parse_stmt(f'Ir2[k] = Xx2[k];'),
          parse_stmt(';')
        ],
        choice
    )
    stmt_parameters.add(
        's4',
        [ parse_stmt(f'Rx2[k] = Xx2[k] - Ir2[k];'),
          parse_stmt(';')
        ],
        choice
    )
    stmt_parameters.add(
        's5',
        [ parse_stmt(f'Ir2[k] = (Ir2[k] & (2048 - 1)) + 1;'),
          parse_stmt(';')
        ],
        choice
    )
    stmt_parameters.add(
        's6',
        [ parse_stmt(f'Xx2[k] = Rx2[k] + Ir2[k];'),
          parse_stmt(';')
        ],
        choice
    )

    skeleton_done = populate_stmt(skeleton, stmt_parameters.populate)
    return skeleton_done

generated = set()
n_to_generate = 15
while len(generated) < n_to_generate:
    choices = tuple([randint(0, 1) for _ in range(6)])
    if choices in generated:
        continue
    generated.add(choices)
    choice = FixedChoice(choices).choice
    generated_skeleton = generate(skeleton.clone(), choice)
    pattern = parse_pattern(generated_skeleton.pprint())
    # print(pattern.pprint())
    # continue
    instance = create_instance(pattern, var_map, types=types, max_tries=1)
    print(instance.pprint())
    fchoices = ''.join(map(str, choices))
    name = f'liv1113_{fchoices}'
    code = f'{name}.c'
    codelet = f'{code}_de'
    generate_codelet_full('LoopGen', batch, code, codelet,
                          n_iterations, n_elements, instance, init_value_map)
