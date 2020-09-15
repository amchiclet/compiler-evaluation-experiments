from loguru import logger
from parser import parse_str
import sys
from log_util import init_logger
from transformers.scalar_expansion import SimpleScalarExpansion
from variable_map import VariableMap, create_instance
from codegen import CodeGen

base_dir = 'test-scalar-expansion'
init_logger(f'{base_dir}/main.log', True)

code = """
declare a[];
local b[];
declare s1;
local s2;
local s3;
for [i, j] {
  s1 = a[i] * 1.1;
  a[i] = s2 * 2.2;
  s2 = a[i] * 3.3;
  s3 = a[i] * s1;
}
"""

# code = """
# declare a[];
# local b[];
# declare s1;
# local s2;
# local s3;
# for [i] {
#   s1 = a[i] * 1.1;
# }
# """

program, node_id = parse_str(code)
print(program.pprint())

var_map = VariableMap(0, 256)
instance = create_instance(program, var_map)
print(instance.pprint())

n_patterns = 1
n_instances = 1
n_mutations = 10

codegen = CodeGen(base_dir)
scalar_expansion = SimpleScalarExpansion()

patterns_map = {}
for p in range(n_patterns):
    pattern_name = f'p{p:02d}'
    instance_map = {}
    for i in range(n_instances):
        instance_name = f'i{i:02d}'
        codegen.generate_wrapper(pattern_name, instance_name, instance)
        mutation_names = []
        for m in range(n_mutations):
            mutation_name = f'm{m:02d}'
            mutation_names.append(mutation_name)
            mutation = next(scalar_expansion.transform(instance, var_map))
            codegen.generate_code(pattern_name, instance_name, mutation_name, mutation)
        instance_map[instance_name] = mutation_names
    patterns_map[pattern_name] = instance_map
codegen.generate_pattern_file(patterns_map)
