import os
from loguru import logger
from pathlib import Path
from abstract_ast import Declaration
from pattern_generator import generate, PatternInfo
from variable_map import validate_var_map, VariableMap, create_instance
from parser import parse_file
from codegen import CodeGen
from transformers.loop_interchange import LoopInterchange
from pattern_info_factory import create_pattern_info_v2

# 1 stmts * 10 ops = 12 access pairs per  loop
# 2 stmts * 1 ops = 12 access pairs per loop
# for n_stmts in range(2, 10):
#     estimate = [estimate_n_access_pairs(1, n_stmts, n_ops) for n_ops in range(1, 20)]
#     print(' '.join(map(str, estimate)))
def estimate_n_access_pairs_per_loop(n_stmts, n_ops):
    n_rhs_leaves_per_stmt = n_ops + 1
    n_leaves_per_stmt = n_rhs_leaves_per_stmt + 1
    n_leaves_per_loop = n_stmts * n_leaves_per_stmt
    n_lhs_leaves_per_loop = n_stmts
    n_access_pairs_per_loop = n_lhs_leaves_per_loop * n_leaves_per_loop
    return n_access_pairs_per_loop

output_root = 'generated-patterns'

def generate_patterns(n_patterns, output_dir, pattern_info):
    Path(output_dir).mkdir(parents=True, exist_ok=True)
    for p in range(n_patterns):
        pattern_path = os.path.join(output_dir, f'p{p:04d}.pattern')
        pattern, _ = generate(pattern_info)
        with open(pattern_path, 'w') as f:
            f.write(pattern.pprint())
        # TODO: write pattern info file

# 1 statement 27 ops = 27 access pairs
# 2 statements 5 ops = 28 access pairs
# 3 statements 1 ops = 27 access pairs
# pattern_shapes = ((1, 27), (2, 5), (3, 1))
pattern_shapes = [(3, 1)]
for pattern_shape in pattern_shapes:
    n_stmts, n_ops = pattern_shape
    pattern_info = create_pattern_info_v2(1, n_stmts, n_ops)
    pattern_dir = os.path.join(output_root, f'gen_{n_stmts}_{n_ops}')
    generate_patterns(10,
                      pattern_dir,
                      pattern_info)
