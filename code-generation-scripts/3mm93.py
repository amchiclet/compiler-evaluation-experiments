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
declare nj;
declare nl;
declare nm;
declare F[900][1100];
declare C[900][1200];
declare D[1200][1100];

for [(i, >=0, <=nj-1), (j, >=0, <=nl-1)] {
  F[i][j] = (0.0);
  for [(k, >=0, <=nm-1)] {
    F[i][j] = F[i][j] + C[i][k] * D[k][j];
  }
}
"""

var_map = VariableMap(default_min=0, default_max=1200)
var_map.set_value('nj', 900)
var_map.set_value('nl', 1100)
var_map.set_value('nm', 1200)
types = TypeAssignment(default_types=['int'])
types.set('F', 'double')
types.set('C', 'double')
types.set('D', 'double')
for i in range(2, 9):
    types.set(f'F{i}', 'double')
    types.set(f'C{i}', 'double')
    types.set(f'D{i}', 'double')
init_value_map = {
    'F': 'drand(0.0, 1.0)',
    'C': 'drand(0.0, 1.0)',
    'D': 'drand(0.0, 1.0)',
    'nj': '900',
    'nl': '1100',
    'nm': '1200',
}
for i in range(2, 9):
    init_value_map[f'F{i}'] = 'drand(0.0, 1.0)'
    init_value_map[f'C{i}'] = 'drand(0.0, 1.0)'
    init_value_map[f'D{i}'] = 'drand(0.0, 1.0)'

application = 'LoopGen'
batch = 'lore'
n_iterations = 10
n_elements = 0

pattern_orig = parse_pattern(original_loop)
print(pattern_orig.pprint())
instance_orig = create_instance(pattern_orig, var_map, types=types, max_tries=1)
print(instance_orig.pprint())
name = f'3mm93_orig'
code = f'{name}.c'
codelet = f'{code}_de'
generate_codelet_full('LoopGen', batch, code, codelet,
                      n_iterations, n_elements, instance_orig, init_value_map)

skeleton_loop = """
declare nj;
declare nl;
declare nm;
declare F[900][1100];
declare F2[][];
declare F3[][];
declare F4[][];
declare F5[][];
declare F6[][];
declare F7[][];
declare F8[][];
declare C[900][1200];
declare C2[][];
declare C3[][];
declare C4[][];
declare C5[][];
declare C6[][];
declare C7[][];
declare C8[][];
declare D[1200][1100];
declare D2[][];
declare D3[][];
declare D4[][];
declare D5[][];
declare D6[][];
declare D7[][];
declare D8[][];

for [(i, >=0, <=nj-1), (j, >=0, <=nl-1)] {
  F[i][j] = (0.0);
  $_:init2$
  $_:init3$
  $_:init4$
  $_:init5$
  $_:init6$
  $_:init7$
  $_:init8$
  for [(k, >=0, <=nm-1)] {
    F[i][j] = F[i][j] + C[i][k] * D[k][j];
    $_:calc2$
    $_:calc3$
    $_:calc4$
    $_:calc5$
    $_:calc6$
    $_:calc7$
    $_:calc8$
  }
}
"""
skeleton = parse_skeleton(skeleton_loop)

def generate(skeleton, n_init, n_calc):
    stmt_parameters = PopulateParameters()

    for i in range(2, 2 + n_init):
        stmt_parameters.add(f'init{i}', [parse_stmt(f'F{i}[i][j] = (0.0);')])
    for i in range(2 + n_init, 9):
        stmt_parameters.add(f'init{i}', [parse_stmt(';')])
    for i in range(2, 2 + n_calc):
        stmt_parameters.add(f'calc{i}', [parse_stmt(f'F{i}[i][j] = F{i}[i][j] + C{i}[i][k] * D{i}[k][j];')])
    for i in range(2 + n_calc, 9):
        stmt_parameters.add(f'calc{i}', [parse_stmt(';')])

    skeleton_done = populate_stmt(skeleton, stmt_parameters.populate)
    return skeleton_done

generated = set()
n_to_generate = 15
while len(generated) < n_to_generate:
    n_init = randint(1, 7)
    n_calc = randint(1, 7)
    if (n_init, n_calc) in generated:
        continue
    generated.add((n_init, n_calc))
    generated_skeleton = generate(skeleton.clone(), n_init, n_calc)
    pattern = parse_pattern(generated_skeleton.pprint())
    # print(pattern.pprint())
    # continue
    instance = create_instance(pattern, var_map, types=types, max_tries=1)
    name = f'3mm93_{n_init+1}_{n_calc+1}'
    code = f'{name}.c'
    codelet = f'{code}_de'
    generate_codelet_full('LoopGen', batch, code, codelet,
                          n_iterations, n_elements, instance, init_value_map)
