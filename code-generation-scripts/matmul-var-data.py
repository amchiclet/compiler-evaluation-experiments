from pattern import parse_str as parse_pattern, generate_patterns_from_skeleton
from instance import create_instance
from constant_assignment import VariableMap
from type_assignment import TypeAssignment
from codegen.c_generator import generate_code
from codelet_generator import generate_codelet_var_ints
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
declare a[M][K];
declare b[K][N];
declare c[M][N];
declare M;
declare N;
declare K;

for [
  (m, >=0, <=M-1),
  (n, >=0, <=N-1),
  (k, >=0, <=K-1)
] {
  c[m][n] = c[m][n] + a[m][k] * b[k][n];
}
"""

M = 50
N = 60
K = 150
var_map = VariableMap()
var_map.set_value('M', M)
var_map.set_value('N', N)
var_map.set_value('K', K)
types = TypeAssignment(default_types=['int'])
types.set('M', 'int')
types.set('N', 'int')
types.set('K', 'int')
types.set('a', 'double')
types.set('b', 'double')
types.set('c', 'double')
init_value_map = {    
    'M': 'inputs[0]',
    'N': 'inputs[1]',
    'K': 'inputs[2]',
    'a': 'drand(0.0, 1.0)',
    'b': 'drand(0.0, 1.0)',
    'c': 'drand(0.0, 1.0)',
}

application = 'LoopGen'
batch = 'matmul-var-data'
n_iterations = 10
int_inputs = [M, N, K]

pattern_orig = parse_pattern(original_loop)
instance_orig = create_instance(pattern_orig, var_map, types=types, max_tries=1)

name = f'matmul-var-data'
code = f'{name}.c'
codelet = f'{code}_de'
generate_codelet_var_ints('LoopGen', batch, code, codelet,
                          n_iterations, int_inputs, instance_orig, init_value_map)
