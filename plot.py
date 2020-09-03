import seaborn
import matplotlib.pyplot as plt
from tqdm import tqdm
from random import choices, sample

def add_plot(list_1d, label, min_val=None, max_val=None):
    # seaborn.distplot(list_1d, hist=True, kde=True)
    # seaborn.kdeplot(list_1d, bw=0.1, clip=(0.0, 1.0), label=label)
    seaborn.kdeplot(list_1d, label=label).set(xlim=(min_val, max_val))
def display_plot(title=None):
    if title is not None:
        plt.title(title)
    plt.show()

def save_plot(path, title=None):
    if title is not None:
        plt.title(title)
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

def add_dddl(pattern_maps, stat, n_patterns=None, n_instances=None, b=100, min_val=None, max_val=None):
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
            k_patterns = len(patterns) if n_patterns is None else n_patterns
            for pattern, instances in choices(patterns, k=k_patterns):
                k_instances = len(instances) if n_instances is None else n_instances
                for instance, runtimes in choices(instances, k=k_instances):
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
