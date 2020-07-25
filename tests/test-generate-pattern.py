import os
from loguru import logger
from pathlib import Path
from abstract_ast import Declaration
from pattern_generator import generate, PatternInfo
from variable_map import validate_var_map, VariableMap, create_instance
from parser import parse_file
from codegen import CodeGen

def create_pattern_info(n_stmts, n_ops):
    mul_consts = ['a1', 'a2', 'a3']
    add_consts = ['b1', 'b2', 'b3']
    data_consts = ['f1', 'f2', 'f3']
    loop_vars = ['i1', 'i2', 'i3', 'i4', 'i5', 'i6']
    decls = [
        Declaration('A', 1),
        Declaration('B', 1),
        Declaration('C', 1),
        Declaration('D', 1),
        Declaration('E', 1),
    ]
    ops = ['+', '*', '-']
    n_loops = 5
    n_depth = 3
    # n_stmts = 2
    # n_ops = 1
    pattern_info = PatternInfo(decls, mul_consts, add_consts,
                               data_consts, ops,
                               loop_vars, n_loops,
                               n_depth, n_stmts, n_ops)
    return pattern_info

# 1 stmts * 10 ops = 12 access pairs per  loop
# 2 stmts * 1 ops = 12 access pairs per loop
# for n_stmts in range(2, 10):
#     estimate = [estimate_n_access_pairs(1, n_stmts, n_ops) for n_ops in range(1, 20)]
#     print(' '.join(map(str, estimate)))
def estimate_n_access_pairs(n_loops, n_stmts, n_ops):
    n_rhs_leaves_per_stmt = n_ops + 1
    n_leaves_per_stmt = n_rhs_leaves_per_stmt + 1
    n_leaves_per_loop = n_stmts * n_leaves_per_stmt
    n_lhs_leaves_per_loop = n_stmts
    n_access_pairs_per_loop = n_lhs_leaves_per_loop * n_leaves_per_loop
    n_access_pairs_per_program = n_loops * n_access_pairs_per_loop
    return n_access_pairs_per_program

output_root = 'generated-patterns'

def generate_patterns(n_patterns, output_dir, pattern_info):
    Path(output_dir).mkdir(parents=True, exist_ok=True)
    for p in range(n_patterns):
        pattern_path = os.path.join(output_dir, f'p{p:04d}.pattern')
        pattern, _ = generate(pattern_info)
        with open(pattern_path, 'w') as f:
            f.write(pattern.pprint())
        # TODO: write pattern info file

pattern_info_1 = create_pattern_info(1, 10)
pattern_dir_1 = os.path.join(output_root, 'pattern_1')
# generate_patterns(10,
#                   pattern_dir_1,
#                   pattern_info_1)

pattern_info_2 = create_pattern_info(2, 1)
pattern_dir_2 = os.path.join(output_root, 'pattern_2')
generate_patterns(10,
                  pattern_dir_2,
                  pattern_info_2)

pattern_info_3 = create_pattern_info(1, 1)
pattern_dir_3 = os.path.join(output_root, 'pattern_3')
# generate_patterns(1,
#                   pattern_dir_3,
#                   pattern_info_3)

# TODO: read pattern info
def generate_programs(pattern_dir, pattern_info, output_dir):
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

    codegen = CodeGen(output_dir)
    patterns_map = {}
    patterns = [f for f in os.listdir(pattern_dir) if f.endswith('.pattern')]
    for filename in patterns:
        pattern_name = filename[:filename.index('.pattern')]

        path = os.path.join(pattern_dir, filename)
        pattern, _ = parse_file(path)
        validate_var_map(pattern, var_map)

        patterns_map[pattern_name] = {}

        for i in range(2):
            instance, var_map = create_instance(pattern, var_map)
            instance_name = f'i{i:04d}'
            codegen.generate_wrapper(pattern_name, instance_name, instance, var_map)
            patterns_map[pattern_name][instance_name] = []

            mutation_name = 'mutation'
            codegen.generate_code(pattern_name, instance_name, mutation_name, instance, var_map)
            patterns_map[pattern_name][instance_name].append(mutation_name)
    codegen.generate_pattern_file(patterns_map)

output_dir = 'debug'
generate_programs(pattern_dir_2, pattern_info_2, output_dir)
