import matplotlib.pyplot as plt
import report.runtime
import report.vector_speedup
import report.vectorizable
import report.cost_model
import report.peer_rank
import plot
from report.generate import \
    get_ok_patterns_fully_qualified, \
    get_popular_pattern_structure, \
    limit_patterns, \
    read_runtimes_database_fully_qualified
from compilers import compilers
from report.peer_metrics import get_compiler_pairs
from scipy.stats import probplot

from tabulate import tabulate

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

def plot_single_compiler_metrics(metrics, metrics_labels, title=None, path=None):
    xticks = []
    for mi in range(len(metrics)):
        xticks.append(mi * 1.0)
    xlabels = metrics_labels

    fig, ax = plt.subplots()

    ax.set_xticks(xticks)
    ax.set_xticklabels(xlabels)
    ax.set_ylim([0, 1])

    for ci, compiler in enumerate(compilers):
        xs = []
        ys = []
        err_xs = []
        err_ys = []
        all_neg_errs = []
        all_pos_errs = []
        outlier_xs = []
        outlier_ys = []
        for mi, (data, neg_errs, pos_errs, interesting_cases) in enumerate(metrics):
            x = mi * 1.0 + ci * 0.1
            xs.append(x)
            y = data[compiler]
            ys.append(y)
            if neg_errs[compiler] is not None and pos_errs[compiler] is not None:
                err_xs.append(x)
                err_ys.append(y)
                all_neg_errs.append(neg_errs[compiler])
                all_pos_errs.append(pos_errs[compiler])

            # if interesting_cases is not None:
            #     if compiler in interesting_cases.cases:
            #         outlier = interesting_cases.cases[compiler][0]
            #         min_outlier = outlier.normalized[0]
            #         outlier_xs.append(x)
            #         outlier_ys.append(min_outlier)
            #         ax.annotate(f'{min_outlier:.3f}', (x, min_outlier))

        ax.bar(xs, ys, 0.1, label=compiler, color=compiler_color(compiler))
        ax.errorbar(err_xs, err_ys, yerr=(all_neg_errs, all_pos_errs), ecolor='black', capsize=10, linestyle='None')
        # ax.plot(outlier_xs, outlier_ys, color='black', marker='x', linestyle='None')

    if path is not None:
        plot.save_plot(path, title)
    else:
        plot.display_plot(title)

def plot_compiler_pair_metrics(metrics, title=None, path=None):
    data, neg_errs, pos_errs = metrics
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
        if left_key in data:
            left_data = data[left_key]
            print(ys, left_data)
            ax.barh(ys, left_data, color=compiler_color(c1))
            neg_err = neg_errs[left_key]
            pos_err = pos_errs[left_key]
            if neg_err is not None and pos_err is not None:
                left_errors = ([neg_err], [pos_err])
                ax.errorbar(left_data, ys, xerr=left_errors, ecolor='black', capsize=10)

        right_key = (c2, c1)
        if right_key in data:
            right_data = data[right_key]
            right_bottom = 1 - right_data
            print(ys, right_data)
            ax.barh(ys, right_data, left=right_bottom, color=compiler_color(c2))
            neg_err = neg_errs[right_key]
            pos_err = pos_errs[right_key]
            if neg_err is not None and pos_err is not None:
                # for the bar on the right, errors are swapped
                right_errors = ([pos_err], [neg_err])
                ax.errorbar(right_bottom, ys, xerr=right_errors, ecolor='black', capsize=10)

    ax.set_xticks(xticks)

    ax.set_xlim([0, 1])
    ax.set_yticks(yticks)
    ax.set_yticklabels(left_ylabels)

    ax_other = ax.twinx()
    ax_other.set_ylim(ax.get_ylim())
    ax_other.set_yticks(yticks)
    ax_other.set_yticklabels(right_ylabels)

    if path is not None:
        plot.save_plot(path, title, legend=False)
    else:
        plot.display_plot(title, legend=False)

