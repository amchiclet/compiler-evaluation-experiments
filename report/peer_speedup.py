from stats import \
    calculate_ci_geometric, \
    create_max_cases, \
    Stats, \
    geometric_mean, \
    arithmetic_mean
from report.util import merge_value, update_dict_dict, update_dict_array, get_paths_for_pair, format_spread_pair, format_raw_single_mutation, get_paths_for_single, Outlier, normalize_compiler_name

from scipy import log
from scipy.stats import gmean, probplot
from report.peer_metrics import get_compiler_pairs_and_pims, x_faster_than_y_key, iterate_compiler_runtime_pairs, is_approximate, x_approximates_y_key, is_faster_mention, get_compiler_pairs

import plot
import matplotlib.pyplot as plt
from loguru import logger
from random import choices
from tqdm import tqdm
import math

from report.mode import is_comparing_versions

normal_threshold = 100
def get_peer_speedups(runtimes):
    compilers = set()
    speedups = {}
    outliers = create_max_cases()
    for (c1, r1), (c2, r2), pim in iterate_compiler_runtime_pairs(runtimes):
        compilers.add(c1)
        compilers.add(c2)
        if is_approximate(r1, r2):
            key = x_approximates_y_key(c1, c2)
            speedup = 1.0
        else:
            if r1 < r2:
                key = x_faster_than_y_key(c1, c2)
                speedup = r2 / r1
                # update_dict_array(speedups, (key,), speedup)
                # outliers.merge((key, pim), speedup, (speedup, pim))
            else:
                key = x_faster_than_y_key(c2, c1)
                speedup = r1 / r2
        update_dict_array(speedups, key, speedup)
        outliers.merge((key, pim), speedup, (speedup, pim))
    return compilers, speedups, outliers

def plot_peer_speedups(runtimes):
    compilers, speedups, _ = get_peer_speedups(runtimes)
    for compiler in compilers:
        filtered = {}
        for k, v in speedups.items():
            if is_faster_mention(k, compiler):
                if plot.check_samples(f'Peer speed up {k}', v):
                    filtered[k] = v
        plot.add_dict_array(filtered, geometric_mean, b=10000, min_val=0)
        plot.display_plot(f'{compiler} peer speed up')

def make_key(c, ref):
    return f'{c} / {ref}'

def get_peer_speedups_v2(runtimes):
    speedups = {}
    outliers = create_max_cases()
    for (c1, r1), (c2, r2), pim in iterate_compiler_runtime_pairs(runtimes):
        key = make_key(c2, c1)
        speedup = r2 / r1
        update_dict_array(speedups, key, speedup)
        outliers.merge((key, pim), speedup, (speedup, pim))

        key_inv = make_key(c1, c2)
        speedup_inv = r1 / r2
        update_dict_array(speedups, key_inv, speedup_inv)
        outliers.merge((key_inv, pim), speedup_inv, (speedup_inv, pim))
    return speedups, outliers

def get_peer_speedups_v3(runtimes):
    speedups = {}
    for (c1, r1), (c2, r2), pim in iterate_compiler_runtime_pairs(runtimes):
        key = make_key(c2, c1)
        speedup = r2 / r1
        speedups[(key, pim)] = speedup

        key_inv = make_key(c1, c2)
        speedup_inv = r1 / r2
        speedups[(key_inv, pim)] = speedup_inv
    return speedups

# def add_plot_peer_speedups(compilers, patterns, runtimes, fig_path=None):
#     speedups_map = get_peer_speedups_v3(runtimes)

#     plots = {}

#     for (c1, c2) in get_compiler_pairs(compilers):
#         plots[make_key(c1, c2)] = []
#         plots[make_key(c2, c1)] = []

#     for _ in tqdm(range(10000)):
#         sample_patterns = choices(patterns, k=len(patterns))
#         for (c1, c2) in get_compiler_pairs(compilers):
#             for pair in [make_key(c1, c2), make_key(c2, c1)]:
#                 speedups = []
#                 for p, instances in sample_patterns:
#                     for i, mutations in instances:
#                         for m in mutations:
#                             speedups.append(speedups_map[(pair, (p, i, m))])
#                 plots[pair].append(geometric_mean(speedups))

