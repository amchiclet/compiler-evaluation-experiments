from parser import parse_str
from dependence_analysis import analyze_dependence
from variable_map import VariableMap, create_instance, validate_var_map
from codegen import CodeGen
from pattern_generator import generate_pattern, PatternInfo, write_patterns_to_dir
from loguru import logger
from abstract_ast import Declaration
from log_util import init_logger
from transformers.loop_unroll import LoopUnroll

def create_pattern_info():
    mul_consts = ['a1', 'a2', 'a3']
    add_consts = ['b1', 'b2', 'b3']
    data_consts = ['f1', 'f2', 'f3']
    loop_vars = ['i1', 'i2', 'i3']
    decls = [
        Declaration('A', 1),
        Declaration('B', 1),
        Declaration('C', 1),
        Declaration('D', 1),
        Declaration('E', 1),
    ]
    ops = ['+', '*', '-']
    n_loops = 1
    n_depth = 1
    n_stmts = 3
    n_ops = 4
    pattern_info = PatternInfo(decls, mul_consts, add_consts,
                               data_consts, ops,
                               loop_vars, n_loops,
                               n_depth, n_stmts, n_ops)
    return pattern_info

def create_var_map():
    var_map = VariableMap(default_max=20000000)
    for v in ['a1', 'a2', 'a3']:
        var_map.set_min(v, 0)
        var_map.set_max(v, 2)
    for v in ['b1', 'b2', 'b3']:
        var_map.set_min(v, 0)
        var_map.set_max(v, 16)
    for v in ['i1', 'i2', 'i3']:
        var_map.set_min(f'{v}_greater_eq', 1000000)
        var_map.set_max(f'{v}_greater_eq', 2000000)
        var_map.set_min(f'{v}_less_eq', 3000000)
        var_map.set_max(f'{v}_less_eq', 4000000)
    for v in ['f1', 'f2', 'f3']:
        var_map.set_min(v, 0.5)
        var_map.set_max(v, 2.0)
    return var_map


n_patterns = 125
n_instances = 2
n_mutations = 4
attempt = 0

root_dir = f'unroll.{n_patterns}.{n_instances}.{n_mutations}.{attempt}'
pattern_dir = f'{root_dir}/patterns'
instance_dir = f'{root_dir}/instances'
code_dir = f'{root_dir}/code'
codegen = CodeGen(code_dir)
init_logger(f'{root_dir}/generate.log', True)

pattern_info = create_pattern_info()
var_map = create_var_map()
pattern_name_pairs = []

max_factor = 16
assert(max_factor >= n_mutations)
loop_unroll = LoopUnroll(max_factor)
patterns = {}
for p in range(n_patterns):
    pattern = generate_pattern(pattern_info, var_map)
    if pattern is None:
        continue
    pattern_name = f'p{p:03d}'

    instances = {}
    while len(instances) < n_instances:
        instance = create_instance(pattern, var_map)

        if instance is None:
            continue

        mutation_names = []
        mutations = []
        while len(mutations) < n_mutations:
            mutation = next(loop_unroll.transform(instance))
            mutation_name = f'm{len(mutations):02d}'
            is_duplicate = False
            for existing_mutation in mutations:
                if existing_mutation.pattern.is_syntactically_equal(mutation.pattern):
                    is_duplicate = True
                    break
            if is_duplicate:
                print('found duplicate trying again')
                continue
            mutation_names.append(mutation_name)
            mutations.append(mutation)

        instance_name = f'i{len(instances):02d}'
        codegen.generate_wrapper(pattern_name, instance_name, instance)
        for mutation, mutation_name in zip(mutations, mutation_names):
            codegen.generate_code(pattern_name, instance_name, 
                                  mutation_name, mutation)

        instances[instance_name] = mutation_names

    patterns[pattern_name] = instances
    pattern_name_pairs.append((pattern, pattern_name))

write_patterns_to_dir(pattern_name_pairs, pattern_dir)
codegen.generate_pattern_file(patterns)

print(patterns)
