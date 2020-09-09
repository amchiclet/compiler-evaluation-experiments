from report.generate import get_ok_patterns, read_runtimes_database_multi_experiment, limit_patterns, read_runtimes_database, get_popular_pattern_structure
from report.runtime import add_plot_normalized_runtimes
from report.util import update_dict_array
from compilers import compilers
from plot import display_plot, save_plot, clear_plot
from random import shuffle
import os

base_dir = os.path.abspath(os.getcwd())

all_patterns = get_ok_patterns(base_dir)
runtimes = read_runtimes_database(base_dir, all_patterns)

n_instances, n_mutations = get_popular_pattern_structure(all_patterns)
all_patterns = limit_patterns(all_patterns, n_instances, n_mutations)

print(n_instances, n_mutations, len(all_patterns))
fig_dir = '/home/phaosaw2/unroll-results'

for repeat in range(10):
    print(f'round {repeat}')
    for n_patterns in [10, 20, 30, 50, 75, 150]:
    # for n_patterns in [50, 100]:
        shuffle(all_patterns)
        sub_patterns = all_patterns[:150]
        n_parts = len(sub_patterns) // n_patterns
        n_all_patterns = n_patterns * n_parts
        assert(n_all_patterns <= len(sub_patterns))
        for c in compilers:
            for part in range(0, n_all_patterns, n_patterns):
                patterns = sub_patterns[part:part+n_patterns]
                pattern_names = [p for (p, instances) in patterns]
                filtered_runtimes = {}
                for k, v in runtimes.items():
                    if k[2] in pattern_names:
                        filtered_runtimes[k] = v

                print(f'compiler({c}) n_patterns({part}-{part+n_patterns})')
                add_plot_normalized_runtimes(c, filtered_runtimes, f'patterns {part}-{part+n_patterns}')
            save_plot(f'/{fig_dir}/unroll.{c}.{n_patterns}.{n_instances}.{repeat}.png', f'{c} runtime stability')
            clear_plot()
