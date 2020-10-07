from stats import \
    calculate_ci_geometric, \
    calculate_ci_proportion, \
    create_min_max_cases, \
    create_max_spread_cases, \
    Stats, \
    geometric_mean
from report.util import merge_value, update_dict_array, get_paths_for_pair, format_spread_pair, update_dddl, update_ddl
import plot
from tqdm import tqdm
from random import choices, sample, shuffle
import matplotlib.pyplot as plt

normal_threshold = 100

def plot_ci_bar(n_patterns, raw_runtimes, fig_path=None):
    normalized, _ = get_normalized_runtimes(raw_runtimes)

    grouped = {}
    for (compiler, pattern, program, mutation), runtime in normalized.items():
        update_dict_array(grouped, compiler, runtime)

    means = {}
    cis = {}
    for key, runtimes in grouped.items():
        all_ci = calculate_ci_geometric(runtimes, 0.0, 1.0, n_patterns)
        cis[key] = all_ci[1]
        means[key] = geometric_mean(runtimes)

    plot.add_bar(means, cis)

    if fig_path is None:
        plot.display_plot('runtime stability')
    else:
        plot.save_plot(fig_path, 'runtime stability')
        plot.clear_plot()

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
            outliers.merge(key, normalized[key], (runtime, key[-3:]))

    return normalized, outliers

def plot_normalized_runtimes(n_patterns, n_instances, runtimes):
    normalized, _ = get_normalized_runtimes(runtimes)
    grouped = {}
    for (compiler, pattern, instance, mutation), runtime in normalized.items():
        update_dddl(grouped, compiler, pattern, instance, runtime)
        compilers.add(compiler)

    for compiler in sorted(list(compilers)):
        filtered = {k:v for k,v in grouped.items() if k == compiler}
        # plot.add_dict_array(filtered, geometric_mean, b=10000, min_val=0, max_val=1)
        plot.add_dddl(filtered,
                      geometric_mean,
                      n_patterns=None,
                      n_instances=None,
                      b=10000,
                      min_val=0,
                      max_val=1)
        plot.display_plot(f'{compiler} runtime stability')

def add_plot_normalized_runtimes_v2(compilers, patterns, runtimes, fig_path=None):
    normalized, _ = get_normalized_runtimes(runtimes)
    print(normalized)
    plots = {}
    for c in compilers:
        plots[c] = []

    print(f'total patterns {len(patterns)}')
    for _ in tqdm(range(10000)):
        sample_patterns = choices(patterns, k=len(patterns))
        for c in compilers:
            rs = []
            for p, instances in sample_patterns:
                for i, mutations in instances:
                    for m in mutations:
                        rs.append(normalized[(c, p, i, m)])
            plots[c].append(geometric_mean(rs))

    for compiler, sample_stat in plots.items():
        plot.add_plot(sample_stat, label=compiler, min_val=0, max_val=1)
    if fig_path is None:
        plot.display_plot('normalized runtimes')
    else:
        plot.save_plot(fig_path, 'normalized runtimes')
        plot.clear_plot()

def add_plot_normalized_runtimes(compiler, runtimes, label):
    normalized, _ = get_normalized_runtimes(runtimes)
    grouped = {}
    for (c, p, i, m), runtime in normalized.items():
        if compiler != c:
            continue
        update_dddl(grouped, label, p, i, runtime)
    plot.add_dddl(grouped,
                  geometric_mean,
                  b=10000,
                  min_val=0, max_val=1)

def get_stats(runtimes):
    normalized, outliers = get_normalized_runtimes(runtimes)

    grouped = {}
    for (compiler, pattern, program, mutation), runtime in normalized.items():
        update_dict_array(grouped, compiler, runtime)

    cis = {}
    for key, runtimes in grouped.items():
        cis[key] = calculate_ci_geometric(runtimes, 0.0, 1.0)

    interesting_cases = create_max_spread_cases()
    for (compiler, *rest), [min_outlier, max_outlier] in outliers.cases.items():
        normalized_pair = (min_outlier.normalized, max_outlier.normalized)
        # max normalized means min raw runtime
        raw_pair = (max_outlier.raw, min_outlier.raw)
        interesting_cases.merge((compiler, rest), normalized_pair, raw_pair)
    return Stats('Runtime stability', cis, interesting_cases)

