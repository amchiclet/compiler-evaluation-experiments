import os
import random
from parser import parse_file
from transformers.loop_interchange import LoopInterchange
from variable_map import VariableMap, validate_var_map, create_instance
from codegen import CodeGen
from multiprocessing import Pool

output_dir = 'delete-me'
from loguru import logger
import sys
logger.remove()
logger.add(sys.stdout, level='INFO')
logger.add(sink = f'{output_dir}/many-patterns.log',
           level = 'INFO',
           format = ('{process.name} | '
                     '{time:YYYYMMDD_HH:mm:ss.SSS} | '
                     '{file}:{function}:{line} | '
                     '{message}'),
           enqueue = True)

def get_patterns(root_dir):
    patterns = []
    for pattern in os.listdir(root_dir):
        full_path = os.path.join(root_dir, pattern)
        if os.path.isfile(full_path) and full_path.endswith('.loop'):
            patterns.append(pattern)
    return patterns

def get_random_pattern(pattern_dir):
    patterns = get_patterns(pattern_dir)
    n_chosen_patterns = 5
    chosen = random.choices(patterns, k=n_chosen_patterns)
    merged = None
    node_id = 0
    for rel_path in chosen:
        pattern_path = os.path.join(pattern_dir, rel_path)
        program, node_id = parse_file(pattern_path, node_id)
        if merged:
            merged.merge(program)
        else:
            merged = program
    return merged

from functools import partial

def generate_instance(pattern, pattern_str, var_map, codegen, transformer, ith_instance):
    result = create_instance(pattern, var_map)
    if result is None:
        return None
    instance, instance_var_map = result
    instance_str = f'i{ith_instance:04d}'
    mutation_strs = []
    codegen.generate_wrapper(pattern_str, instance_str, pattern, instance_var_map)
    ith_mutation = 0
    for mutation in transformer.transform(pattern, instance_var_map):
        mutation_str = f'm{ith_mutation:04d}'
        mutation_strs.append(mutation_str)
        codegen.generate_code(pattern_str, instance_str, mutation_str,
                              mutation, instance_var_map)
        ith_mutation += 1
        if ith_mutation == n_mutations:
            break
    return (instance_str, mutation_strs)

def generate_mutations(pattern_dir, output_dir, var_map, n_patterns, n_instances, n_mutations):
    patterns_map = {}
    codegen = CodeGen(output_dir)
    for ith_pattern in range(n_patterns):
        pattern = get_random_pattern(pattern_dir)
        loop_interchange = LoopInterchange()
        pattern_str = f'p{ith_pattern:04d}'
        logger.info(f'Pattern {pattern_str}:\n'
                    f'{pattern.pprint()}')
        pool = Pool()
        f = partial(generate_instance, pattern, pattern_str, var_map, codegen, loop_interchange)
        patterns_map[pattern_str] = {}
        instances = pool.map(f, range(n_instances))
        instances[:] = [i for i in instances if i is not None]
        for instance, mutations in instances:
            patterns_map[pattern_str][instance] = mutations

    codegen.generate_pattern_file(patterns_map)

pattern_dir = os.path.abspath('loops/lore')

n_patterns = 10
n_instances = 10
n_mutations = 10

default_min = 0
default_max = 255
var_map = VariableMap(default_min, default_max)

generate_mutations(pattern_dir, output_dir, var_map, n_patterns, n_instances, n_mutations)
