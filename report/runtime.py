from stats import \
    calculate_ci_geometric, \
    calculate_ci_proportion, \
    create_min_max_cases, \
    create_max_spread_cases, \
    Stats
from util import merge_value, update_dict_array

def get_normalized_runtimes(runtimes):
    best_mutations = {}
    for key, runtime in runtimes.items():
        if key[1] == 'fast':
            merge_value(best_mutations, key[:-1], runtime, min)

    outliers = create_min_max_cases()
    normalized = {}
    for key, runtime in runtimes.items():
        if key[1] == 'fast':
            normalized[key] = best_mutations[key[:-1]] / runtime
            outliers.merge(key, normalized[key], runtime)

    return normalized, outliers

def get_runtime_stats(runtimes):
    normalized, outliers = get_normalized_runtimes(runtimes)

    grouped = {}
    for (compiler, mode, pattern, program, mutation), runtime in normalized.items():
        update_dict_array(grouped, (compiler, mode), runtime)

    cis = {}
    for key, runtimes in grouped.items():
        cis[key] = calculate_ci_geometric(runtimes)

    interesting_cases = create_max_spread_cases()
    for (compiler, mode, *rest), [min_outlier, max_outlier] in outliers.cases.items():
        normalized_pair = (min_outlier.normalized, max_outlier.normalized)
        # max normalized means min raw runtime
        raw_pair = (max_outlier.raw, min_outlier.raw)
        interesting_cases.merge((compiler, mode, rest), normalized_pair, raw_pair)

    return Stats('Runtime stability', cis, interesting_cases)
