from stats import \
    calculate_ci_geometric, \
    calculate_ci_proportion, \
    create_min_max_cases, \
    create_max_spread_cases, \
    Stats, \
    geometric_mean
from report.util import merge_value, update_dict_array, get_paths_for_pair, format_spread_pair, update_dddl, update_ddl
import plot
from tqdm import tqdm
from random import choices, sample, shuffle

def get_normalized_runtimes(runtimes):
    best_mutations = {}
    for (compiler, mode, pattern, program, mutation), runtime in runtimes.items():
        if mode == 'fast':
            key = (compiler, pattern, program)
            merge_value(best_mutations, key, runtime, min)

    outliers = create_min_max_cases()
    normalized = {}
    for (compiler, mode, pattern, program, mutation), runtime in runtimes.items():
        if mode == 'fast':
            key = (compiler, pattern, program, mutation)
            normalized[key] = best_mutations[key[:-1]] / runtime
            outliers.merge(key, normalized[key], (runtime, key[-3:]))

    return normalized, outliers

def plot_normalized_runtimes(n_patterns, n_instances, runtimes):
    normalized, _ = get_normalized_runtimes(runtimes)
    grouped = {}
    for (compiler, pattern, instance, mutation), runtime in normalized.items():
        update_dddl(grouped, compiler, pattern, instance, runtime)
        compilers.add(compiler)

    for compiler in sorted(list(compilers)):
        filtered = {k:v for k,v in grouped.items() if k == compiler}
        # plot.add_dict_array(filtered, geometric_mean, b=10000, min_val=0, max_val=1)
        plot.add_dddl(filtered,
                      geometric_mean,
                      n_patterns=None,
                      n_instances=None,
                      b=10000,
                      min_val=0,
                      max_val=1)
        plot.display_plot(f'{compiler} runtime stability')

def add_plot_normalized_runtimes_v2(compilers, patterns, runtimes, fig_path=None):
    normalized, _ = get_normalized_runtimes(runtimes)

    plots = {}
    for c in compilers:
        plots[c] = []

    print(f'total patterns {len(patterns)}')
    for _ in tqdm(range(10000)):
        sample_patterns = choices(patterns, k=len(patterns))
        for c in compilers:
            rs = []
            for p, instances in sample_patterns:
                for i, mutations in instances:
                    for m in mutations:
                        rs.append(normalized[(c, p, i, m)])
            plots[c].append(geometric_mean(rs))

    for compiler, sample_stat in plots.items():
        plot.add_plot(sample_stat, label=compiler, min_val=0, max_val=1)
    if fig_path is None:
        plot.display_plot('normalized runtimes')
    else:
        plot.save_plot(fig_path, 'normalized runtimes')
        plot.clear_plot()

def add_plot_normalized_runtimes(compiler, runtimes, label):
    normalized, _ = get_normalized_runtimes(runtimes)
    grouped = {}
    for (c, p, i, m), runtime in normalized.items():
        if compiler != c:
            continue
        update_dddl(grouped, label, p, i, runtime)
    plot.add_dddl(grouped,
                  geometric_mean,
                  b=10000,
                  min_val=0, max_val=1)

def get_stats(runtimes):
    normalized, outliers = get_normalized_runtimes(runtimes)

    grouped = {}
    for (compiler, pattern, program, mutation), runtime in normalized.items():
        update_dict_array(grouped, compiler, runtime)

    cis = {}
    for key, runtimes in grouped.items():
        cis[key] = calculate_ci_geometric(runtimes, 0.0, 1.0)

    interesting_cases = create_max_spread_cases()
    for (compiler, *rest), [min_outlier, max_outlier] in outliers.cases.items():
        normalized_pair = (min_outlier.normalized, max_outlier.normalized)
        # max normalized means min raw runtime
        raw_pair = (max_outlier.raw, min_outlier.raw)
        interesting_cases.merge((compiler, rest), normalized_pair, raw_pair)
    return Stats('Runtime stability', cis, interesting_cases)

def get_paths(stats):
    return get_paths_for_pair(stats)

def format_raw(raw):
    return format_spread_pair(raw)
