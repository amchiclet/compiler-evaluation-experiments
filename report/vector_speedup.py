from stats import \
    calculate_ci_geometric, \
    calculate_ci_proportion, \
    create_min_max_cases, \
    create_max_spread_cases, \
    Stats, \
    geometric_mean
import plot
from report.util import update_dict_dict, merge_value, update_dict_array, get_paths_for_pair, format_spread_pair, Outlier, normalize_compiler_name
from random import choices
from tqdm import tqdm
from scipy.stats import probplot
import matplotlib.pyplot as plt
import math
from loguru import logger
from report.mode import is_comparing_versions

normal_threshold = 100
def get_vec_speedups(runtimes):
    compilers = set()
    grouped = {}
    for (compiler, mode, pattern, program, mutation), runtime in runtimes.items():
        compilers.add(compiler)
        key = (compiler, pattern, program, mutation)
        update_dict_dict(grouped, key, mode, runtime)

    speedups = {}
    for key, mode_runtimes in grouped.items():
        if 'novec' in mode_runtimes and 'fast' in mode_runtimes:
            speedups[key] = mode_runtimes['novec'] / mode_runtimes['fast']
    best_speedups = {}
    for key, speedup in speedups.items():
        merge_value(best_speedups, key[:-1], speedup, max)
    return compilers, speedups, best_speedups

def get_normalized_vec_speedups(runtimes):
    compilers, speedups, best_speedups = get_vec_speedups(runtimes)
    outliers = create_min_max_cases()
    normalized = {}
    for key, speedup in speedups.items():
        normalized[key] = speedup / best_speedups[key[:-1]]
        outliers.merge(key, normalized[key], (speedup, key[-3:]))

    return normalized, outliers

def add_plot_normalized_vec_speedups(compilers, patterns, runtimes, fig_path=None):
    normalized, _ = get_normalized_vec_speedups(runtimes)
    plots = {}
    for c in compilers:
        plots[c] = []
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
        plot.display_plot('vector speedup')
    else:
        plot.save_plot(fig_path, 'vector speedup')
        plot.clear_plot()

def plot_ci_bar(n_patterns, raw_runtimes, fig_path=None, legend=True):
    normalized, _ = get_normalized_vec_speedups(raw_runtimes)

    grouped = {}
    for (compiler, pattern, program, mutation), runtime in normalized.items():
        update_dict_array(grouped, compiler, runtime)

    means = {}
    cis = {}
    for key, runtimes in grouped.items():
        all_ci = calculate_ci_geometric(runtimes, 0.0, 1.0, n_patterns)
        cis[key] = all_ci[1]
        means[key] = geometric_mean(runtimes)

    plot.add_bar(means, cis)

    if fig_path is None:
        plot.display_plot('vector speedup', legend)
    else:
        plot.save_plot(fig_path, 'vector speedup', legend)
        plot.clear_plot()

def plot_vec_speedups(runtimes):
    compilers = set()
    normalized, _ = get_normalized_vec_speedups(runtimes)
    grouped = {}
    for (compiler, pattern, program, mutation), runtime in normalized.items():
        update_dict_array(grouped, compiler, runtime)
        compilers.add(compiler)

    for compiler in sorted(list(compilers)):
        filtered = {k:v for k,v in grouped.items() if k == compiler}
        plot.add_dict_array(filtered, geometric_mean, b=10000, min_val=0, max_val=1)
        plot.display_plot(f'{compiler} vector speedup stability')

def get_raw_outliers(runtimes):
    grouped = {}
    for (compiler, mode, pattern, program, mutation), runtime in runtimes.items():
        key = (compiler, pattern, program, mutation)
        update_dict_dict(grouped, key, mode, runtime)

    outliers = create_min_max_cases()
    for key, mode_runtimes in grouped.items():
        if 'novec' in mode_runtimes and 'fast' in mode_runtimes:
            speedup = mode_runtimes['novec'] / mode_runtimes['fast']
            compiler, *rest = key
            outliers.merge((compiler, rest), speedup, rest)

    return outliers

def get_stats(runtimes):
    normalized, outliers = get_normalized_vec_speedups(runtimes)

    grouped = {}
    for (compiler, pattern, program, mutation), runtime in normalized.items():
        update_dict_array(grouped, compiler, runtime)

    cis = {}
    for key, runtimes in grouped.items():
        cis[key] = calculate_ci_geometric(runtimes, 0.0, 1.0)

    interesting_cases = create_max_spread_cases()
    for (compiler, *rest), [min_outlier, max_outlier] in outliers.cases.items():
        normalized_pair = (min_outlier.normalized, max_outlier.normalized)
        raw_pair = (min_outlier.raw, max_outlier.raw)
        interesting_cases.merge((compiler, rest), normalized_pair, raw_pair)
    return Stats('Vec speedup stability', cis, interesting_cases)

def get_paths(stats):
    return get_paths_for_pair(stats)

def format_raw(raw):
    return format_spread_pair(raw)

