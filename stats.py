from scipy import log, e
from scipy.stats import gmean, gstd, tmean, tstd
from math import sqrt
from aggregate import Summary
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

# def calculate_stability(min_of_program_path):
#     means = []
#     with open(min_of_program_path) as f:
#         means.append(parse_mean(f.read))
#     print(means)
#     return format(means)

def calculate_mutation_perf_stability(min_of_program_path, mutation_summary_path, stability_path):
    best_mutation = Summary().parse_from_summary(min_of_program_path).mean
    mutation = Summary().parse_from_summary(mutation_summary_path).mean
    with open(stability_path, 'w') as f:
        f.write(f'{best_mutation / mutation}')

def calculate_vec_speedup(vec_path, novec_path, stability_path):
    vec = Summary().parse_from_summary(vec_path).mean
    novec = Summary().parse_from_summary(novec_path).mean
    with open(stability_path, 'w') as f:
        f.write(f'{novec / vec}')

def calculate_perf_stability(mutation_stability_paths, stability_path):
    mutation_stabilities = []
    for path in mutation_stability_paths:
        with open(path) as f:
            mutation_stabilities.append(float(f.read()))
    with open(stability_path, 'w') as f:
        f.write(f'{geometric_mean(mutation_stabilities)}')

def calculate_vec_stability(mutation_vec_speedup_paths, stability_path):
    mutation_vec_speedups = []
    for path in mutation_vec_speedup_paths:
        with open(path) as f:
            mutation_vec_speedups.append(float(f.read()))
    # count speed up > 15%
    n_vectorized = sum(1 for m in mutation_vec_speedups if m >= 1.15)
    n_total = len(mutation_vec_speedups)
    with open(stability_path, 'w') as f:
        f.write(f'gmean:{geometric_mean(mutation_vec_speedups)} '
                f'vectorized:{n_vectorized / n_total}')

def calculate_peer_fraction(c1_path, c2_path, peer_fraction_path):
    c1 = Summary().parse_from_summary(c1_path).mean
    c2 = Summary().parse_from_summary(c2_path).mean
    with open(peer_fraction_path, 'w') as f:
        f.write(f'{c1 / c2}')
