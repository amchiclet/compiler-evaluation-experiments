from api import Skeleton, Mapping, CodegenConfig
from random import randint, seed
from codelet_generator import codelet_dir, generate_codelet_files, generate_batch_summary, SourceInfo
from pattern_ast import get_ordered_assignments, get_accesses

application = 'LoopGen'
batch = 'vecdiv-api-v2'
code = f'a_aa'
codelet = f'{code}_de'

skeleton_code = """
declare a[N];
declare N;

for [(i, >=0, <=N-1)] {
  a[i] = a[i] + a[i];
}
"""

program = Skeleton(skeleton_code)

config = CodegenConfig()

config.possible_values = {
    'a[i]': 1,
    'N': 1,
}

config.types = {
    'a[i]': 'double',
    'N': 'int',
}

config.initial_values = {
    'a[i]' : 'drand(0.01, 1.0)',
    'N': 'inputs[0]',
}

config.template_dir = 'codelet-template-int-inputs'
config.output_dir = generate_codelet_files(application, batch, code, codelet, 10, [32000])
config.array_as_ptr = True
program.generate_code(config)
