from stats import \
    calculate_ci_geometric, \
    calculate_ci_arithmetic, \
    calculate_ci_proportion, \
    create_min_max_cases, \
    create_max_spread_cases, \
    Stats, \
    arithmetic_mean
from report.util import update_dict_dict, merge_value, get_paths_for_single, format_pair_raw_single_mutation, update_dict_array
import plot
from random import choices
from tqdm import tqdm
from scipy.stats import probplot
import matplotlib.pyplot as plt

normal_threshold=100
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

def add_plot_cost_model(compilers, patterns, runtimes, fig_path=None):
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
        plot.add_plot(sample_stat, label=compiler, min_val=0, max_val=1)
    if fig_path is None:
        plot.display_plot('cost model')
    else:
        plot.save_plot(fig_path, 'cost model')
        plot.clear_plot()

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

def plot_ci_bars(n_patterns, raw_runtimes, fig_path=None):
    normalized, _ = get_normalized_cost_model_performance(runtimes)

    proportions = {}
    cis = {}
    for compiler, (occurrences, total) in normalized.items():
        all_ci = calculate_ci_proportion(occurrences, total, n_patterns)
        cis[compiler] = all_ci[1]
        proportions[compiler] = occurrences / total

    plot.add_bar(proportions, cis)

    if fig_path is None:
        plot.display_plot('cost model')
    else:
        plot.save_plot(fig_path, 'cost model')
        plot.clear_plot()

def get_paths(stats):
    return get_paths_for_single(stats)

def format_raw(raw):
    return format_pair_raw_single_mutation(raw)

def get_data_and_errors(n_patterns, raw_runtimes):
    normalized, outliers = get_normalized_cost_model_performance(raw_runtimes)

    proportions = {}
    neg_errs = {}
    pos_errs = {}
    for compiler, (occurrences, total) in normalized.items():
        all_ci = calculate_ci_proportion(occurrences, total, n_patterns)
        ci95 = all_ci[1]
        val = occurrences / total
        proportions[compiler] = val
        neg_errs[compiler] = val - ci95[0]
        pos_errs[compiler] = ci95[1] - val

    # print('cost model')
    # print(outliers.pprint())
    return proportions, neg_errs, pos_errs, outliers

def get_data_and_errors_v2(compilers, patterns, runtimes):
    outliers = create_max_spread_cases()
    per_pattern_map = {}
    for c in compilers:
        for p, instances in patterns:
            for i, mutations in instances:
                best_no_predict = min([runtimes[(c, 'nopredict', p, i, m)] for m in mutations])

                for m in mutations:
                    pim = (p, i, m)
                    with_cost_model_key = (c, 'fast', *pim)
                    no_cost_model_key = (c, 'nopredict', *pim)
                    assert(with_cost_model_key in runtimes)
                    assert(no_cost_model_key in runtimes)
                    no_cost_model = runtimes[no_cost_model_key]
                    with_cost_model = runtimes[with_cost_model_key]

                    is_good = with_cost_model < 1.05 * no_cost_model
                    if is_good:
                        good_count = 1
                    else:
                        good_count = 0
                        spread = (best_no_predict/with_cost_model, best_no_predict/no_cost_model)
                        raw = (no_cost_model, with_cost_model)
                        outliers.merge((c, pim), spread, (raw, pim))
                    update_dict_array(per_pattern_map, (c, p), good_count)

    percentages_map = {}
    for (compiler, _), counts in per_pattern_map.items():
        update_dict_array(percentages_map, compiler, arithmetic_mean(counts))

    data = {}
    neg_errs = {}
    pos_errs = {}
    for compiler, percentages in percentages_map.items():
        assert(len(percentages) == len(patterns))
        val = arithmetic_mean(percentages)
        data[compiler] = val
        if len(percentages) > normal_threshold:
            all_ci = calculate_ci_arithmetic(percentages)
            ci95 = all_ci[1]
            neg_errs[compiler] = val - ci95[0]
            pos_errs[compiler] = ci95[1] - val
        else:
            neg_errs[compiler] = None
            pos_errs[compiler] = None

    # print('cost model')
    # print(outliers.pprint())
    return data, neg_errs, pos_errs, outliers

def get_data_and_errors_v3(compilers, patterns, runtimes):
    outliers = create_max_spread_cases()
    per_pattern_map = {}
    for c in compilers:
        for p, instances in patterns:
            for i, mutations in instances:
                best_no_predict = min([runtimes[(c, 'nopredict', p, i, m)] for m in mutations])

                for m in mutations:
                    pim = (p, i, m)
                    with_cost_model_key = (c, 'fast', *pim)
                    no_cost_model_key = (c, 'nopredict', *pim)
                    assert(with_cost_model_key in runtimes)
                    assert(no_cost_model_key in runtimes)
                    no_cost_model = runtimes[no_cost_model_key]
                    with_cost_model = runtimes[with_cost_model_key]

                    is_good = with_cost_model < 1.05 * no_cost_model
                    if is_good:
                        good_count = 1
                    else:
                        good_count = 0
                        spread = (best_no_predict/with_cost_model, best_no_predict/no_cost_model)
                        raw = (no_cost_model, with_cost_model)
                        outliers.merge((c, pim), spread, (raw, pim))
                    update_dict_array(per_pattern_map, (c, p), good_count)

    percentages_map = {}
    for (compiler, _), counts in per_pattern_map.items():
        update_dict_array(percentages_map, compiler, arithmetic_mean(counts))

    data = {}
    neg_errs = {}
    pos_errs = {}
    for compiler, percentages in percentages_map.items():
        assert(len(percentages) == len(patterns))
        val = arithmetic_mean(percentages)
        data[compiler] = val
        if len(percentages) > normal_threshold:
            all_ci = calculate_ci_arithmetic(percentages)
            ci95 = all_ci[1]
            neg_errs[compiler] = val - ci95[0]
            pos_errs[compiler] = ci95[1] - val
        else:
            neg_errs[compiler] = None
            pos_errs[compiler] = None

    # print('cost model')
    # print(outliers.pprint())
    return data, neg_errs, pos_errs, outliers

def plot_qq(compilers, patterns, runtimes):
    per_pattern_map = {}
    for c in compilers:
        for p, instances in patterns:
            for i, mutations in instances:
                for m in mutations:
                    pim = (p, i, m)
                    with_cost_model_key = (c, 'fast', *pim)
                    no_cost_model_key = (c, 'nopredict', *pim)
                    assert(with_cost_model_key in runtimes)
                    assert(no_cost_model_key in runtimes)
                    no_cost_model = runtimes[no_cost_model_key]
                    with_cost_model = runtimes[with_cost_model_key]

                    is_good = with_cost_model < 1.05 * no_cost_model
                    if is_good:
                        good_count = 1
                    else:
                        good_count = 0
                    update_dict_array(per_pattern_map, (c, p), good_count)

    percentages_map = {}
    for (compiler, _), counts in per_pattern_map.items():
        update_dict_array(percentages_map, compiler, arithmetic_mean(counts))

    for vals in percentages_map.values():
        data = []
        for _ in tqdm(range(1000)):
            samples = choices(vals, k=len(vals))
            data.append(arithmetic_mean(samples))
        probplot(data, plot=plt)
        plt.show()
