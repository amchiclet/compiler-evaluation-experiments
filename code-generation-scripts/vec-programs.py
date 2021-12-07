from pattern import parse_str, parse_stmt_str, parse_expr_str
from instance import try_create_instance
from constant_assignment import VariableMap
from type_assignment import TypeAssignment
from codelet_generator import generate_codelet_var_ints
from populator import PopulateParameters, populate_stmt, populate_expr
from random import randint, seed
from pathlib import Path

n_exprs = 9
n_iterations = 10

types = TypeAssignment(default_types=['int'])
types.set('A', 'double')
types.set('B1', 'double')
types.set('B2', 'double')
types.set('B3', 'double')
types.set('B4', 'double')
types.set('B5', 'double')
types.set('B6', 'double')
types.set('B7', 'double')
types.set('B8', 'double')
types.set('B9', 'double')

init_value_map = {
    'I': '32000',
    'A': 'drand(0.0, 1.0)',
    'B1': 'drand(0.0, 1.0)',
    'B2': 'drand(0.0, 1.0)',
    'B3': 'drand(0.0, 1.0)',
    'B3': 'drand(0.0, 1.0)',
    'B4': 'drand(0.0, 1.0)',
    'B5': 'drand(0.0, 1.0)',
    'B6': 'drand(0.0, 1.0)',
    'B7': 'drand(0.0, 1.0)',
    'B8': 'drand(0.0, 1.0)',
    'B9': 'drand(0.0, 1.0)',
}

dst_dir = 'output'
Path(dst_dir).mkdir(parents=True, exist_ok=True)

loop_code = """
declare I;
declare A[];
declare B1[];
declare B2[];
declare B3[];
declare B4[];
declare B5[];
declare B6[];
declare B7[];
declare B8[];
declare B9[];

for [(i, >=0, <=I-1)] {
  A[i] = (#_# * #_# + #_#) + (#_# * #_# + #_#) + (#_# * #_# + #_#);
}
"""

skeleton = parse_str(loop_code)

def populate_exprs(skeleton, n_vars):
    indices = [i for i in range(1, n_vars+1)]
    for i in range(n_exprs - n_vars):
        indices.append(randint(1, n_vars))
    exprs = [parse_expr_str(f'B{i}[i]') for i in indices]
    for e in exprs:
        p = PopulateParameters(exprs, is_finite=True)
    return populate_expr(skeleton, p.populate)

def gen(skeleton, n_vars):
    program = populate_exprs(skeleton.clone(), n_vars)
    var_map = VariableMap(0, 32000)
    var_map.set_value('I', 32000)
    instance = try_create_instance(program, var_map, types)
    print(instance.pprint())
    batch = 'vec_1_stmt'
    name = f'vec_{n_vars}_loads'
    code = f'{name}.c'
    codelet = f'{code}_de'
    generate_codelet_var_ints('LoopGen', batch, code, codelet,
                              n_iterations, [32000], instance, init_value_map)

seed(0)
for n_vars in range(1, n_exprs+1):
    gen(skeleton.clone(), n_vars)

