from pattern import parse_str as parse_pattern
from instance import create_instance
from constant_assignment import VariableMap
from type_assignment import TypeAssignment
from codegen.c_generator import generate_code
from codelet_generator import generate_codelet_full, name

code = """
declare A[n];
declare B[n];
declare n;

for [(i, >=0, <=n-1)] {
  A[i] = A[i] + B[i] + 5;
}
"""

pattern = parse_pattern(code)
print(pattern.pprint())

size = 1000000

# Set possible values for n and m.
# We need to do this because n and m are used as loop bounds
# and they determine how much space to allocate arrays with.
var_map = VariableMap()
var_map.set_value('n', size)

# Specify variable types
types = TypeAssignment()
types.set('A', 'double')
types.set('B', 'double')
types.set('n', 'int')

instance = create_instance(pattern, var_map, types=types)
print(instance.pprint())

# Config how values are initialized
init_value_map = {
    'A': 'drand(0.0, 1.0)',
    'B': 'drand(0.0, 1.0)',
    'n': 'n_elements',
}

batch = f'blas1_test'
code_prefix = f'{name(instance.pattern)}'
code = f'{code_prefix}.c'
codelet = f'{code_prefix}.c_de'
n_iterations = 10
n_elements = 1000000

generate_codelet_full('LoopGen', batch, code, codelet,
                      n_iterations, n_elements, instance, init_value_map)

