from parser import parse_str
from dependence_analysis import analyze_dependence
from variable_map import VariableMap, create_instance, validate_var_map
from codegen import CodeGen

code = """
declare a[];
for [(i,+=2)] {
  a[i] = a[i-2];
}
"""
ast, _ = parse_str(code)
print(ast.pprint())
var_map = VariableMap()
print(var_map.pprint())
print(validate_var_map(ast, var_map))
instance = create_instance(ast, var_map)
print(instance.pprint())
dep_graph = analyze_dependence(instance.pattern)
print(dep_graph.pprint())

codegen = CodeGen('temp')
codegen.generate_wrapper('p0', 'i0', instance)
codegen.generate_code('p0', 'i0', 'm0', instance)

patterns_map = {'p0':{'i0':['m0']}}
codegen.generate_pattern_file(patterns_map)
