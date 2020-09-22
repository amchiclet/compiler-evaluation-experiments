import seaborn
import matplotlib.pyplot as plt
from tqdm import tqdm
from random import choices, sample
from scipy.stats import norm, gamma

def add_plot(list_1d, label, color=None, min_val=None, max_val=None):
    width = (max(list_1d) - min(list_1d)) * 0.5
    n_bins = [t/100 for t in range(200)]
    seaborn.distplot(
        list_1d,
        label=label,
        hist=True,
        kde=False,
        fit=norm,
        color=color,
        norm_hist=True,
        bins=n_bins,
    ).set(xlim=(min_val, 2))
    # seaborn.kdeplot(list_1d, bw=0.1, clip=(0.0, 1.0), label=label)
    # seaborn.kdeplot(list_1d, label=label, bw=width).set(xlim=(min_val, max_val))

def add_bar(values, cis):
    n_bars = len(cis)
    x_pos = list(range(n_bars))
    neg_errs = []
    pos_errs = []
    data = []
    labels = sorted(cis.keys())
    for key in labels:
        val = values[key]
        data.append(val)
        neg_errs.append(val - cis[key][0])
        pos_errs.append(cis[key][1] - val)

    fig, ax = plt.subplots()
    ax.bar(x_pos, data, 0.5, yerr=(neg_errs, pos_errs), capsize=10)
    ax.set_xticks(x_pos)
    ax.set_xticklabels(labels)

def display_plot(title=None, legend=True):
    if title is not None:
        plt.title(title)
    if legend:
        plt.legend()
    plt.show()

def save_plot(path, title=None, legend=True):
    if title is not None:
        plt.title(title)
    if legend:
        plt.legend()
    plt.savefig(path)

def clear_plot():
    plt.close()
    # plt.clf()

def add_dict_array(da, stat, b=100, min_val=None, max_val=None):
    for k, vs in da.items():
        data = []
        print(f'Plotting: {k}')
        for _ in tqdm(range(b)):
            samples = choices(vs, k=len(vs))
            data.append(stat(samples))
        add_plot(data, k, min_val, max_val)

def add_dddl(pattern_maps, stat, b=100, min_val=None, max_val=None):
    for compiler, pattern_map in pattern_maps.items():
        patterns = []
        for pattern, instance_map in pattern_map.items():
            instances = []
            for instance, mutations in instance_map.items():
                instances.append((instance, mutations))
            patterns.append((pattern, instances))

        data = []
        for _ in tqdm(range(b)):
            samples = []
            for pattern, instances in choices(patterns, k=len(patterns)):
                for instance, runtimes in instances:
                    samples += runtimes
            data.append(stat(samples))
        add_plot(data, compiler, min_val, max_val)

def check_samples(name, samples):
    if len(samples) == 0:
        print(f'{name} sample size is 0')
        return False
    if len(set(samples)) == 1:
        print(f'{name} sample has no variation')
        return False
    return True

def plot_dict_array(da, stat, b=1000, output_path=None, display=True):
    for k, vs in da.items():
        data = []
        print(f'Plotting: {k}')
        for _ in tqdm(range(b)):
            samples = choices(vs, k=len(vs))
            data.append(stat(samples))
        add_plot(data, k)
    if output_path is not None:
        save_plot(output_path)
    display_plot()
