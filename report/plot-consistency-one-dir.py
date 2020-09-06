from report.generate import get_ok_patterns, read_runtimes_database_multi_experiment, limit_patterns, read_runtimes_database, get_popular_pattern_structure
from report.runtime import add_plot_normalized_runtimes
from report.util import update_dict_array
from compilers import compilers
from plot import display_plot, save_plot, clear_plot
from random import shuffle
import os

base_dir = 'interchange.125.2.4.3/code'
base_dir = os.path.abspath(os.getcwd())
n_patterns = 2

all_patterns = get_ok_patterns(base_dir)
n_instances, n_mutations = get_popular_pattern_structure(all_patterns)
all_patterns = limit_patterns(all_patterns, n_instances, n_mutations)

if n_patterns > len(all_patterns):
    n_patterns = 1
n_parts = len(all_patterns) // n_patterns
n_all_patterns = n_patterns * n_parts
print(f'n_patterns({n_patterns}) n_instances({n_instances}) n_mutations({n_mutations})')
assert(n_all_patterns <= len(all_patterns))
c = 'gcc'

for repeat in range(10):
    shuffle(all_patterns)
    for part in range(0, n_all_patterns, n_patterns):
        patterns = all_patterns[part:part+n_patterns]
        runtimes = read_runtimes_database(base_dir, patterns)
        add_plot_normalized_runtimes(c, runtimes, f'patterns {part}-{part+n_patterns}')
    save_plot(f'/mnt/d/interchange.{n_patterns}.{n_instances}.{repeat}.png', f'{c} runtime stability')
    clear_plot()
