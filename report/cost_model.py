from stats import \
    calculate_ci_geometric, \
    calculate_ci_proportion, \
    create_min_max_cases, \
    create_max_spread_cases, \
    Stats
from util import update_dict_dict, merge_value

def get_normalized_cost_model_performance(runtimes):
    grouped = {}
    compilers = set()
    for (compiler, mode, pattern, program, mutation), runtime in runtimes.items():
        compilers.add(compiler)
        key = (compiler, pattern, program, mutation)
        update_dict_dict(grouped, key, mode, runtime)

    n_cost_model_good = {}
    n_total_mutations = {}
    for compiler in compilers:
        n_cost_model_good[compiler] = 0
        n_total_mutations[compiler] = 0

    best_nopredict = {}
    for (compiler, mode, *rest), runtime in runtimes.items():
        if mode == 'nopredict':
            merge_value(best_nopredict, (compiler, *rest[:-1]), runtime, min)

    outliers = create_max_spread_cases()

    for (compiler, *rest), mode_runtimes in grouped.items():
        if 'nopredict' in mode_runtimes and 'fast' in mode_runtimes:
            with_cost_model = mode_runtimes['fast']
            without_cost_model = mode_runtimes['nopredict']
            if without_cost_model >= with_cost_model * 0.95:
                n_cost_model_good[compiler] += 1
            else:
                best = best_nopredict[(compiler, *rest[:-1])]
                normalized = (best/with_cost_model, best/without_cost_model)
                raw = (without_cost_model, with_cost_model)
                outliers.merge((compiler, rest), normalized, raw)
            n_total_mutations[compiler] += 1

    normalized = {}
    for key, n_total in n_total_mutations.items():
        if n_total > 0:
            normalized[key] = (n_cost_model_good[key], n_total)

    return normalized, outliers

def get_cost_model_stats(runtimes):
    normalized, outliers = get_normalized_cost_model_performance(runtimes)

    cis = {}
    for compiler, (occurrences, total) in normalized.items():
        cis[(compiler,)] = calculate_ci_proportion(occurrences, total)

    return Stats('Cost model stability', cis, outliers)
