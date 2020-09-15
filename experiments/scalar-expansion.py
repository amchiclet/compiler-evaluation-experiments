from parser import parse_str
from dependence_analysis import analyze_dependence
from variable_map import VariableMap, create_instance, validate_var_map, Error, dimension_var
from codegen import CodeGen
from pattern_generator import generate_pattern, PatternInfo, write_patterns_to_dir
from loguru import logger
from abstract_ast import Declaration
from log_util import init_logger
from transformers.scalar_expansion import SimpleScalarExpansion, array_name
from multiprocessing import Pool
from pathlib import Path
import copy
from random import randint

def create_pattern_info():
    mul_consts = ['a1', 'a2', 'a3']
    maybe_zero_mul_consts = ['z']
    add_consts = ['b1', 'b2', 'b3']
    data_consts = ['f1', 'f2', 'f3']
    loop_vars = ['i1', 'i2', 'i3']
    decls = [
        Declaration('A', 1),
        Declaration('B', 1),
        Declaration('C', 1),
        Declaration('D', 1),
        Declaration('E', 1),
        Declaration('F', 1),
        Declaration('G', 1),
        Declaration('s1', 0, True),
        Declaration('s2', 0, True),
        Declaration('s3', 0, True),
        Declaration('s4', 0, True),
    ]
    ops = ['+', '*', '-']
    n_loops = 1
    n_depth = 1
    n_stmts = 10
    n_ops = 1
    pattern_info = PatternInfo(decls, mul_consts, add_consts,
                               data_consts, ops,
                               loop_vars, n_loops,
                               n_depth, n_stmts, n_ops,
                               maybe_zero_mul_consts)
    return pattern_info

def create_var_map(pattern_info):
    var_map = VariableMap(default_max=20000000)
    for v in ['a1', 'a2', 'a3']:
        var_map.set_min(v, 1)
        var_map.set_max(v, 3)
    for v in ['z']:
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

    for decl in pattern_info.decls:
        if decl.n_dimensions == 0:
            if decl.is_local:
                n_depth = 1
                for dim in range(n_depth):
                    v = dimension_var(array_name(decl.name), dim)
                    var_map.set_min(v, 4000000 * 3 + 16 + 1 + randint(0, 16))
        else:
            for dim in range(decl.n_dimensions):
                v = dimension_var(decl.name, dim)
                var_map.set_min(v, 4000000 * 3 + 16 + 1 + randint(0, 16))

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

def generate_instances(pattern_name, pattern, var_map, pattern_logger):
    instances = {}
    max_tries = 3
    n_tries = 0
    while len(instances) < n_instances and n_tries < max_tries:
        instance = create_instance(pattern, var_map, l=pattern_logger)

        if instance is None:
            n_tries += 1
            continue

        if instance == Error.Z3_BUG:
            break

        instance_name = f'i{len(instances):02d}'
        codegen.generate_wrapper(pattern_name, instance_name, instance, l=pattern_logger)

        mutations = []
        mutation_names = []

        no_mutation = False
        for m in range(n_mutations):
            mutation = next(scalar_expansion.transform(instance, var_map))
            if mutation is None:
                no_mutation = True
                break
            if mutation == Error.Z3_BUG:
                return None
            mutation_name = f'm{m:02d}'
            mutations.append(mutation)
            mutation_names.append(mutation_name)
            codegen.generate_code(pattern_name, instance_name, 
                                  mutation_name, mutation, l=pattern_logger)

        # Enforce that at least two mutations are different
        if no_mutation:
            n_tries += 1
            pattern_logger.warning(f'An error occurred while creating mutations')
            continue

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
    return instances

def generate(pattern_name):
    print(pattern_name)
    pattern = generate_pattern(pattern_info, var_map)
    pattern_logger = get_logger(pattern_name)
    if pattern is None:
        return None
    instances = generate_instances(pattern_name, pattern, var_map, pattern_logger)
    if instances is None:
        return None
    return (pattern_name, pattern, instances)

n_patterns = 10
n_instances = 2
n_mutations = 4

root_dir = f'scalar-expansion.{n_patterns}.{n_instances}.{n_mutations}'
pattern_dir = f'{root_dir}/patterns'
code_dir = f'{root_dir}/code'
codegen = CodeGen(code_dir)

pattern_info = create_pattern_info()
var_map = create_var_map(pattern_info)
print(var_map.pprint())
scalar_expansion = SimpleScalarExpansion()

pattern_name_pairs = []
patterns = {}

# This needs to be called for the generate function to work with multiprocessing
logger.remove()

remaining_patterns = set([f'p{p:03d}' for p in range(n_patterns)])

# for p in remaining_patterns:
#     generate(p)

# exit(0)
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
