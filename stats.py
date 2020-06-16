from scipy import log, e
from scipy.stats import gmean, gstd, tmean, tstd
from math import sqrt
from aggregate import parse_mean
from build import PathBuilder
def geometric_mean(l):
    return gmean(l)

def arithmetic_mean(l):
    return tmean(l)

def arithmetic_stability(l):
    the_min = min(l)
    return arithmetic_mean([the_min / i for i in l])

def geometric_stability(l):
    the_min = min(l)
    return geometric_mean([the_min / i for i in l])

# print(geometric_stability(sample))
# print(y1(sample))

def format(l):
    return (f'arithmetic_stability:{arithmetic_stability(l):.10f} '
            f'geometric_stability:{geometric_stability(l):.10f}')

def format_summary_file(path):
    means = []
    with open(path) as f:
        for line in f:
            if line:
                means.append(parse_mean(line))
    print(means)
    return format(means)

def calculate_stability(compiler, mode, pattern, program):
    path_builder = PathBuilder(compiler, mode, pattern, program)
    stability_path = path_builder.program_stability_path()
    with open(stability_path, 'w') as f:
        summary_path = path_builder.program_summary_path()
        f.write(format_summary_file(summary_path))