def get_data_and_errors(compilers, patterns, raw_runtimes):
    normalized, outliers = get_normalized_vec_speedups(raw_runtimes)

    per_pattern = {}
    for (compiler, pattern, program, mutation), runtime in normalized.items():
        update_dict_array(per_pattern, (compiler, pattern), runtime)

    grouped = {}
    for (compiler, pattern), runtimes in per_pattern.items():
        update_dict_array(grouped, compiler, geometric_mean(runtimes))

    # grouped = {}
    # for (compiler, pattern, program, mutation), runtime in normalized.items():
    #     update_dict_array(grouped, compiler, runtime)

    data = {}
    neg_errs = {}
    pos_errs = {}

    for key, runtimes in grouped.items():
        val = geometric_mean(runtimes)
        data[key] = val
        if len(runtimes) > normal_threshold:
            # all_ci = calculate_ci_geometric(runtimes, 0.0, 1.0, n_patterns)
            all_ci = calculate_ci_geometric(runtimes, 0.0, 1.0)
            ci95 = all_ci[1]
            neg_errs[key] = val - ci95[0]
            pos_errs[key] = ci95[1] - val
        else:
            neg_errs[key] = None
            pos_errs[key] = None

    interesting_cases = create_max_spread_cases()
    for (compiler, *rest), [min_outlier, max_outlier] in outliers.cases.items():
        normalized_pair = (min_outlier.normalized, max_outlier.normalized)
        raw_pair = (min_outlier.raw, max_outlier.raw)
        interesting_cases.merge((compiler, rest), normalized_pair, raw_pair)

    # print('vector speedup')
    # print(interesting_cases.pprint())
    return data, neg_errs, pos_errs, interesting_cases

def plot_qq(compilers, patterns, runtimes):
    normalized, _ = get_normalized_vec_speedups(runtimes)
    per_pattern = {}
    for (c, p, i, m), speedup in normalized.items():
        update_dict_array(per_pattern, (c, p), speedup)
    grouped = {}
    for (c, _), speedups in per_pattern.items():
        update_dict_array(grouped, c, geometric_mean(speedups))
    for vals in grouped.values():
        data = []
        for _ in tqdm(range(1000)):
            samples = choices(vals, k=len(vals))
            data.append(geometric_mean(samples))
        probplot(data, plot=plt)
        plt.show()

def pure(p, i, m):
    return p[1], i, m

def plot_scaled_speedups(compilers, patterns, runtimes, path_prefix=None):
    def is_better_speedup(x, y):
        return x > y

    speedups = {}
    best_speedups = {}
    for c in compilers:
        for p, instances in patterns:
            for i, mutations in instances:
                for m in mutations:
                    fast_key = (c, 'fast', p, i, m)
                    novec_key = (c, 'novec', p, i, m)
                    if fast_key in runtimes and novec_key in runtimes:
                        speedup = runtimes[novec_key] / runtimes[fast_key]
                        speedups[(c, p, i, m)] = speedup
                        if (c, p, i) not in best_speedups:
                            best_speedups[(c, p, i)] = Outlier()
                        best_speedups[(c, p, i)].merge(is_better_speedup, speedup, m)

    def is_worse_speedup(x, y):
        return x < y

    mins = {}
    data = {}
    data_and_info = {}
    for (c, p, i, m), speedup in speedups.items():
        scaled = speedups[(c, p, i, m)] / best_speedups[(c, p, i)].data

        update_dict_array(data, c, scaled)

        scaled_pim = scaled, (f'{speedups[(c, p, i, m)]:.3f}/{best_speedups[(c, p, i)].data:.3f}={scaled:.3f}', pure(p, i, m))
        update_dict_array(data_and_info, c, scaled_pim)
        
        if c not in mins:
            mins[c] = Outlier()
        best_m = best_speedups[(c, p, i)].key
        mins[c].merge(is_worse_speedup, scaled, (p, i, m, best_m))

    for a in data_and_info.values():
        a.sort(key=lambda x: x[0])

    how_sparse = 1
    sorted_compilers = sorted(data.keys())

    logger.info('Scaled vector speedup')
    for c in sorted_compilers:
        logger.info(c)
        for rpim in data_and_info[c][:10]:
            logger.info(rpim)

    yticks = []
    ytick_labels = []
    for y_inv, compiler in enumerate(sorted_compilers):
        y = len(sorted_compilers) - y_inv
        yticks.append(y)
        if is_comparing_versions:
            ytick_labels.append(compiler)
        else:
            ytick_labels.append(normalize_compiler_name(compiler))

        ss = [s for s, _ in data_and_info[compiler]]
        sparse = sorted(ss)
        sparse = [s for i, s in enumerate(sparse) if i % how_sparse == 0]

        bottom_index = math.ceil(len(sparse)*0.1)
        bottom = sparse[:bottom_index-1]
        top = sparse[bottom_index:]
        plt.plot(bottom, [y] * len(bottom), '.', color='red')
        plt.plot(top, [y] * len(top), '.', color='green')

    title = f'Scaled vector speedup distribution'
    plt.yticks(yticks, ytick_labels)
    xticks = [0.1 * i for i in range(11)]
    xtick_labels = [f'{t:.1f}' for t in xticks]
    plt.xticks(xticks, xtick_labels)
    plt.xlim(0, 1)
    if path_prefix is None:
        plot.display_plot(title=title, legend=False)
    else:
        path = f'{path_prefix}-all-compilers.png'
        plot.save_plot(path, title, legend=False)
        plot.clear_plot()
