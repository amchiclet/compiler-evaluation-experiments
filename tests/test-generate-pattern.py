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
    n_loops = 1
    n_depth = 1
    n_stmts = 1
    n_ops = 1
    pattern_info = PatternInfo(decls, mul_consts, add_consts,
                               data_consts, ops,
                               loop_vars, n_loops,
                               n_depth, n_stmts, n_ops)
    return pattern_info

pattern_info = create_pattern_info()
pattern, _ = generate(pattern_info)
from loguru import logger
logger.info(pattern.pprint())

from variable_map import validate_var_map, VariableMap, create_instance

var_map = VariableMap(default_min=0, default_max=64)
for mul_const in pattern_info.mul_consts:
    var_map.set_min(mul_const, 0)
    var_map.set_max(mul_const, 2)
for add_const in pattern_info.add_consts:
    var_map.set_min(add_const, 0)
    var_map.set_max(add_const, 16)
for data_const in pattern_info.data_consts:
    var_map.set_min(data_const, 0)
    var_map.set_max(data_const, 128)
validate_var_map(pattern, var_map)

logger.info('Valid pattern')

pattern, var_map = create_instance(pattern, var_map)

from codegen import CodeGen

output_dir = 'generated-pattern'
codegen = CodeGen(output_dir)
patterns_map = {'p': {'i': ['m']}}
codegen.generate_wrapper('p', 'i', pattern, var_map)
codegen.generate_code('p', 'i', 'm', pattern, var_map)
codegen.generate_pattern_file(patterns_map)

print(pattern.pprint())
print(var_map.pprint())
logger.info('This is a valid var map')
