from stats import \
    calculate_ci_geometric, \
    calculate_ci_proportion, \
    create_min_max_cases, \
    create_max_spread_cases, \
    Stats, \
    arithmetic_mean
from report.util import merge_value, update_dict_dict, update_dict_array
from scipy import log
from report.peer_metrics import iterate_compiler_runtime_pairs, x_faster_than_y_key, x_faster_than_y_pair, normalized_key_pair, is_approximate, x_approximates_y_key, is_faster_mention, is_approximate_mention, get_compiler_pairs, get_per_pattern_avg_runtimes, get_per_pattern_sum_log_runtimes
from loguru import logger
import plot
from random import choices
from tqdm import tqdm

def add(x, y):
    return x + y

def get_rank_counts(runtimes):
    rank_counts = {}

    for (c1, r1), (c2, r2), _ in iterate_compiler_runtime_pairs(runtimes):
        if is_approximate(r1, r2):
            merge_value(rank_counts, x_approximates_y_key(c1, c2), 1, add)
        else:
            if r1 < r2:
                merge_value(rank_counts, x_faster_than_y_key(c1, c2), 1, add)
            else:
                merge_value(rank_counts, x_faster_than_y_key(c2, c1), 1, add)

    return rank_counts

def plot_rank_counts(runtimes):
    compilers = set()
    rank_counts = {}
    for (c1, r1), (c2, r2), _ in iterate_compiler_runtime_pairs(runtimes):
        compilers.add(c1)
        compilers.add(c2)
        if is_approximate(r1, r2):
            merge_value(rank_counts, x_approximates_y_key(c1, c2), [1], add)
            merge_value(rank_counts, x_faster_than_y_key(c1, c2), [0], add)
            merge_value(rank_counts, x_faster_than_y_key(c2, c1), [0], add)
        else:
            if r1 < r2:
                merge_value(rank_counts, x_approximates_y_key(c1, c2), [0], add)
                merge_value(rank_counts, x_faster_than_y_key(c1, c2), [1], add)
                merge_value(rank_counts, x_faster_than_y_key(c2, c1), [0], add)
            else:
                merge_value(rank_counts, x_approximates_y_key(c1, c2), [0], add)
                merge_value(rank_counts, x_faster_than_y_key(c1, c2), [0], add)
                merge_value(rank_counts, x_faster_than_y_key(c2, c1), [1], add)
    for compiler in sorted(list(compilers)):
        filtered = {}
        for k, v in rank_counts.items():
            if is_faster_mention(k, compiler) or is_approximate_mention(k, compiler):
                if plot.check_samples(f'peer rank {k}', v):
                    filtered[k] = v
        plot.add_dict_array(filtered, arithmetic_mean, b=10000, min_val=0, max_val=1)
        plot.display_plot(f'{compiler} peer rank')

def get_rankings(runtimes):
    rankings = {}
    for (c1, r1), (c2, r2), pim in iterate_compiler_runtime_pairs(runtimes):
        if is_approximate(r1, r2):
            rankings[(x_approximates_y_key(c1, c2), pim)] = 1
            rankings[(x_faster_than_y_key(c1, c2), pim)] = 0
            rankings[(x_faster_than_y_key(c2, c1), pim)] = 0
        else:
            if r1 < r2:
                rankings[(x_approximates_y_key(c1, c2), pim)] = 0
                rankings[(x_faster_than_y_key(c1, c2), pim)] = 1
                rankings[(x_faster_than_y_key(c2, c1), pim)] = 0
            else:
                rankings[(x_approximates_y_key(c1, c2), pim)] = 0
                rankings[(x_faster_than_y_key(c1, c2), pim)] = 0
                rankings[(x_faster_than_y_key(c2, c1), pim)] = 1
    return rankings

def add_plot_rank_counts(compilers, patterns, runtimes, fig_path=None):
    rankings_map = get_rankings(runtimes)

    plots = {}
    for (c1, c2) in get_compiler_pairs(compilers):
        plots[x_approximates_y_key(c1, c2)] = []
        plots[x_faster_than_y_key(c1, c2)] = []
        plots[x_faster_than_y_key(c2, c1)] = []

    for _ in tqdm(range(10000)):
        sample_patterns = choices(patterns, k=len(patterns))
        for (c1, c2) in get_compiler_pairs(compilers):
            keys = [x_approximates_y_key(c1, c2),
                    x_faster_than_y_key(c1, c2),
                    x_faster_than_y_key(c2, c1)]
            for pair in keys:
                rankings = []
                for p, instances in sample_patterns:
                    for i, mutations in instances:
                        for m in mutations:
                            rankings.append(rankings_map[(pair, (p, i, m))])
                plots[pair].append(arithmetic_mean(rankings))

    colors = 'bgrcmyk'
    for (pair, sample_stat), color in zip(plots.items(), colors):
        plot.add_plot(sample_stat, label=pair, color=color, min_val=0, max_val=1)
    if fig_path is None:
        plot.display_plot('peer rank')
    else:
        plot.save_plot(fig_path, 'peer rank')
        plot.clear_plot()

def get_total_counts(rank_counts):
    total_counts = {}
    for k, v in rank_counts.items():
        merge_value(total_counts, normalized_key_pair(k), v, add)
    return total_counts

def get_stats(runtimes):
    cis = {}
    rank_counts = get_rank_counts(runtimes)
    total_counts = get_total_counts(rank_counts)
    for rank_key, occurrences in rank_counts.items():
        total = total_counts[normalized_key_pair(rank_key)]
        cis[rank_key] = calculate_ci_proportion(occurrences, total)
    return Stats('Peer rank', cis, None)