#     colors = 'bgrcmyk'
#     for (pair, sample_stat), color in zip(plots.items(), colors):
#         plot.add_plot(sample_stat, label=pair, color=color, min_val=0)
#     if fig_path is None:
#         plot.display_plot('peer speedup')
#     else:
#         plot.save_plot(fig_path, 'peer speedup')
#         plot.clear_plot()

# def get_stats(runtimes):
#     _, speedups, outliers = get_peer_speedups(runtimes)

#     cis = {}
#     for key, speedup in speedups.items():
#         cis[key] = calculate_ci_geometric(speedup)

#     return Stats('Peer speedup stability', cis, outliers)

def plot_ci_bar(n_patterns, raw_runtimes, fig_path=None):
    _, speedups, _ = get_peer_speedups(runtimes)

    means = {}
    cis = {}
    for key, speedup in speedups.items():
        all_ci = calculate_ci_geometric(speedup, n_samples=n_patterns)
        cis[key] = all_ci[1]
        means[key] = geometric_mean(speedup)

    plot.add_bar(means, cis)

    if fig_path is None:
        plot.display_plot('peer speedup')
    else:
        plot.save_plot(fig_path, 'peer speedup')
        plot.clear_plot()

def get_paths(stats):
    return get_paths_for_single(stats)

def format_raw(raw):
    return format_raw_single_mutation(raw)

# def get_data_and_errors(compilers, n_patterns, runtimes):
#     speedups = {}

#     outliers = create_max_cases()

#     for (c1, r1), (c2, r2), pim in iterate_compiler_runtime_pairs(runtimes):
#         p, i, m = pim
#         speedup = r2 / r1
    
#         speedups[((c2, c1), pim)] = speedup
#         outliers.merge(((c2, c1), pim), speedup, (speedup, pim))

#         speedup_inv = r1 / r2
#         speedups[((c1, c2), pim)] = speedup_inv
#         outliers.merge(((c1, c2), pim), speedup_inv, (speedup_inv, pim))
#     # print(outliers.pprint())

#     # pattern level
#     pattern_speedups = {}
#     for (pair, (p, i, m)), speedup in speedups.items():
#         update_dict_array(pattern_speedups, (pair, p), speedup)

#     pattern_mean_speedup = {k:geometric_mean(speedups)
#                             for k, speedups in pattern_speedups.items()}

#     grouped = {}
#     for (pair, p), mean_speedup in pattern_mean_speedup.items():
#         if mean_speedup > 1.05:
#             update_dict_array(grouped, pair, mean_speedup)

#     data = {}
#     neg_errs = {}
#     pos_errs = {}
#     for key, speedups in grouped.items():
#         val = geometric_mean(speedups)

#         data[key] = val
#         if len(speedups) > normal_threshold:
#             all_ci = calculate_ci_geometric(speedups)
#             ci95 = all_ci[1]
#             neg_errs[key] = val - ci95[0]
#             pos_errs[key] = ci95[1] - val
#         else:
#             neg_errs[key] = None
#             pos_errs[key] = None

#     return data, neg_errs, pos_errs, outliers

def get_per_pattern(compilers, patterns, runtimes):
    speedups = {}

    for (c1, r1), (c2, r2), pim in iterate_compiler_runtime_pairs(runtimes):
        if is_comparing_versions:
            # uncomment for old version vs new version experiment
            if normalize_compiler_name(c1) != normalize_compiler_name(c2):
                continue

        p, i, m = pim
        speedup = r2 / r1
        speedups[((c2, c1), pim)] = speedup

        speedup_inv = r1 / r2
        speedups[((c1, c2), pim)] = speedup_inv

    per_pattern = {}
    for (pair, (p, i, m)), speedup in speedups.items():
        update_dict_array(per_pattern, (pair, p), speedup)

    grouped = {}
    for (pair, _), ss in per_pattern.items():
        update_dict_array(grouped, pair, geometric_mean(ss))
    return grouped

