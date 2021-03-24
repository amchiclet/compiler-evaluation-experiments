import matplotlib.pyplot as plt
import report.runtime
import report.vector_speedup
import report.vectorizable
import report.cost_model
import report.peer_rank
import report.transformation_speedup
import plot
from report.generate import \
    get_ok_patterns_fully_qualified, \
    get_popular_pattern_structure, \
    limit_patterns, \
    read_runtimes_database_fully_qualified
from report.util import normalize_compiler_name
from compilers import compilers
from report.peer_metrics import get_compiler_pairs
from scipy.stats import probplot
from report.mode import is_comparing_versions
from tabulate import tabulate
from loguru import logger

def compiler_color(compiler):
    if compiler == 'gcc':
        return 'palegreen'
    if compiler == 'gcc-5':
        return 'palegreen'
    if compiler == 'gcc-7':
        return 'green'
    elif compiler == 'clang':
        return 'moccasin'
    elif compiler == 'clang-6':
        return 'moccasin'
    elif compiler == 'clang-10':
        return 'orange'
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
    return all_patterns, n_instances, n_mutations

def filter_existing_patterns(patterns, runtimes):
    filtered_patterns = []
    for p, instances in patterns:
        filtered_instances = []
        for i, mutations in instances:
            filtered_mutations = []
            for m in mutations:
                is_complete = True
                for c in compilers:
                    for mode in ['fast', 'novec', 'nopredict']:
                        if (c, mode, p, i, m) not in runtimes:
                            is_complete = False
                            break
                if is_complete:
                    filtered_mutations.append(m)
            if len(filtered_mutations) > 0:
                filtered_instances.append((i, filtered_mutations))
        if len(filtered_instances) > 0:
            filtered_patterns.append((p, filtered_instances))
    return filtered_patterns

def plot_single_compiler_metrics(metrics, metrics_labels, title=None, path=None, is_normalized=True):
    xticks = []
    for mi in range(len(metrics)):
        xticks.append(mi * 1.0)
    xlabels = metrics_labels

    fig, ax = plt.subplots()

    ax.set_xticks(xticks)
    ax.set_xticklabels(xlabels)
    if is_normalized:
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
            if compiler not in data:
                continue
            x = mi * 1.0 + ci * 0.1
            xs.append(x)
            y = data[compiler]
            ys.append(y)
            if neg_errs[compiler] is not None and pos_errs[compiler] is not None:
                err_xs.append(x)
                err_ys.append(y)
                all_neg_errs.append(neg_errs[compiler])
                all_pos_errs.append(pos_errs[compiler])

        if is_comparing_versions:
            # uncomment for old version vs new version experiment
            ax.bar(xs, ys, 0.1, label=compiler, color=compiler_color(compiler))
        else:
            # uncomment for versionless experiments
            ax.bar(xs, ys, 0.1, label=normalize_compiler_name(compiler), color=compiler_color(compiler))
        ax.errorbar(err_xs, err_ys, yerr=(all_neg_errs, all_pos_errs), ecolor='black', capsize=10, linestyle='None')

    if path is not None:
        plot.save_plot(path, title)
        plot.clear_plot()
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
        if is_comparing_versions:
            # uncomment for old version vs new version experiment
            if normalize_compiler_name(c1) != normalize_compiler_name(c2):
                continue

        yticks.append(ys)
        if is_comparing_versions:
            # uncomment for old version vs new verion experiment
            left_ylabels.append(c1)
            right_ylabels.append(c2)
        else:
            # uncomment for versionless experiments
            left_ylabels.append(normalize_compiler_name(c1))
            right_ylabels.append(normalize_compiler_name(c2))

        left_key = (c1, c2)
        if left_key in data:
            left_data = data[left_key]
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
        plot.clear_plot()
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
        if is_comparing_versions:
            # uncomment for old version vs new version experiment
            if normalize_compiler_name(c1) != normalize_compiler_name(c2):
                continue

        key = (c1, c2)
        xtick = x*n_pairs
        xticks.append(xtick)
        if is_comparing_versions:
            # uncomment for old version vs new version experiment
            xlabels.append(f'{c1}/{c2}')
        else:
            # uncomment for versionless experiments
            xlabels.append(f'{normalize_compiler_name(c1)}/{normalize_compiler_name(c2)}')
        if key in data:
            ax.bar(xtick, data[key], width=1, color=compiler_color(c2))
            neg_err = neg_errs[key]
            pos_err = pos_errs[key]
            if neg_err is not None and pos_err is not None:
                ax.errorbar(xtick, data[key], yerr=([neg_err], [pos_err]), capsize=10, color='black')

        key_inv = (c2, c1)
        xtick = x*n_pairs + 1
        xticks.append(xtick)
        if is_comparing_versions:
            # uncomment for old version vs new version experiment
            xlabels.append(f'{c2}/{c1}')
        else:
            # uncomment for versionless experiments
            xlabels.append(f'{normalize_compiler_name(c2)}/{normalize_compiler_name(c1)}')
        if key_inv in data:
            ax.bar(xtick, data[key_inv],
                   width=1, capsize = 10, color=compiler_color(c1))
            neg_err = neg_errs[key_inv]
            pos_err = pos_errs[key_inv]
            if neg_err is not None and pos_err is not None:
                ax.errorbar(xtick, data[key_inv], yerr=([neg_err], [pos_err]), capsize=10, ecolor='black')

    ax.set_xticks(xticks)
    ax.set_xticklabels(xlabels, rotation=90)
    # ax.set_ylim([0, max_y])
    ax.set_title(title)
    fig.tight_layout()

    if path is not None:
        plot.save_plot(path, legend=False)
        plot.clear_plot()
    else:
        plot.display_plot(legend=False)