def get_rankings_v2(runtimes):
    rankings = {}
    for (c1, r1), (c2, r2), pim in iterate_compiler_runtime_pairs(runtimes):
        if is_approximate(r1, r2):
            rankings[((c1, c2), pim)] = 0
            rankings[((c2, c1), pim)] = 0
        else:
            if r1 < r2:
                rankings[((c1, c2), pim)] = 1
                rankings[((c2, c1), pim)] = 0
            else:
                rankings[((c1, c2), pim)] = 0
                rankings[((c2, c1), pim)] = 1
    return rankings

def get_data_and_errors(compilers, n_patterns, runtimes):
    rankings_map = get_rankings_v2(runtimes)

    # ranking_map
    # ((better_c, ref_c), pim) => 0 or 1
    grouped = {}
    for (pair, pim), runtime in rankings_map.items():
        update_dict_array(grouped, pair, runtime)

    data = {}
    neg_errs = {}
    pos_errs = {}
    for key, flags in grouped.items():
        occurrences = sum(flags)
        total = len(flags)
        all_ci = calculate_ci_proportion(occurrences, total, n_patterns)
        ci95 = all_ci[1]

        val = occurrences / total
        data[key] = val
        neg_errs[key] = val - ci95[0]
        pos_errs[key] = ci95[1] - val
    return data, neg_errs, pos_errs

def get_data_and_errors_v2(compilers, patterns, runtimes):
    n_mutations = 0
    n_patterns = 0
    win_count_map = {c:0 for c in compilers}
    for p, instances in patterns:
        for i, mutations in instances:
            for m in mutations:
                pim = (p, i, m)
                rs = {c:runtimes[(c, 'fast', *pim)] for c in compilers}
                winner = min(rs.values())
                winner_threshold = winner * 1.05
                for c in compilers:
                    if rs[c] < winner_threshold:
                        win_count_map[c] += 1
                n_mutations += 1
        n_patterns += 1

    data = {}
    neg_errs = {}
    pos_errs = {}
    for compiler, win_count in win_count_map.items():
        all_ci = calculate_ci_proportion(win_count, n_mutations, n_patterns)
        ci95 = all_ci[1]

        val = win_count / n_mutations
        data[compiler] = val
        neg_errs[compiler] = val - ci95[0]
        pos_errs[compiler] = ci95[1] - val
    return data, neg_errs, pos_errs, None

def get_data_and_errors_top(compilers, patterns, runtimes):
    p, instances = next(iter(patterns))
    i, mutations = next(iter(instances))
    n_mutations_per_pattern = len(instances) * len(mutations)

    pattern_sum_log_runtimes = get_per_pattern_sum_log_runtimes(runtimes)
    pairs = get_compiler_pairs(compilers)

    win_count_map = {c:0 for c in compilers}
    for p, _ in patterns:
        sum_logs = {c:pattern_sum_log_runtimes[(c, p)] for c in compilers}
        winner = min(sum_logs.values())
        winner_threshold = n_mutations_per_pattern * log(1.05) + winner
        for c in compilers:
            if sum_logs[c] < winner_threshold:
                win_count_map[c] += 1

    n_patterns = len(patterns)

    data = {}
    neg_errs = {}
    pos_errs = {}
    for compiler, win_count in win_count_map.items():
        all_ci = calculate_ci_proportion(win_count, n_patterns)
        ci95 = all_ci[1]

        val = win_count / n_patterns
        data[compiler] = val
        neg_errs[compiler] = val - ci95[0]
        pos_errs[compiler] = ci95[1] - val
    return data, neg_errs, pos_errs, None

def get_rankings_v2(runtimes):
    rankings = {}
    for (c1, r1), (c2, r2), pim in iterate_compiler_runtime_pairs(runtimes):
        if is_approximate(r1, r2):
            rankings[((c1, c2), pim)] = 0
            rankings[((c2, c1), pim)] = 0
        else:
            if r1 < r2:
                rankings[((c1, c2), pim)] = 1
                rankings[((c2, c1), pim)] = 0
            else:
                rankings[((c1, c2), pim)] = 0
                rankings[((c2, c1), pim)] = 1
    return rankings

def get_data_and_errors_pair(compilers, patterns, runtimes):
    p, instances = next(iter(patterns))
    i, mutations = next(iter(instances))
    n_mutations_per_pattern = len(instances) * len(mutations)

    pattern_sum_log_runtimes = get_per_pattern_sum_log_runtimes(runtimes)
    pairs = get_compiler_pairs(compilers)

    win_counts = {}
    for (c1, c2) in pairs:
        win_counts[(c1, c2)] = 0
        win_counts[(c2, c1)] = 0

    for (c1, c2) in pairs:
        for p, _ in patterns:
            r1 = pattern_sum_log_runtimes[(c1, p)]
            r2 = pattern_sum_log_runtimes[(c2, p)]
            if (r1 - r2)/n_mutations_per_pattern > log(1.05):
                if c2 == 'pgi' and c1 == 'icc':
                    print('hey', p)
                win_counts[(c2, c1)] += 1
            if (r2 - r1)/n_mutations_per_pattern > log(1.05):
                if c1 == 'pgi' and c2 == 'icc':
                    print('yo', p)
                win_counts[(c1, c2)] += 1

    n_patterns = len(patterns)
    data = {}
    neg_errs = {}
    pos_errs = {}
    for pair, win_count in win_counts.items():
        all_ci = calculate_ci_proportion(win_count, n_patterns)
        ci95 = all_ci[1]

        val = win_count / n_patterns
        data[pair] = val
        neg_errs[pair] = val - ci95[0]
        pos_errs[pair] = ci95[1] - val
    return data, neg_errs, pos_errs
