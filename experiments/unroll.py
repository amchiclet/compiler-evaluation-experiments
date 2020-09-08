from parser import parse_str
from dependence_analysis import analyze_dependence
from variable_map import VariableMap, create_instance, validate_var_map
from codegen import CodeGen
from pattern_generator import generate_pattern, PatternInfo, write_patterns_to_dir
from loguru import logger
from abstract_ast import Declaration
from log_util import init_logger
from transformers.loop_unroll import LoopUnroll
from multiprocessing import Pool
from pathlib import Path
import copy

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

def get_logger(pattern_name):
    log_dir = f'{root_dir}/logs'
    Path(log_dir).mkdir(parents=True, exist_ok=True)
    pattern_log_path = f'{log_dir}/{pattern_name}.log'
    pattern_logger = copy.deepcopy(logger)
    pattern_logger.add(sink = pattern_log_path,
                       level = 'DEBUG',
                       format = ('{time:YYYYMMDD_HH:mm:ss.SSS} | '
                                 '{file}:{function}:{line} | '
                                 '{message}'))
    return pattern_logger

def generate(pattern_name):
    print(pattern_name)
    pattern = generate_pattern(pattern_info, var_map)
    pattern_logger = get_logger(pattern_name)
    assert(pattern is not None)

    instances = {}
    while len(instances) < n_instances:
        instance = create_instance(pattern, var_map, l=pattern_logger)

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
                pattern_logger.debug('found duplicate trying again')
                continue
            mutation_names.append(mutation_name)
            mutations.append(mutation)

        instance_name = f'i{len(instances):02d}'
        codegen.generate_wrapper(pattern_name, instance_name, instance, l=pattern_logger)
        for mutation, mutation_name in zip(mutations, mutation_names):
            codegen.generate_code(pattern_name, instance_name, 
                                  mutation_name, mutation, l=pattern_logger)

        instances[instance_name] = mutation_names
    return (pattern_name, pattern, instances)

n_patterns = 200
n_instances = 2
n_mutations = 4

root_dir = f'unroll.{n_patterns}.{n_instances}.{n_mutations}'
pattern_dir = f'{root_dir}/patterns'
code_dir = f'{root_dir}/code'
codegen = CodeGen(code_dir)

# This needs to be called for the generate function to work with multiprocessing
logger.remove()

pattern_info = create_pattern_info()
var_map = create_var_map()

max_factor = 16
assert(max_factor >= n_mutations)
loop_unroll = LoopUnroll(max_factor)

pattern_name_pairs = []
patterns = {}

with Pool() as pool:
    new_patterns = pool.map(generate, [f'p{p:03d}' for p in range(n_patterns)])
    for pattern_name, pattern, instances in new_patterns:
        patterns[pattern_name] = instances
        pattern_name_pairs.append((pattern, pattern_name))
    write_patterns_to_dir(pattern_name_pairs, pattern_dir)
    codegen.generate_pattern_file(patterns)

# for p in range(n_patterns):
#     new_pattern = generate(f'p{p:03d}')
#     pattern_name, pattern, instances = new_pattern
#     patterns[pattern_name] = instances
#     pattern_name_pairs.append((pattern, pattern_name))
# write_patterns_to_dir(pattern_name_pairs, pattern_dir)
# codegen.generate_pattern_file(patterns)

print(patterns)
