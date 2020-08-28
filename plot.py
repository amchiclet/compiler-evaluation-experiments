import seaborn
import matplotlib.pyplot as plt
from tqdm import tqdm
from random import choices

def add_plot(list_1d, label, min_val=None, max_val=None):
    # seaborn.distplot(list_1d, hist=True, kde=True)
    # seaborn.kdeplot(list_1d, bw=0.1, clip=(0.0, 1.0), label=label)
    seaborn.kdeplot(list_1d, label=label).set(xlim=(min_val, max_val))
def display_plot(title=None):
    if title is not None:
        plt.title(title)
    plt.show()

def save_plot(path):
    plt.savefig(path)

def add_dict_array(da, stat, b=100, min_val=None, max_val=None):
    for k, vs in da.items():
        data = []
        print(f'Plotting: {k}')
        for _ in tqdm(range(b)):
            samples = choices(vs, k=len(vs))
            data.append(stat(samples))
        add_plot(data, k, min_val, max_val)

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
