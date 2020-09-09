from stats import \
    calculate_ci_geometric, \
    calculate_ci_proportion, \
    create_min_max_cases, \
    create_max_spread_cases, \
    Stats, \
    arithmetic_mean
from report.util import update_dict_dict, merge_value, get_paths_for_single, format_pair_raw_single_mutation
import plot
from random import choices
from tqdm import tqdm

def get_normalized_cost_model_performance(runtimes):
    grouped = {}
    compilers = set()
    for (compiler, mode, pattern, program, mutation), runtime in runtimes.items():
        compilers.add(compiler)
        key = (compiler, pattern, program, mutation)
        update_dict_dict(grouped, key, mode, runtime)

    best_nopredict = {}
    for (compiler, mode, *rest), runtime in runtimes.items():
        if mode == 'nopredict':
            merge_value(best_nopredict, (compiler, *rest[:-1]), runtime, min)

    n_cost_model_good = {}
    n_total_mutations = {}
    for compiler in compilers:
        n_cost_model_good[compiler] = 0
        n_total_mutations[compiler] = 0

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
                outliers.merge((compiler, rest), normalized, (raw, tuple(rest[-3:])))
            n_total_mutations[compiler] += 1

    normalized = {}
    for key, n_total in n_total_mutations.items():
        if n_total > 0:
            normalized[key] = (n_cost_model_good[key], n_total)

    return normalized, outliers

def add_plot_cost_model(compilers, patterns, runtimes):
    plots = {}
    for c in compilers:
        plots[c] = []

    for _ in tqdm(range(10000)):
        sample_patterns = choices(patterns, k=len(patterns))
        for c in compilers:
            n_good_cost_model = []
            for p, instances in sample_patterns:
                for i, mutations in instances:
                    for m in mutations:
                        with_cost_model = runtimes[(c, 'fast', p, i, m)]
                        without_cost_model = runtimes[(c, 'nopredict', p, i, m)]
                        is_good = without_cost_model >= with_cost_model * 0.95
                        n_good_cost_model.append(1 if is_good else 0)
            plots[c].append(arithmetic_mean(n_good_cost_model))

    for compiler, sample_stat in plots.items():
        print(plots[c][:100])
        plot.add_plot(sample_stat, label=compiler, min_val=0, max_val=1)
    plot.display_plot('cost model')

def plot_cost_model(runtimes):
    grouped = {}
    compilers = set()
    for (compiler, mode, pattern, program, mutation), runtime in runtimes.items():
        compilers.add(compiler)
        key = (compiler, pattern, program, mutation)
        update_dict_dict(grouped, key, mode, runtime)

    n_cost_model_good = {}
    for compiler in compilers:
        n_cost_model_good[compiler] = []

    for (compiler, *rest), mode_runtimes in grouped.items():
        if 'nopredict' in mode_runtimes and 'fast' in mode_runtimes:
            with_cost_model = mode_runtimes['fast']
            without_cost_model = mode_runtimes['nopredict']
            is_good = without_cost_model >= with_cost_model * 0.95
            n_cost_model_good[compiler].append(1 if is_good else 0)

    for compiler in sorted(list(compilers)):
        filtered = {}
        filtered[compiler] = n_cost_model_good[compiler]
        if plot.check_samples(f'cost model {compiler}', filtered[compiler]):
            plot.add_dict_array(filtered, arithmetic_mean, b=10000, min_val=0, max_val=1)
            plot.display_plot(f'{compiler} cost model stability')

def get_stats(runtimes):
    normalized, outliers = get_normalized_cost_model_performance(runtimes)

    cis = {}
    for compiler, (occurrences, total) in normalized.items():
        cis[compiler] = calculate_ci_proportion(occurrences, total)

    return Stats('Cost model stability', cis, outliers)

def get_paths(stats):
    return get_paths_for_single(stats)

def format_raw(raw):
    return format_pair_raw_single_mutation(raw)
