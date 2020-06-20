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

def calculate_normalized(small_path, big_path, stability_path, ty=float):
    with open(small_path) as f:
        small = ty(f.read())
    with open(big_path) as f:
        mine = ty(f.read())
    with open(stability_path, 'w') as f:
        f.write(f'{small / mine}')

def calculate_vec_speedup(vec_path, novec_path, speedup_path, success_path):
    vec = Summary().parse_from_summary(vec_path).mean
    novec = Summary().parse_from_summary(novec_path).mean
    speedup = novec / vec
    success = 1 if speedup >= 1.15 else 0
    with open(speedup_path, 'w') as f:
        f.write(f'{speedup}')
    with open(success_path, 'w') as f:
        f.write(f'{success}')

def calculate_peer_fraction(c1_path, c2_path, c1_is_faster_path, fraction_path, is_faster_path):
    with open(c1_is_faster_path) as f:
        c1_is_faster = int(f.read())
    c1 = Summary().parse_from_summary(c1_path).mean
    c2 = Summary().parse_from_summary(c2_path).mean
    if c1_is_faster == 1:
        small = c1
        large = c2
    else:
        small = c2
        large = c1
    fraction = large / small
    is_faster = 1 if small < large else 0 
    with open(fraction_path, 'w') as f:
        f.write(f'{fraction}')
    with open(is_faster_path, 'w') as f:
        f.write(f'{is_faster}')

def calculate_is_faster(path1, path2, output_path, ty=float):
    with open(path1) as f:
        i1 = ty(f.read())
    with open(path2) as f:
        i2 = ty(f.read())
    with open(output_path, 'w') as f:
        f.write(f'{1 if i1 < i2 else 0}')

def calculate_max(sample_paths, output_path, ty=float):
    samples = []
    for path in sample_paths:
        with open(path) as f:
            samples.append(ty(f.read()))
    with open(output_path, 'w') as f:
        f.write(f'{max(samples)}')

# TODO: generalize this function and merge with max
def calculate_sum_of_logs(sample_paths, output_path):
    samples = []
    for path in sample_paths:
        with open(path) as f:
            runtime = Summary().parse_from_summary(path).mean
            samples.append(runtime)
    with open(output_path, 'w') as f:
        f.write(f'{sum(log(samples))}')

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

