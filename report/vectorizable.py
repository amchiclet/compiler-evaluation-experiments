from stats import \
    calculate_ci_geometric, \
    calculate_ci_proportion, \
    create_min_max_cases, \
    create_max_spread_cases, \
    Stats, \
    arithmetic_mean
from report.util import merge_value, update_dict_dict
from report.vector_speedup import get_vec_speedups
import plot

vectorizable_threshold = 1.15

def get_normalized_vectorizables(runtimes):
    compilers, speedups, best_speedups = get_vec_speedups(runtimes)

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

def plot_vectorizables(runtimes):
    compilers, speedups, best_speedups = get_vec_speedups(runtimes)

    n_actually_vectorized = {}
    for c in compilers:
        n_actually_vectorized[c] = []

    for key, speedup in speedups.items():
        compiler = key[0]
        best_speedup = best_speedups[key[:-1]]
        if best_speedup > vectorizable_threshold:
            n_actually_vectorized[c].append(1 if speedup > vectorizable_threshold else 0)

    for compiler in sorted(list(compilers)):
        filtered = {}
        filtered[compiler] = n_actually_vectorized[compiler]
        if plot.check_samples(f'vectorizable {compiler}', filtered[compiler]):
            plot.add_dict_array(filtered, arithmetic_mean, b=10000, min_val=0, max_val=1)
            plot.display_plot(f'{compiler} vectorizability stability')

def get_stats(runtimes):
    normalized = get_normalized_vectorizables(runtimes)
    cis = {}
    for key, (occurrences, total) in normalized.items():
        cis[key] = calculate_ci_proportion(occurrences, total)
    return Stats('Vectorizables', cis, None)
