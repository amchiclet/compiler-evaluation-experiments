from stats import \
    calculate_ci_geometric, \
    calculate_ci_proportion, \
    create_min_max_cases, \
    create_max_spread_cases, \
    Stats
from util import merge_value, update_dict_dict
from compilers import compilers
from scipy import log

def get_normalized_peer_ranks(runtimes):
    grouped = {}
    for (compiler, mode, pattern, program, mutation), runtime in runtimes.items():
        if mode == 'fast':
            key = (pattern, program, mutation)
            update_dict_dict(grouped, key, compiler, runtime)

    keys_to_consider = []
    overall_runtime = {}
    for key, compiler_runtimes in grouped.items():
        if all([compiler in compiler_runtimes for compiler in compilers]):
            keys_to_consider.append(key)
            for compiler, runtime in compiler_runtimes.items():
                merge_value(overall_runtime, compiler, runtime,
                            lambda v1, v2: log(v1) + log(v2))

    ascend_perf_pairs = []
    for i, c1 in enumerate(compilers[:-1]):
        for c2 in compilers[i+1:]:
            # lower runtime means better performance
            ascend_perf = (c2, c1) if overall_runtime[c1] < overall_runtime[c2] else (c1, c2)
            ascend_perf_pairs.append(ascend_perf)

    correct_ranks = {}
    for key in ascend_perf_pairs:
        correct_ranks[key] = 0
    for key in keys_to_consider:
        for (slower, faster) in ascend_perf_pairs:
            slower_key = (slower, 'fast', *key)
            faster_key = (faster, 'fast', *key)
            if runtimes[slower_key] > runtimes[faster_key]:
                correct_ranks[(slower, faster)] += 1

    normalized = {}
    n_mutation_count = len(keys_to_consider)
    for key, count in correct_ranks.items():
        normalized[key] = (count, n_mutation_count)

    return normalized

def get_peer_rank_stats(runtimes):
    normalized = get_normalized_peer_ranks(runtimes)
    cis = {}
    for key, (occurrences, total) in normalized.items():
        cis[key] = calculate_ci_proportion(occurrences, total)
    return Stats('Peer rank', cis, None)
