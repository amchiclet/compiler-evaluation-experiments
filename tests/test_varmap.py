from parser import parse_file
from loguru import logger
from variable_map import VariableMap, validate_var_map, randomize_iteration_vars
from simple_formatter import SimpleFormatter
from multiprocessing import Pool
from build import PathBuilder
from codegen import CodeGen
import sys

pattern_str = 'delete_me'
n_programs = 2
n_mutations = 3
output_dir = pattern_str

logger.remove()
logger.add(sys.stdout, level='INFO')
logger.add(sink = 'multiple.log',
           level = 'INFO',
           format = ('{process.name} | '
                     '{time:YYYYMMDD_HH:mm:ss.SSS} | '
                     '{file}:{function}:{line} | '
                     '{message}'),
           enqueue = True)

program, _ = parse_file('loops/aplbench_mean_subtract_images.loop')
logger.info(program.pprint())

default_min = 0
default_max = 128
var_map = VariableMap(default_min, default_max)
validated = validate_var_map(program, var_map)
print('validated')
print(validated.pprint())
randomized = randomize_iteration_vars(program, validated)
print('randomized')
print(randomized.pprint())
codegen = CodeGen('out')
codegen.generate_wrapper('varmap', 'program',
                         program, randomized)
codegen.generate_code('varmap', 'program', 'mutation',
                      program, randomized)
codegen.generate_pattern_file()