def get_data_and_errors_v2(compilers, patterns, runtimes):
    speedups = {}

    outliers = create_max_cases()

    for (c1, r1), (c2, r2), pim in iterate_compiler_runtime_pairs(runtimes):
        if is_comparing_versions:
            # uncomment for old version vs new version experiment
            if normalize_compiler_name(c1) != normalize_compiler_name(c2):
                continue

        p, i, m = pim
        speedup = r2 / r1

        speedups[((c2, c1), pim)] = speedup
        outliers.merge(((c2, c1), pim), speedup, (speedup, pim))

        speedup_inv = r1 / r2
        speedups[((c1, c2), pim)] = speedup_inv
        outliers.merge(((c1, c2), pim), speedup_inv, (speedup_inv, pim))

    per_pattern = {}
    for (pair, (p, i, m)), speedup in speedups.items():
        if speedup > 1.05:
            update_dict_array(per_pattern, (pair, p), speedup)

    grouped = {}
    for (pair, _), ss in per_pattern.items():
        update_dict_array(grouped, pair, geometric_mean(ss))

    data = {}
    neg_errs = {}
    pos_errs = {}
    for key, speedups in grouped.items():
        val = geometric_mean(speedups)
        all_ci = calculate_ci_geometric(speedups)
        ci95 = all_ci[1]

        data[key] = val
        if len(speedups) > normal_threshold:
            neg_errs[key] = val - ci95[0]
            pos_errs[key] = ci95[1] - val
        else:
            neg_errs[key] = None
            pos_errs[key] = None

    return data, neg_errs, pos_errs, outliers

def plot_qq(compilers, patterns, runtimes):
    speedups = {}
    for (c1, r1), (c2, r2), pim in iterate_compiler_runtime_pairs(runtimes):
        p, i, m = pim
        speedup = r2 / r1
        speedups[((c2, c1), pim)] = speedup

        speedup_inv = r1 / r2
        speedups[((c1, c2), pim)] = speedup_inv

    pattern_speedup_map = {}
    for (pair, (p, i, m)), speedup in speedups.items():
        update_dict_array(pattern_speedup_map, (pair, p), speedup)

    grouped = {}
    for (pair, _), pattern_speedups in pattern_speedup_map.items():
        mean_speedup = geometric_mean(pattern_speedups)
        # update_dict_array(grouped, pair, mean_speedup)
        if mean_speedup > 1.05:
            update_dict_array(grouped, pair, mean_speedup)

    for pair, vals in grouped.items():
        data = []
        for _ in tqdm(range(1000)):
            samples = choices(vals, k=len(vals))
            data.append(geometric_mean(samples))

        probplot(data, plot=plt)
        plt.title(f'{pair[0]}/{pair[1]} n_samples={len(vals)}')
        plt.show()

def pure(p, i, m):
    return p[1], i, m