import os

# base_dirs = [f'result-db/r{r:02d}/code' for r in range(1)]
base_dirs = [os.getcwd()]
patterns, n_instances, n_mutations = read_patterns(base_dirs)
runtimes = read_runtimes_database_fully_qualified(patterns)
patterns = filter_existing_patterns(patterns, runtimes)

patterns = limit_patterns(patterns, n_instances, n_mutations)

n_patterns = len(patterns)
print(f'n_patterns = {n_patterns}')

# import report.runtime_vs_vector_speedup
# report.runtime_vs_vector_speedup.find_outliers(compilers, patterns, runtimes)
# exit(0)

# for sample_size in [10, 20, 30, 100]:
#     report.runtime.plot_qq(compilers, patterns, runtimes, sample_size)
#     report.peer_rank.top_plot_qq(compilers, patterns, runtimes, sample_size)
#     # report.peer_rank.pair_plot_qq(compilers, patterns, runtimes, sample_size)
# exit(1)

# Gather metrics
runtime_metrics = report.runtime.get_data_and_errors(compilers, patterns, runtimes)
vector_speedup_metrics = report.vector_speedup.get_data_and_errors(compilers, patterns, runtimes)
cost_model_metrics = report.cost_model.get_data_and_errors_v4(compilers, patterns, runtimes)
top_rank_metrics = report.peer_rank.get_data_and_errors_top_v2(compilers, patterns, runtimes)
bottom_rank_metrics = report.peer_rank.get_data_and_errors_bottom(compilers, patterns, runtimes)
pair_comparison_metrics = report.peer_rank.get_data_and_errors_pair_v2(compilers, patterns, runtimes)
peer_speedup_metrics = report.peer_speedup.get_data_and_errors_v2(compilers, patterns, runtimes)

logger.info(f'runtime confidence intervals')
for c in compilers:
    data, neg_errs, pos_errs, _ = runtime_metrics
    if c not in data or c not in neg_errs or c not in pos_errs:
        continue
    logger.info(f'{c} {data[c]}, [{data[c] - neg_errs[c]} {data[c] + pos_errs[c]}]')
logger.info(f'vector speedup confidence intervals')
for c in compilers:
    data, neg_errs, pos_errs, _ = vector_speedup_metrics
    if c not in data:
        continue
    logger.info(f'{c} [{data[c] - neg_errs[c]} {data[c] + pos_errs[c]}]')
