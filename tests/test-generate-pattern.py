from abstract_ast import Declaration
from pattern_generator import generate, PatternInfo
from pattern_normalizer import normalize_pattern
def create_pattern_info() :
    mul_consts = ['a', 'b', 'c', 'd', 'e']
    add_consts = ['x', 'y']
    data_consts = ['f', 'g']
    loop_vars = ['i', 'j', 'k', 'l', 'm']
    decls = [
        Declaration('A', 2),
        Declaration('B', 2),
        Declaration('C', 2),
    ]
    ops = ['+', '*', '-']
    n_loops = 3
    n_depth = 3
    n_stmts = 2
    n_ops = 3
    pattern_info = PatternInfo(decls, mul_consts, add_consts,
                               data_consts, ops,
                               loop_vars, n_loops,
                               n_depth, n_stmts, n_ops)
    return pattern_info

pattern_info = create_pattern_info()
pattern, _ = generate(pattern_info)
print(pattern.pprint())

from variable_map import validate_var_map, VariableMap
var_map = VariableMap(default_min=0, default_max=64)
validate_var_map(pattern, var_map)

# # print(node.pprint())
# from pathlib import Path
# output_dir = 'generated-patterns'
# Path(output_dir).mkdir(parents=True, exist_ok=True)
