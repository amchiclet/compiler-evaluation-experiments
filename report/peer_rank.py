from stats import \
    calculate_ci_geometric, \
    calculate_ci_proportion, \
    create_min_max_cases, \
    create_max_spread_cases, \
    Stats
from util import merge_value, update_dict_dict
from scipy import log
from peer_metrics import iterate_compiler_runtime_pairs, x_faster_than_y_key, x_faster_than_y_pair
from loguru import logger

def add(x, y):
    return x + y

def get_rank_counts(runtimes):
    rank_counts = {}

    for (c1, r1), (c2, r2), _ in iterate_compiler_runtime_pairs(runtimes):
        if r1 < r2:
            merge_value(rank_counts, x_faster_than_y_key(c1, c2), 1, add)
        else:
            merge_value(rank_counts, x_faster_than_y_key(c2, c1), 1, add)

    return rank_counts

def normalized_key_pair(key):
    return tuple(sorted(x_faster_than_y_pair(key)))

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
