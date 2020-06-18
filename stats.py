from scipy import log, e
from scipy.stats import gmean, gstd, tmean, tstd, t, norm
from math import sqrt
from aggregate import Summary, format_runtimes_file
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

def calculate_perf_slowdown(min_of_program_path, mutation_summary_path, stability_path):
    best_mutation = Summary().parse_from_summary(min_of_program_path).mean
    mutation = Summary().parse_from_summary(mutation_summary_path).mean
    with open(stability_path, 'w') as f:
        f.write(f'{best_mutation / mutation}')

def calculate_vec_speedup(vec_path, novec_path, speedup_path, success_path):
    vec = Summary().parse_from_summary(vec_path).mean
    novec = Summary().parse_from_summary(novec_path).mean
    speedup = novec / vec
    success = 1 if speedup >= 1.15 else 0
    with open(speedup_path, 'w') as f:
        f.write(f'{speedup}')
    with open(success_path, 'w') as f:
        f.write(f'{success}')

def calculate_peer_fraction(c1_path, c2_path, fraction_path, is_faster_path):
    c1 = Summary().parse_from_summary(c1_path).mean
    c2 = Summary().parse_from_summary(c2_path).mean
    fraction = c1 / c2
    is_faster = 1 if c1 < c2 else 0 
    with open(fraction_path, 'w') as f:
        f.write(f'{fraction}')
    with open(is_faster_path, 'w') as f:
        f.write(f'{is_faster}')

def calculate_95ci_geometric(sample_paths, output_path):
    samples = []
    for path in sample_paths:
        with open(path) as f:
            samples.append(float(f.read()))
    log_samples = list(map(log, samples))
    log_ci = confidence_interval_mean(log_samples, 0.95)
    ci = (e**log_ci[0], e**log_ci[1])
    with open(output_path, 'w') as f:
        f.write(f'ci-95:{ci[0]}:{ci[1]}')

def calculate_95ci_proportion(sample_paths, output_path):
    n = 0
    total = 0
    for path in sample_paths:
        with open(path) as f:
            if int(f.read()) > 0:
                n += 1
        total += 1
    proportion = n / total
    ci = confidence_interval_proportion(proportion, total, 0.95)
    with open(output_path, 'w') as f:
        f.write(f'ci-95:{ci[0]}:{ci[1]}')

def find_min_for_program(runtime_paths, min_path):
    assert(len(runtime_paths) > 0)
    summaries = []
    for runtimes_path in runtime_paths:
        summary = Summary()
        summary.parse_from_runtimes(runtimes_path)
        summaries.append(summary)
    min_summary = summaries[0]
    for other_summary in summaries[1:]:
        min_summary.merge_min(other_summary)
    with open(min_path, 'w') as f:
        f.write(min_summary.pprint())

def summarize_mutation(runtimes_path, summary_path):
    with open(summary_path, 'w') as f:
        f.write(format_runtimes_file(runtimes_path))
