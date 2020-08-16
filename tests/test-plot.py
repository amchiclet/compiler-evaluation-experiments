from report.generate import get_ok_patterns, read_runtimes_database
from report.runtime import get_normalized_runtimes
from stats import geometric_mean
from random import choices
from plot import add_plot, display_plot, save_plot
from report.util import update_dict_array

ok_patterns = get_ok_patterns()
runtimes = read_runtimes_database(ok_patterns)
normalized, _ = get_normalized_runtimes(runtimes)

def plot_normalized_runtimes(runtimes):
    grouped = {}
    for (compiler, pattern, program, mutation), runtime in runtimes.items():
        update_dict_array(grouped, compiler, runtime)
    for c, rs in grouped.items():
        data = []
        for b in range(10000):
            samples = choices(rs, k=len(rs))
            data.append(geometric_mean(samples))
        add_plot(data, c)
    save_plot('test.png')
    display_plot()


plot_normalized_runtimes(normalized)
