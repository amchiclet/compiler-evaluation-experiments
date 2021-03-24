from stats import \
    calculate_ci_geometric, \
    calculate_ci_proportion, \
    create_min_max_cases, \
    create_max_spread_cases, \
    Stats, \
    geometric_mean, \
    arithmetic_mean
from report.util import merge_value, update_dict_array, get_paths_for_pair, format_spread_pair, update_dddl, update_ddl, normalize_compiler_name
import plot
from tqdm import tqdm
from random import choices, sample, shuffle
import matplotlib.pyplot as plt
from scipy import log
from scipy.stats import probplot
import math
from loguru import logger
import heapq
from report.mode import is_comparing_versions
normal_threshold = 100

def plot_ci_bar(n_patterns, raw_runtimes, fig_path=None):
    normalized, _ = get_normalized_runtimes(raw_runtimes)

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
        plot.display_plot('runtime stability')
    else:
        plot.save_plot(fig_path, 'runtime stability')
        plot.clear_plot()

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
    # print(normalized)
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

def get_per_pattern(compilers, patterns, raw_runtimes):
    normalized, outliers = get_normalized_runtimes(raw_runtimes)

    per_pattern = {}
    for (compiler, pattern, program, mutation), runtime in normalized.items():
        update_dict_array(per_pattern, (compiler, pattern), runtime)

    grouped = {}
    for (compiler, pattern), runtimes in per_pattern.items():
        update_dict_array(grouped, compiler, geometric_mean(runtimes))
    return grouped

def get_data_and_errors(compilers, patterns, raw_runtimes):
    normalized, outliers = get_normalized_runtimes(raw_runtimes)

    per_pattern = {}
    for (compiler, pattern, program, mutation), runtime in normalized.items():
        update_dict_array(per_pattern, (compiler, pattern), runtime)

    grouped = {}
    for (compiler, pattern), runtimes in per_pattern.items():
        update_dict_array(grouped, compiler, geometric_mean(runtimes))

    data = {}
    neg_errs = {}
    pos_errs = {}

    for key, runtimes in grouped.items():
        val = geometric_mean(runtimes)
        data[key] = val
        if len(runtimes) > normal_threshold:
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
        # max normalized means min raw runtime
        raw_pair = (max_outlier.raw, min_outlier.raw)
        interesting_cases.merge((compiler, rest), normalized_pair, raw_pair)
    # print('runtime stability')
    # print(interesting_cases.pprint())

    return data, neg_errs, pos_errs, interesting_cases

def pure(p, i, m):
    return p[1], i, m

def pure(p, i, m):
    return p, i, m

def plot_scaled_runtimes(compilers, patterns, runtimes, path_prefix=None):
    best_mutations = {}
    for (compiler, mode, pattern, instance, mutation), runtime in runtimes.items():
        if mode == 'fast':
            k = (compiler, pattern, instance)
            if k not in best_mutations:
                best_mutations[k] = (runtime, (pattern, instance, mutation))
            else:
                if runtime < best_mutations[k][0]:
                    best_mutations[k] = (runtime, (pattern, instance, mutation))

    normalized = {}
    for (compiler, mode, pattern, program, mutation), runtime in runtimes.items():
        if mode == 'fast':
            key = (compiler, pattern, program, mutation)
            best_mutation_runtime = best_mutations[(compiler, pattern, program)][0]
            normalized[key] = (best_mutation_runtime, runtime)

    mins = {}
    data = {}
    data_and_info = {}
    for (compiler, pattern, instance, mutation), (best_mutation_runtime, runtime) in normalized.items():
        r = best_mutation_runtime / runtime
        update_dict_array(data, compiler, r)

        # find outliers
        pim = (pattern, instance, mutation)
        best_pim = best_mutations[(compiler, pattern, instance)][1]
        r_pim = (r, (f'{best_mutation_runtime:.3f}/{runtime:.3f}={r:.3f}', pure(*pim), pure(*best_pim)))
        update_dict_array(data_and_info, compiler, r_pim)

        if compiler not in mins:
            mins[compiler] = (r, pim, best_pim)
        else:
            if r < mins[compiler][0]:
                mins[compiler] = (r, pim, best_pim)

    for a in data_and_info.values():
        a.sort(key=lambda x: x[0])

    how_sparse = 1
    sorted_compilers = sorted(data.keys())

    logger.info('Scaled runtimes')
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

        rs = [r for r, _ in data_and_info[compiler]]
        sparse = sorted(rs)
        sparse = [s for i, s in enumerate(sparse) if i % how_sparse == 0]

        bottom_5_index = math.ceil(len(sparse)*0.1)
        bottom_5 = sparse[:bottom_5_index-1]
        top_95 = sparse[bottom_5_index:]
        plt.plot(bottom_5, [y] * len(bottom_5), '.', color='red')
        plt.plot(top_95, [y] * len(top_95), '.', color='green')

    title = f'Scaled runtime distribution'
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

def plot_qq(compilers, patterns, raw_runtimes, sample_size=None):
    normalized, outliers = get_normalized_runtimes(raw_runtimes)

    per_pattern = {}
    for (compiler, pattern, program, mutation), runtime in normalized.items():
        update_dict_array(per_pattern, (compiler, pattern), runtime)

    grouped = {}
    for (compiler, pattern), runtimes in per_pattern.items():
        update_dict_array(grouped, compiler, geometric_mean(runtimes))

    for compiler, vals in grouped.items():
        data = []
        if sample_size is None:
            sample_size = len(vals)
        else:
            sample_size = min(sample_size, len(vals))
        for _ in tqdm(range(1000)):
            samples = choices(vals, k=sample_size)
            # data.append(geometric_mean(samples))

            # test for arithmetic mean of logs
            # samples = [log(s) for s in samples]
            data.append(arithmetic_mean([log(s) for s in samples]))

        probplot(data, plot=plt)
        # plot.display_plot(title=f'{compiler} (n={sample_size})',
        #                   legend=False)
        plot.save_plot(f'runtime_{compiler}_{sample_size}.png',
                       title=f'{compiler} (n={sample_size})',
                       legend=False)
        plot.clear_plot()