def plot_peer_speedups_v2(compilers, patterns, runtimes, path_prefix=None):
    def is_better_speedup(x, y):
        return x > y
    def is_worse_speedup(x, y):
        return x < y

    data = {}
    mins = {}
    maxs = {}
    data_and_info = {}
    for (c1, r1), (c2, r2), pim in iterate_compiler_runtime_pairs(runtimes):
        if is_comparing_versions:
            # uncomment for old version vs new version experiment
            if normalize_compiler_name(c1) != normalize_compiler_name(c2):
                continue

        p, i, m = pim
        key = (c2, c1)
        speedup = r2 / r1
        key_inv = (c1, c2)
        speedup_inv = r1 / r2
        update_dict_array(data, key, speedup)
        update_dict_array(data, key_inv, speedup_inv)

        s_pim = (speedup, (f'{r2:.3f}/{r1:.3f}={speedup:.3f}', pure(*pim)))
        update_dict_array(data_and_info, key, s_pim)
        s_inv_pim = (speedup_inv, (f'{r1:.3f}/{r2:.3f}={speedup_inv:.3f}', pure(*pim)))
        update_dict_array(data_and_info, key_inv, s_inv_pim)

        if key not in mins:
            mins[key] = Outlier()
        mins[key].merge(is_worse_speedup, speedup, pim)
        if key_inv not in mins:
            mins[key_inv] = Outlier()
        mins[key_inv].merge(is_worse_speedup, speedup_inv, pim)

        if key not in maxs:
            maxs[key] = Outlier()
        maxs[key].merge(is_better_speedup, speedup, pim)
        if key_inv not in maxs:
            maxs[key_inv] = Outlier()
        maxs[key_inv].merge(is_better_speedup, speedup_inv, pim)

    how_sparse = 1
    sorted_compilers = sorted(compilers)
    # sorted_compilers = sorted(data.keys(),
    #                           key=lambda pair: (pair[1], pair[0]))

    for a in data_and_info.values():
        a.sort(key=lambda x: x[0])

    logger.info('Peer slowdown')
    for c1 in sorted_compilers:
        for c2 in sorted_compilers:
            if c1 == c2:
                continue
            if is_comparing_versions:
                # uncomment for old version vs new version experiment
                if normalize_compiler_name(c1) != normalize_compiler_name(c2):
                    continue
            logger.info(f'{c1}/{c2}')

            for rpim in data_and_info[(c1, c2)][:10]:
                logger.info(rpim)

    logger.info('Peer speedups')
    for c1 in sorted_compilers:
        for c2 in sorted_compilers:
            if c1 == c2:
                continue
            if is_comparing_versions:
                # uncomment for old version vs new version experiment
                if normalize_compiler_name(c1) != normalize_compiler_name(c2):
                    continue
            logger.info(f'{c1}/{c2}')

            for rpim in data_and_info[(c1, c2)][-10:]:
                logger.info(rpim)

    x_limit = 10
    for ref_compiler in sorted_compilers:
        yticks = []
        ytick_labels = []
        y_inv = 0
        for compiler in sorted_compilers:
            if compiler == ref_compiler:
                continue
            if is_comparing_versions:
                # uncomment for old version vs new version experiment
                if normalize_compiler_name(ref_compiler) != normalize_compiler_name(compiler):
                    continue

            y = len(sorted_compilers) - y_inv
            yticks.append(y)
            if is_comparing_versions:
                # uncomment for old version vs new version experiment
                ytick_labels.append(compiler)
            else:
                # uncomment for versionless experiments
                ytick_labels.append(normalize_compiler_name(compiler))

            ss = data[(compiler, ref_compiler)]
            collapsed = [s if s < x_limit else x_limit for s in ss]
            sparse = sorted(collapsed)
            sparse = [s for i, s in enumerate(sparse) if i % how_sparse == 0]

            bottom_index = math.ceil(len(sparse)*0.1)
            bottom = sparse[:bottom_index-1]
            top = sparse[bottom_index:]
            plt.plot(bottom, [y] * len(bottom), '.', color='red')
            plt.plot(top, [y] * len(top), '.', color='green')
            y_inv += 1

        if is_comparing_versions:
            # uncomment for old version vs new version experiment
            title = f'{ref_compiler} slowdown distribution vs other compilers'
        else:
            # uncomment for versionless experiments
            title = f'{normalize_compiler_name(ref_compiler)} slowdown distribution vs other compilers'

        xticks = [0.1 * i for i in range(11)]
        xtick_labels = [f'{t:.1f}' for t in xticks]

        plt.xticks(xticks, xtick_labels)
        plt.yticks(yticks, ytick_labels)
        plt.xlim(0, 1)
        if path_prefix is None:
            plot.display_plot(title=title, legend=False)
        else:
            if is_comparing_versions:
                # uncomment for old version vs new version experiment
                path = f'{path_prefix}-{ref_compiler}.png'
            else:
                # uncomment for versionless experiments
                path = f'{path_prefix}-{normalize_compiler_name(ref_compiler)}.png'
            plot.save_plot(path, title, legend=False)
            plot.clear_plot()