def plot_pair_speedup_metrics(metrics, title=None, path=None):
    data, neg_errs, pos_errs, outliers = report.peer_speedup.get_data_and_errors_v2(compilers, patterns, runtimes)
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
            ax.bar(xtick, data[key], width=1, color=compiler_color(c2))
            neg_err = neg_errs[key]
            pos_err = pos_errs[key]
            if neg_err is not None and pos_err is not None:
                ax.errorbar(xtick, data[key], yerr=([neg_err], [pos_err]), capsize=10, color='black')
            # outlier = outliers.cases[key][0]
            # max_outlier = outlier.normalized
            # max_outlier_txt = f'{max_outlier:.2f}'
            # max_y = 5
            # if max_outlier > max_y:
            #     ax.annotate(max_outlier_txt, (xtick-0.2, max_y-0.7), rotation=90)
            #     ax.plot(xtick, max_y, color='black', marker='o', linestyle='None')
            # else:
            #     ax.annotate(max_outlier_txt, (xtick-0.3, max_outlier+0.2), rotation=90)
            #     ax.plot(xtick, max_outlier, color='black', marker='o', linestyle='None')

        key_inv = (c2, c1)
        xtick = x*n_pairs + 1
        xticks.append(xtick)
        xlabels.append(f'{c2}/{c1}')
        if key_inv in data:
            ax.bar(xtick, data[key_inv],
                   width=1, capsize = 10, color=compiler_color(c1))
            neg_err = neg_errs[key_inv]
            pos_err = pos_errs[key_inv]
            if neg_err is not None and pos_err is not None:
                ax.errorbar(xtick, data[key_inv], yerr=([neg_err], [pos_err]), capsize=10, ecolor='black')
            # outlier = outliers.cases[key_inv][0]
            # max_outlier = outlier.normalized
            # max_outlier_txt = f'{max_outlier:.2f}'
            # if max_outlier > max_y:
            #     ax.annotate(max_outlier_txt, (xtick-0.4, max_y-0.7), rotation=90)
            #     ax.plot(xtick, max_y, color='black', marker='o', linestyle='None')
            # else:
            #     ax.annotate(max_outlier_txt, (xtick-0.5, max_outlier+0.2), rotation=90)
            #     ax.plot(xtick, max_outlier, color='black', marker='o', linestyle='None')

    ax.set_xticks(xticks)
    ax.set_xticklabels(xlabels, rotation=90)
    # ax.set_ylim([0, max_y])
    ax.set_title(title)
    fig.tight_layout()

    if path is not None:
        plot.save_plot(path, legend=False)
    else:
        plot.display_plot(legend=False)

import os

# base_dirs = [f'result-db/r{r:02d}/code' for r in range(1)]
base_dirs = [os.getcwd()]
patterns = read_patterns(base_dirs)
runtimes = read_runtimes_database_fully_qualified(patterns)
n_patterns = len(patterns)

# report.runtime.get_grouped_normalized_runtimes(compilers, runtimes)
# report.peer_speedup.plot_qq(compilers, patterns, runtimes)
# exit(1)

# Gather metrics
runtime_metrics = report.runtime.get_data_and_errors(compilers, patterns, runtimes)
vector_speedup_metrics = report.vector_speedup.get_data_and_errors(compilers, patterns, runtimes)
cost_model_metrics = report.cost_model.get_data_and_errors_v2(compilers, patterns, runtimes)
top_rank_metrics = report.peer_rank.get_data_and_errors_top_v2(compilers, patterns, runtimes)
bottom_rank_metrics = report.peer_rank.get_data_and_errors_bottom(compilers, patterns, runtimes)
pair_comparison_metrics = report.peer_rank.get_data_and_errors_pair_v2(compilers, patterns, runtimes)
peer_speedup_metrics = report.peer_speedup.get_data_and_errors(compilers, patterns, runtimes)

# Plot
inter_compiler_metrics = [runtime_metrics, vector_speedup_metrics, cost_model_metrics]
inter_compiler_labels = ['runtime', 'vec speedup', 'cost model']
single_compiler_rank = [top_rank_metrics, bottom_rank_metrics]

# save to file
# plot_single_compiler_metrics(inter_compiler_metrics, inter_compiler_labels, 'Stability', 'stability.png')
# single_compiler_rank_labels = ['top rank', 'bottom rank']
# plot_single_compiler_metrics(single_compiler_rank, single_compiler_rank_labels, 'Top and bottom rank', 'top-bottom.png')
# plot_compiler_pair_metrics(pair_comparison_metrics, 'Peer comparison', 'pairs.png')
# plot_pair_speedup_metrics(peer_speedup_metrics, 'Peer speedup', 'speedup.png')

# display
plot_single_compiler_metrics(inter_compiler_metrics, inter_compiler_labels, 'Stability')
single_compiler_rank_labels = ['top rank', 'bottom rank']
plot_single_compiler_metrics(single_compiler_rank, single_compiler_rank_labels, 'Top and bottom rank')
plot_compiler_pair_metrics(pair_comparison_metrics, 'Peer comparison')
plot_pair_speedup_metrics(peer_speedup_metrics, 'Peer speedup')


def format_row(outliers, name, order, format_raw):
    row = [name]
    for key in order:
        if key not in outliers.cases:
            row.append('N/A')
        else:
            lines = []
            for case in outliers.cases[key]:
                lines.append(format_raw(case.raw))
            row.append('\n'.join(lines))
    return row

# Interesting cases
interesting_cases = [
    ('runtime stability', runtime_metrics[3], report.runtime.format_raw),
    ('vector speedup stability', vector_speedup_metrics[3], report.vector_speedup.format_raw),
    ('cost model stability', cost_model_metrics[3], report.cost_model.format_raw),
]
print('Interesting cases')

header = ['', *[c for c in compilers]]
table = []
for label, outliers, format_raw in interesting_cases:
    row = format_row(outliers, label, compilers, format_raw)
    table.append(row)
print(tabulate(table, headers=header))

pairs = peer_speedup_metrics[0].keys()

label = 'peer speedup'
outliers = peer_speedup_metrics[3]
format_raw = report.peer_speedup.format_raw
row = format_row(outliers, label, pairs, format_raw)

header = ['', *[f'{pair[0]}/{pair[1]}' for pair in pairs]]
table = [row]
print(tabulate(table, headers=header))
