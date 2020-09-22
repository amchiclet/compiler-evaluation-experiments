from report.generate import get_ok_patterns_fully_qualified, get_popular_pattern_structure, limit_patterns, read_runtimes_database_fully_qualified
from compilers import compilers
import matplotlib.pyplot as plt

import report.runtime
import report.vector_speedup
import report.vectorizable
import report.cost_model
import report.peer_rank
from report.peer_metrics import get_compiler_pairs

def compiler_color(compiler):
    if compiler == 'gcc':
        return 'palegreen'
    elif compiler == 'clang':
        return 'moccasin'
    elif compiler == 'icc':
        return 'lightskyblue'
    elif compiler == 'pgi':
        return 'pink'
    else:
        return None

def read_patterns(base_dirs):
    all_patterns = []
    for base_dir in base_dirs:
        all_patterns += get_ok_patterns_fully_qualified(base_dir)
    n_instances, n_mutations = get_popular_pattern_structure(all_patterns)
    all_patterns = limit_patterns(all_patterns, n_instances, n_mutations)
    return all_patterns

def plot_single_compiler_metrics(compilers, patterns, runtimes):
    n_patterns = len(patterns)
    runtime_metrics = report.runtime.get_data_and_errors(n_patterns, runtimes)
    vector_speedup_metrics = report.vector_speedup.get_data_and_errors(n_patterns, runtimes)
    # vectorizable_metrics = report.vectorizable.get_data_and_errors(runtimes)
    cost_model_metrics = report.cost_model.get_data_and_errors(n_patterns, runtimes)
    peer_rank_metrics = report.peer_rank.get_data_and_errors_top(compilers, patterns, runtimes)
    metrics = [
        runtime_metrics,
        vector_speedup_metrics,
        # vectorizable_metrics,
        cost_model_metrics,
        peer_rank_metrics
    ]
    xticks = []
    for mi in range(len(metrics)):
        xticks.append(mi * 1.0)
    xlabels = [
        'runtime',
        'vec speedup',
        # 'vec proportion',
        'cost model',
        'peer_rank',
    ]

    fig, ax = plt.subplots()

    ax.set_xticks(xticks)
    ax.set_xticklabels(xlabels)
    ax.set_ylim([0, 1])

    for ci, compiler in enumerate(compilers):
        xs = []
        ys = []
        all_neg_errs = []
        all_pos_errs = []
        outlier_xs = []
        outlier_ys = []
        for mi, (data, neg_errs, pos_errs, interesting_cases) in enumerate(metrics):
            x = mi * 1.0 + ci * 0.1
            xs.append(x)
            y = data[compiler]
            ys.append(y)
            all_neg_errs.append(neg_errs[compiler])
            all_pos_errs.append(pos_errs[compiler])

            if interesting_cases is not None:
                outlier = interesting_cases.cases[compiler][0]
                min_outlier = outlier.normalized[0]
                outlier_xs.append(x)
                outlier_ys.append(min_outlier)
                ax.annotate(f'{min_outlier:.3f}', (x, min_outlier))
        ax.bar(xs, ys, 0.1, yerr=(all_neg_errs, all_pos_errs), capsize=10, label=compiler, color=compiler_color(compiler))
        ax.plot(outlier_xs, outlier_ys, color='black', marker='x', linestyle='None')

    plt.legend()
    plt.show()

    outlier_pims = set()
    for metric in metrics:
        outlier = metric[3]
        if outlier is None:
            continue

    return [metric[3] for metric in metrics if metric[3] is not None]

