from scipy import log, e
from scipy.stats import gmean, gstd, tmean, tstd, t, norm
from math import sqrt
from build import PathBuilder

def geometric_mean(l):
    return gmean(l)

def arithmetic_mean(l):
    return tmean(l)

def sample_std(l):
    return tstd(l)

def sample_gstd(l):
    return gstd(l)

def confidence_interval_mean(samples, level):
    n_samples = len(samples)
    mean = arithmetic_mean(samples)
    std = sample_std(samples)
    dof = n_samples - 1
    t_value = t.ppf((1+level)/2, dof)
    error = t_value * std / sqrt(n_samples)
    return (mean - error, mean + error)

def confidence_interval_proportion(proportion, n_samples, level):
    z_value = norm.ppf((1+level)/2)
    error = z_value * sqrt((proportion * (1-proportion)) / n_samples)
    return (proportion - error, proportion + error)

def calculate_ci_geometric(sample_paths, output_path):
    samples = []
    for path in sample_paths:
        with open(path) as f:
            samples.append(float(f.read()))
    log_samples = list(map(log, samples))
    log_ci90 = confidence_interval_mean(log_samples, 0.90)
    log_ci95 = confidence_interval_mean(log_samples, 0.95)
    log_ci99 = confidence_interval_mean(log_samples, 0.99)
    ci90 = (e**log_ci95[0], e**log_ci90[1])
    ci95 = (e**log_ci95[0], e**log_ci95[1])
    ci99 = (e**log_ci99[0], e**log_ci99[1])
    with open(output_path, 'w') as f:
        f.write(f'ci-90:{ci90[0]}:{ci90[1]} '
                f'ci-95:{ci95[0]}:{ci95[1]} '
                f'ci-99:{ci99[0]}:{ci99[1]}')

def calculate_ci_proportion(sample_paths, output_path):
    n = 0
    total = 0
    for path in sample_paths:
        with open(path) as f:
            if int(f.read()) > 0:
                n += 1
        total += 1
    proportion = n / total
    ci90 = confidence_interval_proportion(proportion, total, 0.90)
    ci95 = confidence_interval_proportion(proportion, total, 0.95)
    ci99 = confidence_interval_proportion(proportion, total, 0.99)
    with open(output_path, 'w') as f:
        f.write(f'ci-90:{ci90[0]}:{ci90[1]} '
                f'ci-95:{ci95[0]}:{ci95[1]} '
                f'ci-99:{ci99[0]}:{ci99[1]} ')
