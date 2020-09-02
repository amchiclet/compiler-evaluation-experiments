from parser import parse_str
from dependence_analysis import analyze_dependence
from variable_map import VariableMap, create_instance, validate_var_map
from codegen import CodeGen
from pattern_generator import generate_pattern, PatternInfo, write_patterns_to_dir
from loguru import logger
from abstract_ast import Declaration
from log_util import init_logger

def create_pattern_info():
    mul_consts = ['a1', 'a2', 'a3']
    add_consts = ['b1', 'b2', 'b3']
    data_consts = ['f1', 'f2', 'f3']
    loop_vars = ['i1', 'i2', 'i3']
    decls = [
        Declaration('A', 3),
        Declaration('B', 3),
        Declaration('C', 3),
        Declaration('D', 3),
        Declaration('E', 3),
    ]
    ops = ['+', '*', '-']
    n_loops = 1
    n_depth = 3
    n_stmts = 2
    n_ops = 1
    pattern_info = PatternInfo(decls, mul_consts, add_consts,
                               data_consts, ops,
                               loop_vars, n_loops,
                               n_depth, n_stmts, n_ops)
    return pattern_info

def create_var_map():
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
    for v in ['f1', 'f2', 'f3']:
        var_map.set_min(v, 0.5)
        var_map.set_max(v, 2.0)
    return var_map

from transformers.loop_interchange import LoopInterchange


root_dir = f'exp.10.10.6.2'
pattern_dir = f'{root_dir}/temp-generated-patterns'
output_dir = f'{root_dir}/temp-generated-code'
codegen = CodeGen(output_dir)
init_logger(f'{root_dir}/end-to-end.log', True)

pattern_info = create_pattern_info()
var_map = create_var_map()
max_patterns = 10
max_instances = 10
max_mutations = 6
pattern_name_pairs = []
patterns = {}
for p in range(max_patterns):
    pattern = generate_pattern(pattern_info, var_map)
    if pattern is None:
        continue
    pattern_name = f'p{p:02d}'

    instances = {}
    for i in range(max_instances):
        instance = create_instance(pattern, var_map)
        if instance is None:
            continue
        instance_name = f'i{i:02d}'
        codegen.generate_wrapper(pattern_name, instance_name, instance)
        loop_interchange = LoopInterchange()
        mutations = []
        for m in range(max_mutations):
            mutation = next(loop_interchange.transform(instance))
            mutation_name = f'm{m:02d}'
            mutations.append(mutation_name)
            codegen.generate_code(pattern_name, instance_name, 
                                  mutation_name, mutation)

        instances[instance_name] = mutations

    patterns[pattern_name] = instances
    pattern_name_pairs.append((pattern, pattern_name))

write_patterns_to_dir(pattern_name_pairs, pattern_dir)
codegen.generate_pattern_file(patterns)

print(patterns)
