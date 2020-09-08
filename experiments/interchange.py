from parser import parse_str
from dependence_analysis import analyze_dependence
from variable_map import VariableMap, create_instance, validate_var_map
from codegen import CodeGen
from pattern_generator import generate_pattern, PatternInfo, write_patterns_to_dir
from loguru import logger
from abstract_ast import Declaration
from log_util import init_logger
from transformers.loop_interchange import LoopInterchange
from multiprocessing import Pool
import copy
import sys
import tqdm
from pathlib import Path

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
    if pattern is None:
        return None

    instances = {}
    max_tries = 3
    n_tries = 0
    while len(instances) < n_instances and n_tries < max_tries:
        instance = create_instance(pattern, var_map, l=pattern_logger)

        if instance is None:
            n_tries += 1
            continue

        instance_name = f'i{len(instances):02d}'
        codegen.generate_wrapper(pattern_name, instance_name, instance, l=pattern_logger)

        mutations = []
        mutation_names = []

        for m in range(n_mutations):
            mutation = next(loop_interchange.transform(instance))
            mutation_name = f'm{m:02d}'
            mutations.append(mutation)
            mutation_names.append(mutation_name)
            codegen.generate_code(pattern_name, instance_name, 
                                  mutation_name, mutation, l=pattern_logger)

        original_mutation = None
        found_diff = False
        for m in mutations:
            if original_mutation is None:
                original_mutation = m
            else:
                if not original_mutation.pattern.is_syntactically_equal(m.pattern):
                    found_diff = True
                    break

        # Enforce that at least two mutations are different
        if not found_diff:
            n_tries += 1
            pattern_logger.warning(f'All mutations are the same. Retry #{n_tries} for {pattern_name}.{instance_name}')
            continue

        # Found a valid instance, resetting n_tries
        n_tries = 0
        instances[instance_name] = mutation_names

    if len(instances) < n_instances:
        pattern_logger.warning(f'Not enough instances for {pattern_name}. Retrying.')
        return None
    return (pattern_name, pattern, instances)

n_patterns = 200
n_instances = 2
n_mutations = 4

root_dir = f'interchange.{n_patterns}.{n_instances}.{n_mutations}'
pattern_dir = f'{root_dir}/patterns'
code_dir = f'{root_dir}/code'
codegen = CodeGen(code_dir)
# init_logger(f'{root_dir}/end-to-end.log', True)

pattern_info = create_pattern_info()
var_map = create_var_map()

loop_interchange = LoopInterchange()

pattern_name_pairs = []
patterns = {}

# This needs to be called for the generate function to work with multiprocessing
logger.remove()

remaining_patterns = set([f'p{p:03d}' for p in range(200)])

with Pool() as pool:
    while len(remaining_patterns) > 0:
        new_patterns = pool.map(generate, remaining_patterns)
        for triplet in new_patterns:
            if triplet is None:
                continue
            pattern_name, pattern, instances = triplet
            patterns[pattern_name] = instances
            pattern_name_pairs.append((pattern, pattern_name))
            remaining_patterns.remove(pattern_name)

    write_patterns_to_dir(pattern_name_pairs, pattern_dir)
    codegen.generate_pattern_file(patterns)

print(patterns)