def plot_compiler_pair_metrics(compilers, patterns, runtimes):
    data, neg_errs, pos_errs = report.peer_rank.get_data_and_errors_pair(compilers, patterns, runtimes)
    fig, ax = plt.subplots()

    xticks = [i*0.1 for i in range(11)]
    yticks = []
    left_ylabels = []
    right_ylabels = []

    for ys, (c1, c2) in enumerate(get_compiler_pairs(compilers)):
        yticks.append(ys)
        left_ylabels.append(c1)
        right_ylabels.append(c2)

        left_key = (c1, c2)
        left_data = data[left_key]
        left_errors = ([neg_errs[left_key]], [pos_errs[left_key]])

        right_key = (c2, c1)
        right_data = data[right_key]

        right_bottom = 1 - right_data
        right_errors = ([pos_errs[right_key]], [neg_errs[right_key]])

        ax.barh(ys, left_data, color=compiler_color(c1))
        ax.barh(ys, right_data, left=right_bottom, color=compiler_color(c2))
        ax.errorbar(left_data, ys, xerr=left_errors, ecolor='black', capsize=10)
        ax.errorbar(right_bottom, ys, xerr=right_errors, ecolor='black', capsize=10)

    ax.set_xticks(xticks)

    ax.set_xlim([0, 1])
    ax.set_yticks(yticks)
    ax.set_yticklabels(left_ylabels)

    ax_other = ax.twinx()
    ax_other.set_ylim(ax.get_ylim())
    ax_other.set_yticks(yticks)
    ax_other.set_yticklabels(right_ylabels)

    plt.show()

def plot_pair_speedup_metrics(compilers, patterns, runtimes):
    data, neg_errs, pos_errs, outliers = report.peer_speedup.get_data_and_errors(compilers, patterns, runtimes)
    fig, ax = plt.subplots()

    compiler_pairs = get_compiler_pairs(compilers)
    n_pairs = len(compiler_pairs)

    xticks = []
    xlabels = []
    for x, (c1, c2) in enumerate(get_compiler_pairs(compilers)):
        key = (c1, c2)
        xtick = x*n_pairs
        xticks.append(xtick)
        xlabels.append(f'{c1}/{c2}')
        if key in data:
            ax.bar(xtick, data[key],
                   yerr=([neg_errs[key]], [pos_errs[key]]),
                   width=1, capsize = 10, color=compiler_color(c2))
        outlier = outliers.cases[key][0]
        max_outlier = outlier.normalized
        max_outlier_txt = f'{max_outlier:.2f}'
        max_y = 5
        if max_outlier > max_y:
            ax.annotate(max_outlier_txt, (xtick-0.2, max_y-0.7), rotation=90)
            ax.plot(xtick, max_y, color='black', marker='o', linestyle='None')
        else:
            ax.annotate(max_outlier_txt, (xtick-0.3, max_outlier+0.2), rotation=90)
            ax.plot(xtick, max_outlier, color='black', marker='o', linestyle='None')

        key_inv = (c2, c1)
        xtick = x*n_pairs + 1
        xticks.append(xtick)
        xlabels.append(f'{c2}/{c1}')
        ax.bar(xtick, data[key_inv],
               yerr=([neg_errs[key_inv]], [pos_errs[key_inv]]),
               width=1, capsize = 10, color=compiler_color(c1))
        outlier = outliers.cases[key_inv][0]
        max_outlier = outlier.normalized
        max_outlier_txt = f'{max_outlier:.2f}'
        if max_outlier > max_y:
            ax.annotate(max_outlier_txt, (xtick-0.4, max_y-0.7), rotation=90)
            ax.plot(xtick, max_y, color='black', marker='o', linestyle='None')
        else:
            ax.annotate(max_outlier_txt, (xtick-0.5, max_outlier+0.2), rotation=90)
            ax.plot(xtick, max_outlier, color='black', marker='o', linestyle='None')

    ax.set_xticks(xticks)
    ax.set_xticklabels(xlabels, rotation=90)
    ax.set_ylim([0, max_y])
    fig.tight_layout()
    plt.show()
    return outliers

import os
# base_dirs = [f'result-db/r{r:02d}/code' for r in range(1)]
base_dirs = [os.getcwd()]
patterns = read_patterns(base_dirs)
runtimes = read_runtimes_database_fully_qualified(patterns)
n_patterns = len(patterns)

# TODO: Make the pair metrics consistent-colored

plot_single_compiler_metrics(compilers, patterns, runtimes)
plot_compiler_pair_metrics(compilers, patterns, runtimes)
plot_pair_speedup_metrics(compilers, n_patterns, runtimes)
