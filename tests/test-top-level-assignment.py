from loguru import logger
from parser import parse_str
import sys
from dependence_analysis import analyze_dependence
logger.remove()
logger.add(sys.stdout, level='INFO')

code = """
declare a[];
declare b[];
a[0] = b[0];
a[1] = b[1];
a[2] = b[2];
a[3] = b[3];
for [i] {
  a[i] = b[i];
}
a[0] = b[0];
a[1] = b[1];
a[2] = b[2];
a[3] = b[3];
"""

program, node_id = parse_str(code)
print(program.pprint())

from variable_map import VariableMap, validate_var_map, randomize_iteration_vars
var_map = validate_var_map(program, VariableMap(0, 4))
print(var_map.pprint())
dep_graph = analyze_dependence(program, var_map)
print(dep_graph.pprint())
from codegen import CodeGen
codegen = CodeGen('test-top-level')
# codegen.generate_wrapper('p0', 'i0', program, var_map)
codegen.generate_code('p0', 'i0', 'm0', program, var_map)
# patterns_map = {
#     'p0': {'i0': ['m0']}
# }
# codegen.generate_pattern_file(patterns_map)
