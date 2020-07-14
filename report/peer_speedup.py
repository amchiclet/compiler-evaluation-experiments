from stats import \
    calculate_ci_geometric, \
    calculate_ci_proportion, \
    create_min_max_cases, \
    create_max_spread_cases, \
    Stats
from util import merge_value, update_dict_dict, update_dict_array, get_paths_for_pair, format_spread_pair

from scipy import log

def get_normalized_peer_speedups(runtimes):
    compiler_set = set()
    grouped = {}
    for (compiler, mode, pattern, program, mutation), runtime in runtimes.items():
        if mode == 'fast':
            compiler_set.add(compiler)
            key = (pattern, program, mutation)
            update_dict_dict(grouped, key, compiler, runtime)
    compilers = list(compiler_set)

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

    speedups = {}
    for key in keys_to_consider:
        for (slower, faster) in ascend_perf_pairs:
            slower_key = (slower, 'fast', *key)
            faster_key = (faster, 'fast', *key)
            speedups[(slower, faster, *key)] = runtimes[slower_key] / runtimes[faster_key]

    best_speedups = {}
    for key, speedup in speedups.items():
        merge_value(best_speedups, key[:-1], speedup, max)

    outliers = create_min_max_cases()
    normalized = {}
    for key, speedup in speedups.items():
        normalized[key] = speedup / best_speedups[key[:-1]]
        mutation_id = key[-3:]
        outliers.merge(key, normalized[key], (speedup, mutation_id))

    return normalized, outliers

def get_stats(runtimes):
    normalized, outliers = get_normalized_peer_speedups(runtimes)

    grouped = {}
    for (c1, c2, *rest), runtime in normalized.items():
        update_dict_array(grouped, (c1, c2), runtime)

    cis = {}
    for key, runtimes in grouped.items():
        cis[key] = calculate_ci_geometric(runtimes)

    interesting_cases = create_max_spread_cases()
    for (c1, c2, *rest), [min_outlier, max_outlier] in outliers.cases.items():
        normalized_pair = (min_outlier.normalized, max_outlier.normalized)
        raw_pair = (min_outlier.raw, max_outlier.raw)
        interesting_cases.merge((c1, c2, rest), normalized_pair, raw_pair)
    return Stats('Peer speedup stability', cis, interesting_cases)

def get_paths(stats):
    return get_paths_for_pair(stats)

def format_raw(raw):
    return format_spread_pair(raw)
