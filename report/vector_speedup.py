from stats import \
    calculate_ci_geometric, \
    calculate_ci_proportion, \
    create_min_max_cases, \
    create_max_spread_cases, \
    Stats
from util import update_dict_dict, merge_value, update_dict_array, get_paths_for_pair, format_spread_pair

def get_normalized_vec_speedups(runtimes):
    grouped = {}
    for (compiler, mode, pattern, program, mutation), runtime in runtimes.items():
        key = (compiler, pattern, program, mutation)
        update_dict_dict(grouped, key, mode, runtime)

    speedups = {}
    for key, mode_runtimes in grouped.items():
        if 'novec' in mode_runtimes and 'fast' in mode_runtimes:
            speedups[key] = mode_runtimes['novec'] / mode_runtimes['fast']

    best_speedups = {}
    for key, speedup in speedups.items():
        merge_value(best_speedups, key[:-1], speedup, max)

    outliers = create_min_max_cases()
    normalized = {}
    for key, speedup in speedups.items():
        normalized[key] = speedup / best_speedups[key[:-1]]
        outliers.merge(key, normalized[key], (speedup, key[-3:]))

    return normalized, outliers

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
        cis[key] = calculate_ci_geometric(runtimes)

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