logger.info(f'cost model confidence intervals')
for c in compilers:
    data, neg_errs, pos_errs, _ = cost_model_metrics
    if c not in data:
        continue
    logger.info(f'{c} [{data[c] - neg_errs[c]} {data[c] + pos_errs[c]}]')
logger.info(f'top rank confidence intervals')
for c in compilers:
    data, neg_errs, pos_errs, _ = top_rank_metrics
    if c not in data:
        continue
    logger.info(f'{c} [{data[c] - neg_errs[c]} {data[c] + pos_errs[c]}]')
logger.info(f'bottom rank confidence intervals')
for c in compilers:
    data, neg_errs, pos_errs, _ = bottom_rank_metrics
    if c not in data:
        continue
    logger.info(f'{c} [{data[c] - neg_errs[c]} {data[c] + pos_errs[c]}]')
logger.info(f'peer comparison confidence intervals')
for c1 in compilers:
    for c2 in compilers:
        if c1 == c2:
            continue
        if is_comparing_versions:
            # uncomment for old version vs new version experiment
            if normalize_compiler_name(c1) != normalize_compiler_name(c2):
                continue
        c = (c1, c2)
        data, neg_errs, pos_errs = pair_comparison_metrics
        if c not in data:
            continue
        logger.info(f'{c} [{data[c] - neg_errs[c]} {data[c] + pos_errs[c]}]')

logger.info(f'peer speedup confidence intervals')
for c1 in compilers:
    for c2 in compilers:
        if c1 == c2:
            continue
        if is_comparing_versions:
            # uncomment for old version vs new version experiment
            if normalize_compiler_name(c1) != normalize_compiler_name(c2):
                continue
        c = (c1, c2)
        data, neg_errs, pos_errs, _ = peer_speedup_metrics
        if c not in data:
            logger.info(f'{c} has no data')
            continue
        if neg_errs[c] is None:
            ci_low = 'N/A'
        else:
            ci_low = f'{data[c] - neg_errs[c]}'

        if pos_errs[c] is None:
            ci_high = 'N/A'
        else:
            ci_high = f'{data[c] + pos_errs[c]}'

        logger.info(f'{c} [{ci_low} {ci_high}]')

# Plot
inter_compiler_metrics = [runtime_metrics, vector_speedup_metrics, cost_model_metrics]
inter_compiler_labels = ['runtime', 'vec speedup', 'cost model']
single_compiler_rank = [top_rank_metrics, bottom_rank_metrics]

# save to file
plot_single_compiler_metrics(inter_compiler_metrics, inter_compiler_labels, 'Stability', 'stability.png')
single_compiler_rank_labels = ['top rank', 'bottom rank']
plot_single_compiler_metrics(single_compiler_rank, single_compiler_rank_labels, 'Top and bottom rank', 'top-bottom.png')
plot_compiler_pair_metrics(pair_comparison_metrics, 'Better rank', 'peer-comparison.png')
plot_pair_speedup_metrics(peer_speedup_metrics, 'Peer speedup', 'peer-speedup.png')

# transformation_speedup_metrics = report.transformation_speedup.get_data_and_errors(compilers, patterns, runtimes)
# transformation = 'Unroll'
# plot_single_compiler_metrics([transformation_speedup_metrics,],
#                              [f'{transformation} speedup',],
#                              f'{transformation} speedup',
#                              f'{transformation.lower()}-speedup.png',
#                              is_normalized=False)
# report.transformation_speedup.plot_qq(compilers, patterns, runtimes)

# Interesting cases
report.runtime.plot_scaled_runtimes(compilers, patterns, runtimes, 'dist-scaled-runtimes')
report.vector_speedup.plot_scaled_speedups(compilers, patterns, runtimes, 'dist-scaled-vector-speedup')
report.cost_model.plot_cost_model_speedups_v2(compilers, patterns, runtimes, 'dist-cost-model-speedup')
report.peer_speedup.plot_peer_speedups_v2(compilers, patterns, runtimes, 'dist-peer-speedup')
