from stats import \
    calculate_ci_geometric, \
    calculate_ci_proportion, \
    create_min_max_cases, \
    create_max_spread_cases, \
    Stats, \
    arithmetic_mean
from report.util import merge_value, update_dict_dict
from scipy import log
from report.peer_metrics import iterate_compiler_runtime_pairs, x_faster_than_y_key, x_faster_than_y_pair, normalized_key_pair, is_approximate, x_approximates_y_key, is_faster_mention, is_approximate_mention
from loguru import logger
import plot

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
