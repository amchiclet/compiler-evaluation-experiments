from loguru import logger
from parser import parse_str
import sys

logger.remove()
logger.add(sys.stdout, level='INFO')

code = """
declare a[];
declare b[];
declare s;
for [i] {
  a[i] = s * a[i];
}
"""

program, node_id = parse_str(code)
print(program.pprint())

from variable_map import VariableMap, validate_var_map, randomize_iteration_vars
var_map = validate_var_map(program, VariableMap(0, 256))
print(var_map.pprint())

from codegen import CodeGen
codegen = CodeGen('test-scalar')
codegen.generate_wrapper('p0', 'i0', program, var_map)
codegen.generate_code('p0', 'i0', 'm0', program, var_map)
patterns_map = {
    'p0': {'i0': ['m0']}
}
codegen.generate_pattern_file(patterns_map)
