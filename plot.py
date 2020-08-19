import seaborn
import matplotlib.pyplot as plt
from tqdm import tqdm
from random import choices

def add_plot(list_1d, label):
    # seaborn.distplot(list_1d, hist=True, kde=True)
    # seaborn.kdeplot(list_1d, bw=0.1, clip=(0.0, 1.0), label=label)
    seaborn.kdeplot(list_1d, label=label).set(xlim=(0, 1))

def display_plot():
    plt.show()

def save_plot(path):
    plt.savefig(path)

def add_dict_array(da, stat, b=100):
    for k, vs in da.items():
        data = []
        print(f'Plotting: {k}')
        for _ in tqdm(range(b)):
            samples = choices(vs, k=len(vs))
            data.append(stat(samples))
        add_plot(data, k)

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
