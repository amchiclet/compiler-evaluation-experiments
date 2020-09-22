from stats import \
    calculate_ci_geometric, \
    create_max_cases, \
    Stats, \
    geometric_mean
from report.util import merge_value, update_dict_dict, update_dict_array, get_paths_for_pair, format_spread_pair, format_raw_single_mutation, get_paths_for_single

from scipy import log
from scipy.stats import gmean
from report.peer_metrics import get_compiler_pairs_and_pims, x_faster_than_y_key, iterate_compiler_runtime_pairs, is_approximate, x_approximates_y_key, is_faster_mention, get_compiler_pairs

import plot

from loguru import logger
from random import choices
from tqdm import tqdm

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

def add_plot_peer_speedups(compilers, patterns, runtimes, fig_path=None):
    speedups_map = get_peer_speedups_v3(runtimes)

    plots = {}

    for (c1, c2) in get_compiler_pairs(compilers):
        plots[make_key(c1, c2)] = []
        plots[make_key(c2, c1)] = []

    for _ in tqdm(range(10000)):
        sample_patterns = choices(patterns, k=len(patterns))
        for (c1, c2) in get_compiler_pairs(compilers):
            for pair in [make_key(c1, c2), make_key(c2, c1)]:
                speedups = []
                for p, instances in sample_patterns:
                    for i, mutations in instances:
                        for m in mutations:
                            speedups.append(speedups_map[(pair, (p, i, m))])
                plots[pair].append(geometric_mean(speedups))

    colors = 'bgrcmyk'
    for (pair, sample_stat), color in zip(plots.items(), colors):
        plot.add_plot(sample_stat, label=pair, color=color, min_val=0)
    if fig_path is None:
        plot.display_plot('peer speedup')
    else:
        plot.save_plot(fig_path, 'peer speedup')
        plot.clear_plot()

def get_stats(runtimes):
    _, speedups, outliers = get_peer_speedups(runtimes)

    cis = {}
    for key, speedup in speedups.items():
        cis[key] = calculate_ci_geometric(speedup)

    return Stats('Peer speedup stability', cis, outliers)

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

def get_data_and_errors(compilers, n_patterns, runtimes):
    speedups = {}

    outliers = create_max_cases()

    for (c1, r1), (c2, r2), pim in iterate_compiler_runtime_pairs(runtimes):
        p, i, m = pim
        speedup = r2 / r1
    
        speedups[((c2, c1), pim)] = speedup
        outliers.merge(((c2, c1), pim), speedup, (speedup, pim))

        speedup_inv = r1 / r2
        speedups[((c1, c2), pim)] = speedup_inv
        outliers.merge(((c1, c2), pim), speedup_inv, (speedup_inv, pim))
    # print(outliers.pprint())

    # pattern level
    pattern_speedups = {}
    for (pair, (p, i, m)), speedup in speedups.items():
        update_dict_array(pattern_speedups, (pair, p), speedup)

    pattern_mean_speedup = {k:geometric_mean(speedups)
                            for k, speedups in pattern_speedups.items()}

    grouped = {}
    for (pair, p), mean_speedup in pattern_mean_speedup.items():
        if p == 'p001' and pair == ('icc', 'pgi'):
            print(p, pair, mean_speedup)
        if mean_speedup > 1.05:
            update_dict_array(grouped, pair, mean_speedup)

    data = {}
    neg_errs = {}
    pos_errs = {}
    for key, speedups in grouped.items():
        val = geometric_mean(speedups)
        all_ci = calculate_ci_geometric(speedups)
        ci95 = all_ci[1]

        data[key] = val
        neg_errs[key] = val - ci95[0]
        pos_errs[key] = ci95[1] - val

    return data, neg_errs, pos_errs, outliers
