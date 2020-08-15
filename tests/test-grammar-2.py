from parser import parse_str
from dependence_analysis import analyze_dependence
from variable_map import VariableMap, create_instance, validate_var_map
from codegen import CodeGen

from loguru import logger
import sys
logger.remove()
logger.add(sys.stdout, level='INFO')
logger.add(sink = f'test-grammar-2.log',
           level = 'INFO',
           format = ('{process.name} | '
                     '{time:YYYYMMDD_HH:mm:ss.SSS} | '
                     '{file}:{function}:{line} | '
                     '{message}'),
           enqueue = True)

code = """
declare a[];
for [(i,+=2)] {
  a[i] = a[i-2];
}
"""

code = """
declare A[];
declare B[];
declare C[];
for [i1, i2, i3] {
  A[a1 * i3 - b1] = A[a2 * i1 - b2] + f1;
  B[a1 * i3 - b3] = C[a3 * i3 + b3] * B[a1 * i3 - b3];
  B[a3 * i3 - b2] = B[a3 * i1 - b2] * f1;
}
"""
ast, _ = parse_str(code)
print(ast.pprint())
var_map = VariableMap()
for v in ['a1', 'a2', 'a3']:
    var_map.set_min(v, 0)
    var_map.set_max(v, 2)
for v in ['b1', 'b2', 'b3']:
    var_map.set_min(v, 0)
    var_map.set_max(v, 16)
for v in ['i1', 'i2', 'i3']:
    var_map.set_min(f'{v}_greater_eq', 100)
    var_map.set_max(f'{v}_greater_eq', 200)
    var_map.set_min(f'{v}_less_eq', 200)
    var_map.set_max(f'{v}_less_eq', 300)

print(var_map.pprint())
print(validate_var_map(ast, var_map))
instance = create_instance(ast, var_map)
print(instance.pprint())
# dep_graph = analyze_dependence(instance.pattern)
# print(dep_graph.pprint())

# codegen = CodeGen('temp')
# codegen.generate_wrapper('p0', 'i0', instance)
# codegen.generate_code('p0', 'i0', 'm0', instance)

# patterns_map = {'p0':{'i0':['m0']}}
# codegen.generate_pattern_file(patterns_map)
