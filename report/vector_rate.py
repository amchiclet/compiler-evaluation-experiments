from stats import \
    calculate_ci_geometric, \
    calculate_ci_proportion, \
    create_min_max_cases, \
    create_max_spread_cases, \
    Stats
from util import merge_value, update_dict_array

def get_normalized_vector_rates(vector_rates):
    best_mutations = {}
    for key, vector_rate in vector_rates.items():
        if key[1] == 'fast':
            merge_value(best_mutations, key[:-1], vector_rate, max)

    outliers = create_min_max_cases()
    normalized = {}
    for key, vector_rate in vector_rates.items():
        if key[1] == 'fast':
            if best_mutations[key[:-1]] > 0:
                normalized[key] = vector_rate / best_mutations[key[:-1]]
                outliers.merge(key, normalized[key], vector_rate)

    return normalized, outliers

def get_vector_rate_stats(vector_rates):
    normalized, outliers = get_normalized_vector_rates(vector_rates)

    grouped = {}
    for (compiler, mode, pattern, program, mutation), runtime in normalized.items():
        update_dict_array(grouped, (compiler, mode), runtime)

    cis = {}
    for key, runtimes in grouped.items():
        cis[key] = calculate_ci_geometric(runtimes)

    interesting_cases = create_max_spread_cases()
    for (compiler, mode, *rest), [min_outlier, max_outlier] in outliers.cases.items():
        normalized_pair = (min_outlier.normalized, max_outlier.normalized)
        raw_pair = (min_outlier.raw, max_outlier.raw)
        interesting_cases.merge((compiler, mode, rest), normalized_pair, raw_pair)

    return Stats('Vector rate', cis, interesting_cases)
