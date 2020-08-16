import seaborn
import matplotlib.pyplot as plt

def add_plot(list_1d, label):
    # seaborn.distplot(list_1d, hist=True, kde=True)
    seaborn.kdeplot(list_1d, bw=0.1, clip=(0.0, 1.0), label=label)

def display_plot():
    plt.show()

def save_plot(path):
    plt.savefig(path)
