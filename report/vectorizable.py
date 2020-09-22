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
from random import choices
from tqdm import tqdm

vectorizable_threshold = 1.15

def get_normalized_vectorizables(runtimes):
    compilers, speedups, best_speedups = get_vec_speedups(runtimes)

    vectorizable_patterns = set()
    n_vectorizables = {}
    n_actually_vectorized = {}
    for compiler in compilers:
        n_vectorizables[compiler] = 0
        n_actually_vectorized[compiler] = 0

    for key, speedup in speedups.items():
        compiler = key[0]
        pattern = key[1]

        best_speedup = best_speedups[key[:-1]]
        if best_speedup > vectorizable_threshold:
            vectorizable_patterns.add(pattern)
            n_vectorizables[compiler] += 1
            if speedup > vectorizable_threshold:
                n_actually_vectorized[compiler] += 1

    normalized = {}
    for key, n_total in n_vectorizables.items():
        if n_total > 0:
            normalized[key] = (n_actually_vectorized[key], n_total, len(vectorizable_patterns))

    return normalized

def add_plot_vectorizables(compilers, patterns, runtimes, fig_path=None):
    _, speedups, best_speedups = get_vec_speedups(runtimes)
    plots = {}
    n_vectorized_map = {}
    for c in compilers:
        plots[c] = []
        n_vectorized_map[c] = []
    for _ in tqdm(range(10000)):
        sample_patterns = choices(patterns, k=len(patterns))
        for c in compilers:
            n_vectorized = []
            for p, instances in sample_patterns:
                for i, mutations in instances:
                    if best_speedups[(c, p, i)] < vectorizable_threshold:
                        continue
                    for m in mutations:
                        speedup = speedups[(c, p, i, m)]
                        is_vectorizable = speedup >= vectorizable_threshold
                        n_vectorized.append(1 if is_vectorizable else 0)
            plots[c].append(arithmetic_mean(n_vectorized))
            n_vectorized_map[c].append(len(n_vectorized))

    for compiler, sample_stat in plots.items():
        plot.add_plot(sample_stat, label=compiler, min_val=0, max_val=1)
    if fig_path is None:
        plot.display_plot('vectorized')
    else:
        plot.save_plot(fig_path, 'vectororized')
        plot.clear_plot()

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
    for key, (occurrences, total, _) in normalized.items():
        cis[key] = calculate_ci_proportion(occurrences, total)
    return Stats('Vectorizables', cis, None)

def plot_ci_bar(raw_runtimes, fig_path=None):
    normalized = get_normalized_vectorizables(raw_runtimes)

    proportions = {}
    cis = {}
    for key, (occurrences, total, n_patterns) in normalized.items():
        all_ci = calculate_ci_proportion(occurrences, total, n_patterns)
        cis[key] = all_ci[1]
        proportions[key] = occurrences / total
    plot.add_bar(proportions, cis)
    if fig_path is None:
        plot.display_plot('vectorizables')
    else:
        plot.save_plot(fig_path, 'vectorizables')
        plot.clear_plot()

def get_data_and_errors(raw_runtimes):
    normalized = get_normalized_vectorizables(raw_runtimes)

    proportions = {}
    neg_errs = {}
    pos_errs = {}
    for key, (occurrences, total, n_patterns) in normalized.items():
        all_ci = calculate_ci_proportion(occurrences, total, n_patterns)
        ci95 = all_ci[1]
        val = occurrences / total
        proportions[key] = val
        neg_errs[key] = val - ci95[0]
        pos_errs[key] = ci95[1] - val
    return proportions, neg_errs, pos_errs
