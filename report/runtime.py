from stats import \
    calculate_ci_geometric, \
    calculate_ci_proportion, \
    create_min_max_cases, \
    create_max_spread_cases, \
    Stats
from util import merge_value, update_dict_array

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
            outliers.merge(key, normalized[key], (runtime, mutation))

    return normalized, outliers

def get_runtime_stats(runtimes):
    normalized, outliers = get_normalized_runtimes(runtimes)

    grouped = {}
    for (compiler, pattern, program, mutation), runtime in normalized.items():
        update_dict_array(grouped, (compiler,), runtime)

    cis = {}
    for key, runtimes in grouped.items():
        cis[key] = calculate_ci_geometric(runtimes)

    interesting_cases = create_max_spread_cases()
    for (compiler, *rest), [min_outlier, max_outlier] in outliers.cases.items():
        normalized_pair = (min_outlier.normalized, max_outlier.normalized)
        # max normalized means min raw runtime
        raw_pair = (max_outlier.raw, min_outlier.raw)
        interesting_cases.merge((compiler, rest), normalized_pair, raw_pair)
    return Stats('Runtime stability', cis, interesting_cases)
