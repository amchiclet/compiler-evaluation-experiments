from pattern import parse_str as parse_pattern
from instance import create_instance
from constant_assignment import VariableMap
from type_assignment import TypeAssignment
from codegen.c_generator import generate_code
from codelet_generator import generate_codelet_full, name

code = """
declare A[n];
declare B[n];
declare x;
declare n;

for [(i, >=0, <=n-1)] {
  A[i] = (B[i] + x) * 0.5;
  x = B[i];
}
"""

pattern = parse_pattern(code)

artificial_size_limit = 1000000
var_map = VariableMap()
var_map.set_value('n', artificial_size_limit)
var_map.set_value('m', artificial_size_limit)

# Specify variable types
types = TypeAssignment()
types.set('A', 'double')
types.set('B', 'double')
types.set('x', 'double')
types.set('n', 'int')

instance = create_instance(pattern, var_map, types=types)
print(instance.pprint())

init_value_map = {
    'A': 'drand(0.0, 1.0)',
    'B': 'drand(0.0, 1.0)',
    'x': 'drand(0.0, 1.0)',
    'n': 'n_elements',
}


application = 'LoopGen'
batch = f'lore'
code_prefix = f'S254'
code = f'{code_prefix}.c'
codelet = f'{code_prefix}.c_de'
n_iterations = 10
n_elements = artificial_size_limit

generate_codelet_full('LoopGen', batch, code, codelet,
                      n_iterations, n_elements, instance, init_value_map)