def get_paths(stats):
    return get_paths_for_pair(stats)

def format_raw(raw):
    return format_spread_pair(raw)

def get_data_and_errors(compilers, patterns, raw_runtimes):
    normalized, outliers = get_normalized_runtimes(raw_runtimes)

    per_pattern = {}
    for (compiler, pattern, program, mutation), runtime in normalized.items():
        update_dict_array(per_pattern, (compiler, pattern), runtime)

    grouped = {}
    for (compiler, pattern), runtimes in per_pattern.items():
        update_dict_array(grouped, compiler, geometric_mean(runtimes))

    data = {}
    neg_errs = {}
    pos_errs = {}

    for key, runtimes in grouped.items():
        val = geometric_mean(runtimes)
        data[key] = val
        if len(runtimes) > normal_threshold:
            all_ci = calculate_ci_geometric(runtimes, 0.0, 1.0)
            ci95 = all_ci[1]
            neg_errs[key] = val - ci95[0]
            pos_errs[key] = ci95[1] - val
        else:
            neg_errs[key] = None
            pos_errs[key] = None

    interesting_cases = create_max_spread_cases()
    for (compiler, *rest), [min_outlier, max_outlier] in outliers.cases.items():
        normalized_pair = (min_outlier.normalized, max_outlier.normalized)
        # max normalized means min raw runtime
        raw_pair = (max_outlier.raw, min_outlier.raw)
        interesting_cases.merge((compiler, rest), normalized_pair, raw_pair)
    # print('runtime stability')
    # print(interesting_cases.pprint())

    return data, neg_errs, pos_errs, interesting_cases

def plot_scaled_runtimes(compilers, patterns, runtimes, path_prefix=None):
    best_mutations = {}
    for (compiler, mode, pattern, instance, mutation), runtime in runtimes.items():
        if mode == 'fast':
            k = (compiler, pattern, instance)
            if k not in best_mutations:
                best_mutations[k] = (runtime, (pattern, instance, mutation))
            else:
                if runtime < best_mutations[k][0]:
                    best_mutations[k] = (runtime, (pattern, instance, mutation))

    normalized = {}
    for (compiler, mode, pattern, program, mutation), runtime in runtimes.items():
        if mode == 'fast':
            key = (compiler, pattern, program, mutation)
            best_mutation_runtime = best_mutations[(compiler, pattern, program)][0]
            normalized[key] = best_mutation_runtime / runtime

    mins = {}
    data = {}
    for (compiler, pattern, instance, mutation), r in normalized.items():
        update_dict_array(data, compiler, r)

        # find outliers
        pim = (pattern, instance, mutation)
        best_pim = best_mutations[(compiler, pattern, instance)][1]
        if compiler not in mins:
            mins[compiler] = (r, pim, best_pim)
        else:
            if r < mins[compiler][0]:
                mins[compiler] = (r, pim, best_pim)

    for compiler, rs in data.items():
        n, bins, patches = plot.plot_histogram(rs, 100)

        n_tallest = max(n)
        plot_height = ((n_tallest + 99) // 100) * 100
        min_r, min_pim, best_pim = mins[compiler]
        (base_dir, p), i, m = min_pim
        (base_dir_best, p_best), i_best, m_best = best_pim
        assert(base_dir == base_dir_best)
        assert(p == p_best)
        assert(i == i_best)
        plt.annotate(f'scaled_runtime={min_r:.6f}\npattern=({p}, {i}, {m}/{m_best})', (min_r, n_tallest / 2))
        if min_r < 0.001:
            min_r = 0.001
        plt.plot((min_r, min_r), (0, plot_height), marker='None', linewidth=2, color='red')
        plt.xlim(0, 1)
        plt.ylim(0, plot_height)

        title = f'Scaled runtime ({compiler})'
        if path_prefix is None:
            plot.display_plot(title=title, legend=False)
        else:
            path = f'{path_prefix}-{compiler}.png'
            plot.save_plot(path, title, legend=False)
            plot.clear_plot()

