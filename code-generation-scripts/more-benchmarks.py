from pattern import parse_str as parse_pattern
from instance import create_instance
from constant_assignment import VariableMap
from type_assignment import TypeAssignment
from codegen.c_generator import generate_code
from codelet_generator import generate_codelet_full, name

nrm261 = """
declare grid_points[3];
declare add;
declare rhs[64 / 2 * 2 + 1][64 / 2 * 2 + 1][64 / 2 * 2 + 1][5];
declare rms[5];

for [(i, >=1, <=grid_points[0]-2), 
     (j, >=1, <=grid_points[1]-2),
     (k, >=1, <=grid_points[2]-2),
     (m, >=0, <=4)] {
  add = rhs[i][j][k][m];
  rms[m] = rms[m] + add * add;
}
"""

cnv243 = """
declare tmort[92700];
declare mormult[92700];
declare nmor;

for [(i, >=0, <=nmor-1)] {
  tmort[i] = tmort[i] / mormult[i];
}
"""

s242 = """
declare a[32000];
declare s1;
declare s2;
declare b[32000];
declare c[32000];
declare d[32000];

for [(i, >=1, <=31999)] {
  a[i] = a[i-1] + s1 + s2 + b[i] + c[i] + d[i];
}
"""

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
