from numpy import quantile
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

def calculate_ci_geometric(samples):
    log_samples = list(map(log, samples))
    log_ci90 = confidence_interval_mean(log_samples, 0.90)
    log_ci95 = confidence_interval_mean(log_samples, 0.95)
    log_ci99 = confidence_interval_mean(log_samples, 0.99)
    ci90 = (e**log_ci95[0], e**log_ci90[1])
    ci95 = (e**log_ci95[0], e**log_ci95[1])
    ci99 = (e**log_ci99[0], e**log_ci99[1])
    return (ci90, ci95, ci99)

def calculate_ci_proportion(occurrences, total):
    proportion = occurrences / total
    ci90 = confidence_interval_proportion(proportion, total, 0.90)
    ci95 = confidence_interval_proportion(proportion, total, 0.95)
    ci99 = confidence_interval_proportion(proportion, total, 0.99)
    return (ci90, ci95, ci99)

def find_outliers(values, keys):
    outliers = []
    q1 = quantile(values, 0.25)
    q3 = quantile(values, 0.75)
    iqr = q3 - q1
    max_val = q3 + 1.5 * iqr
    min_val = q1 - 1.5 * iqr
    distribution = (min_val, q1, q3, max_val)
    for val, key in zip(values, keys):
        if val < min_val or max_val < val:
            outliers.append((val, key))
    return distribution, outliers

def negate(f):
    def not_f(x, y):
        return not f(x, y)
    return not_f

def is_greater(x, y):
    return x > y

is_less = negate(is_greater)

def create_min_max_cases():
    return InterestingCases([is_greater, is_less])

def is_wider(pair1, pair2):
    width1 = pair1[1] - pair1[0]
    width2 = pair2[1] - pair2[0]
    return width1 > width2

is_narrower = negate(is_wider)

def create_max_spread_cases():
    return InterestingCases([is_narrower])

class InterestingCase:
    def __init__(self, merge_predicate):
        self.normalized = None
        self.raw = None
        self.key = None
        self.merge_predicate = merge_predicate
    def merge(self, key, normalized, raw):
        if self.normalized is None or self.merge_predicate(self.normalized, normalized):
            self.normalized = normalized
            self.key = key
            self.raw = raw

class InterestingCases:
    def __init__(self, merge_predicates):
        self.cases = {}
        self.merge_predicates = merge_predicates
    def merge(self, key, new_value, raw):
        cases_key = key[:-1]
        if cases_key not in self.cases:
            self.cases[cases_key] = [InterestingCase(p) for p in self.merge_predicates]
        for outlier in self.cases[cases_key]:
            outlier.merge(key, new_value, raw)
