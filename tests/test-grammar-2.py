from parser import parse_str
from dependence_analysis import analyze_dependence
from variable_map import VariableMap, create_instance

code = """
declare a[];
for [i] {
  a[i] = a[i-1];
}
"""
ast, _ = parse_str(code)
print(ast.pprint())
var_map = VariableMap()
pattern, var_map = create_instance(ast, var_map)
print(pattern.pprint())
# dep_graph = analyze_dependence(ast, var_map)
# print(dep_graph.pprint())

# TODO: make sure greater_eq is less than less_eq
#       use step as the step in dependence analysis
