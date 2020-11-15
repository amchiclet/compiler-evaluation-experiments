from parser import parse_file, parse_str
from loguru import logger
from dependence_analysis import analyze_dependence
from variable_map import VariableMap, validate_var_map, create_instance
from abstract_ast import Replacer, Access, Literal
from codegen import CodeGen

#34.142

# TODO:
# constants allowed in all places
# 2i + 3j ...
# generalize binop to be just op
program_str = """
declare a[1200][1100];
local b;
declare c;

for [i, j] {
  a[i][j] = a[i-1][j] + 2.0;
}
"""
# import sys
# logger.remove()
# logger.add(sys.stdout, level='INFO')

program, _ = parse_str(program_str)
logger.info(program.pprint())
var_map = VariableMap()
instance = create_instance(program, var_map)
logger.info(instance.pprint())

codegen = CodeGen('new-instance')
codegen.generate_wrapper('p00', 'i00', instance)

# graph = analyze_dependence(program, var_map)
# graph.debug()

# validated = validate_var_map(program, var_map)

# class AssignConsts(Replacer):
#     def __init__(self, replace_map):
#         self.replace_map = replace_map
#     def should_replace(self, node):
#         return type(node) == Access and node.var in replace_map
#     def replace(self, node):
#         return Literal(int, replace_map[node.var], node.node_id)

# replace_map = {'b': 5}
# replacer = AssignConsts(replace_map)
# program.replace(replacer)
# logger.info(program.pprint())
