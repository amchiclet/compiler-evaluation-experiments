from stats import \
    calculate_ci_geometric, \
    calculate_ci_proportion, \
    create_min_max_cases, \
    create_max_spread_cases, \
    Stats
from util import merge_value, update_dict_dict

vectorizable_threshold = 1.00
def get_normalized_vectorizables(runtimes):
    compilers = set()
    grouped = {}
    for (compiler, mode, pattern, program, mutation), runtime in runtimes.items():
        compilers.add(compiler)
        key = (compiler, pattern, program, mutation)
        update_dict_dict(grouped, key, mode, runtime)

    speedups = {}
    for key, mode_runtimes in grouped.items():
        if 'novec' in mode_runtimes and 'fast' in mode_runtimes:
            speedups[key] = mode_runtimes['novec'] / mode_runtimes['fast']

    best_speedups = {}
    for key, speedup in speedups.items():
        merge_value(best_speedups, key[:-1], speedup, max)

    n_vectorizables = {}
    n_actually_vectorized = {}
    for compiler in compilers:
        n_vectorizables[compiler] = 0
        n_actually_vectorized[compiler] = 0

    for key, speedup in speedups.items():
        compiler = key[0]
        best_speedup = best_speedups[key[:-1]]
        if best_speedup > vectorizable_threshold:
            n_vectorizables[compiler] += 1
            if speedup > vectorizable_threshold:
                n_actually_vectorized[compiler] += 1

    normalized = {}
    for key, n_total in n_vectorizables.items():
        if n_total > 0:
            normalized[key] = (n_actually_vectorized[key], n_total)

    return normalized

def get_stats(runtimes):
    normalized = get_normalized_vectorizables(runtimes)
    cis = {}
    for key, (occurrences, total) in normalized.items():
        cis[key] = calculate_ci_proportion(occurrences, total)
    return Stats('Vectorizables', cis, None)
