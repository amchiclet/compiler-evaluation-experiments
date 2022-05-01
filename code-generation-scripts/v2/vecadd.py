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
declare a[N];
declare b[N];
declare N;

for [(i, >=0, <=N-1)] {
  a[i] = a[i] + b[i];
}
"""

size = 1000000
var_map = VariableMap()
var_map.set_value('N', size)
types = TypeAssignment(default_types=['int'])
types.set('N', 'int')
types.set('a', 'double')
types.set('b', 'double')
init_value_map = {
    'N': 'n_elements',
    'a': 'drand(0.0, 1.0)',
    'b': 'drand(0.0, 1.0)',
}

application = 'LoopGen'
batch = 'vecadd'
n_iterations = 10
n_elements = 0

pattern_orig = parse_pattern(original_loop)
instance_orig = create_instance(pattern_orig, var_map, types=types, max_tries=1)

name = f'a_ab'
code = f'{name}.c'
codelet = f'{code}_de'
generate_codelet_full('LoopGen', batch, code, codelet,
                      n_iterations, n_elements, instance_orig, init_value_map)
