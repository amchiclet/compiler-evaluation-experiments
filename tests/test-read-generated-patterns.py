from pattern_info_factory import create_pattern_info_2
from variable_map import VariableMap, validate_var_map, create_instance
import os
from parser import parse_file
from codegen import CodeGen
from transformers.loop_interchange import LoopInterchange

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

def validate_patterns(paths_and_names, n_patterns):
    patterns_and_names = []
    for path, name in paths_and_names:
        pattern, _ = parse_file(path)
        if validate_var_map(pattern, var_map):
            patterns_and_names.append((pattern, name))
        if len(patterns_and_names) == n_patterns:
            break
    return patterns_and_names

def generate_mutations(patterns_and_names, n_instances, n_mutations, output_dir):
    codegen = CodeGen(output_dir)
    patterns_map = {}
    for pattern, pattern_name in patterns_and_names:
        patterns_map[pattern_name] = {}
        for i in range(n_instances):
            instance, instance_var_map = create_instance(pattern, var_map)
            instance_name = f'i{i:04d}'
            codegen.generate_wrapper(pattern_name, instance_name, instance, instance_var_map)
            patterns_map[pattern_name][instance_name] = []

            loop_interchange = LoopInterchange()
            m = 0
            for mutation in loop_interchange.transform(instance, instance_var_map):
                mutation_name = f'm{m:04d}'
                patterns_map[pattern_name][instance_name].append(mutation_name)
                codegen.generate_code(pattern_name, instance_name, 
                                      mutation_name, mutation,
                                      instance_var_map)
                m += 1
                if m == n_mutations:
                    break
    codegen.generate_pattern_file(patterns_map)

n_patterns = 2
n_instances = 2
n_mutations = 2
pattern_info = create_pattern_info_2()
var_map = create_var_map(pattern_info)
paths_and_names = get_paths_and_names('generated-patterns/pattern_2')
patterns_and_names = validate_patterns(paths_and_names, n_patterns)
output_dir = 'generated-output'
generate_mutations(patterns_and_names, n_instances, n_mutations, output_dir)

