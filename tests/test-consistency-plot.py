from report.generate import get_ok_patterns, read_runtimes_database
from report.runtime import get_normalized_runtimes
from stats import geometric_mean
from plot import plot_dict_array, add_plot, display_plot, add_dict_array
from report.util import update_dict_array
from report.peer_speedup import get_peer_speedups
import os

root_dir = os.getcwd()
# for max_p, max_i in [(10, 10), (20, 5), (25, 4)]:

grouped = {}
for max_p, max_i in [(10, 10), (20, 5), (25, 4)]:
    for attempt in range(3):
        base_dir = f'p{max_p}-i{max_i}-version-{attempt}/temp-generated-code'
        ok_patterns = get_ok_patterns(base_dir)
        runtimes = read_runtimes_database(base_dir, ok_patterns)
        normalized, _ = get_normalized_runtimes(runtimes)
        for (compiler, pattern, program, mutation), runtime in normalized.items():
            update_dict_array(grouped, f'{compiler}-{max_p}-{max_i}-{attempt}', runtime)

for interested in ['icc', 'gcc', 'clang', 'pgi']:
    print(f'interested in {interested}')
    interestd = {}
    filtered = {c:v for c, v in grouped.items() if interested in c}
    add_dict_array(filtered, geometric_mean)
    display_plot()

