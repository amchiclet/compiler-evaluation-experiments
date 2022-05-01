from api import Skeleton, Mapping, CodegenConfig
from random import randint, seed
from codelet_generator import codelet_dir, generate_codelet_files, generate_batch_summary, SourceInfo
from pattern_ast import get_ordered_assignments, get_accesses

application = 'LoopGen'
batch = 'vecadd-api-v2'
code = f'a_bb'
codelet = f'{code}_de'

skeleton_code = """
declare a[N];
declare b[N];
declare N;

for [(i, >=0, <=N-1)] {
  a[i] = b[i] + b[i];
}
"""

program = Skeleton(skeleton_code)

config = CodegenConfig()

config.possible_values = {
    'a[i]': 1,
    'b[i]': 1,
    'N': 1,
}

config.types = {
    'a[i]': 'double',
    'b[i]': 'double',
    'N': 'int',
}

config.initial_values = {
    'a[i]' : 'drand(0.0, 1.0)',
    'b[i]' : 'drand(0.0, 1.0)',
    'N': 'inputs[0]',
}

config.template_dir = 'codelet-template-int-inputs'
config.output_dir = generate_codelet_files(application, batch, code, codelet, 10, [32000])
config.array_as_ptr = True
program.generate_code(config)
