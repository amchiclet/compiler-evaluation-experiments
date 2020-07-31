from pattern_info_factory import create_pattern_info
from variable_map import VariableMap, validate_var_map, create_instance
import os
from parser import parse_file
from codegen import CodeGen
from transformers.loop_interchange import LoopInterchange
from multiprocessing import Pool
from functools import partial
from random import shuffle

def create_var_map(pattern_info):
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
    return var_map

def get_paths_and_names(pattern_dir):
    paths_and_names = []
    for f in os.listdir(pattern_dir):
        if f.endswith('.pattern'):
            path = os.path.join(pattern_dir, f)
            name = f[:f.index('.pattern')]
            paths_and_names.append((path, name))
    return paths_and_names

def validate_pattern(var_map, path_and_name):
    path, name = path_and_name
    pattern, _ = parse_file(path)

    if validate_var_map(pattern, var_map):
        return (pattern, name)
    return None

def validate_patterns(var_map, paths_and_names, n_patterns):
    patterns_and_names = []

    validate_one = partial(validate_pattern, var_map)
    worklist = list(paths_and_names)
    while len(patterns_and_names) < n_patterns and len(worklist) > 0:
        n_needed = n_patterns - len(patterns_and_names)
        batch = worklist[:n_needed]
        worklist[:] = worklist[n_needed:]

        with Pool() as p:
            result = p.map(validate_one, batch)
            patterns_and_names += [i for i in result if i is not None]

    return patterns_and_names

def generate_code_instance(codegen, var_map, n_mutations,
                           pattern, pattern_name, instance_name):
    instance, instance_var_map = create_instance(pattern, var_map)

    codegen.generate_wrapper(pattern_name, instance_name, instance, instance_var_map)

    mutations = []

    loop_interchange = LoopInterchange()
    m = 0
    for mutation in loop_interchange.transform(instance, instance_var_map):
        mutation_name = f'm{m:04d}'
        mutations.append(mutation_name)
        codegen.generate_code(pattern_name, instance_name, 
                              mutation_name, mutation,
                              instance_var_map)
        m += 1
        if m == n_mutations:
            break
    return (instance_name, mutations)

def generate_code_pattern(patterns_and_names, var_map, n_instances, n_mutations, output_dir):
    codegen = CodeGen(output_dir)

    patterns_map = {}
    for pattern, pattern_name in patterns_and_names:
        patterns_map[pattern_name] = {}

        instance_names = [f'i{i:04d}' for i in range(n_instances)]
        with Pool() as p:
            f = partial(generate_code_instance, codegen, var_map,
                        n_mutations, pattern, pattern_name)
            pairs = p.map(f, instance_names)
            for (instance_name, mutations) in pairs:
                patterns_map[pattern_name][instance_name] = mutations

    codegen.generate_pattern_file(patterns_map)

from loguru import logger
import sys
logger.remove()
logger.add(sys.stdout, level='INFO')
logger.add(sink = f'read-patterns.log',
           level = 'INFO',
           format = ('{process.name} | '
                     '{time:YYYYMMDD_HH:mm:ss.SSS} | '
                     '{file}:{function}:{line} | '
                     '{message}'),
           enqueue = True)

n_patterns = 1
n_instances = 1
n_mutations = 2

pattern_root = 'generated-patterns'

pattern_shapes = ((1, 27), (2, 5), (3, 1))
for pattern_shape in pattern_shapes:
    n_stmts, n_ops = pattern_shape
    pattern_info = create_pattern_info(n_stmts, n_ops)
    var_map = create_var_map(pattern_info)
    pattern_dir = os.path.join(pattern_root, f'gen_{n_stmts}_{n_ops}')
    paths_and_names = get_paths_and_names(pattern_dir)
    shuffle(paths_and_names)
    patterns_and_names = validate_patterns(var_map, paths_and_names, n_patterns)
    output_dir = f'output_{n_stmts}_{n_ops}'
    codegen = CodeGen(output_dir)
    generate_code_pattern(patterns_and_names, var_map, n_instances, n_mutations, output_dir)

