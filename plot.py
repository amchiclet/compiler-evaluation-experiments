import argparse
import pandas as pd
import matplotlib.pyplot as plt
from pathlib import Path

parser = argparse.ArgumentParser()
parser.add_argument('--input1', type=Path, required=True)
parser.add_argument('--input2', type=Path, required=True)
args = parser.parse_args()

data1 = pd.read_csv(args.input1)
data1 = data1.rename(columns={'Time[Loop]_s': 'runtime1'})

data2 = pd.read_csv(args.input2)
data2 = data2.rename(columns={'Time[Loop]_s': 'runtime2'})
data = pd.concat([data1, data2], ignore_index=True)

x = data['label']
y1 = data['runtime1']
y2 = data['runtime2']

plt.figure(figsize=(10, 6))
plt.plot(x, y1, color='blue', linestyle='-', label='runtime1')
plt.plot(x, y2, color='red', linestyle='-', label='runtime2')
plt.xlabel('label')
plt.ylabel('runtime')

plt.yscale('log')

x_ticks = x[::5]
plt.xticks(x_ticks, rotation=90)

plt.legend()

plt.show()
