from numpy import quantile, median
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

def confidence_interval_mean(samples, level, min_val=None, max_val=None, n_samples=None):
    if n_samples is None:
        n_samples = len(samples)
    mean = arithmetic_mean(samples)
    std = sample_std(samples)
    dof = n_samples - 1
    t_value = t.ppf((1+level)/2, dof)
    error = t_value * std / sqrt(n_samples)
    return [mean - error, mean + error]

def confidence_interval_proportion(proportion, n_samples, level):
    z_value = norm.ppf((1+level)/2)
    error = z_value * sqrt((proportion * (1-proportion)) / n_samples)
    return [max(proportion - error, 0.0),
            min(proportion + error, 1.0)]

def calculate_ci_arithmetic(samples, min_val=None, max_val=None, n_samples=None):
    ci90 = confidence_interval_mean(samples, 0.90, min_val, max_val, n_samples)
    ci95 = confidence_interval_mean(samples, 0.95, min_val, max_val, n_samples)
    ci99 = confidence_interval_mean(samples, 0.99, min_val, max_val, n_samples)
    if min_val is not None:
        ci90[0] = max(ci90[0], min_val)
        ci95[0] = max(ci95[0], min_val)
        ci99[0] = max(ci99[0], min_val)
    if max_val is not None:
        ci90[1] = min(ci90[1], max_val)
        ci95[1] = min(ci95[1], max_val)
        ci99[1] = min(ci99[1], max_val)
    return (ci90, ci95, ci99)

def calculate_ci_geometric(samples, min_val=None, max_val=None, n_samples=None):
    log_samples = list(map(log, samples))
    log_ci90 = confidence_interval_mean(log_samples, 0.90, min_val, max_val, n_samples)
    log_ci95 = confidence_interval_mean(log_samples, 0.95, min_val, max_val, n_samples)
    log_ci99 = confidence_interval_mean(log_samples, 0.99, min_val, max_val, n_samples)

    ci90 = [e**log_ci95[0], e**log_ci90[1]]
    ci95 = [e**log_ci95[0], e**log_ci95[1]]
    ci99 = [e**log_ci99[0], e**log_ci99[1]]
    if min_val is not None:
        ci90[0] = max(ci90[0], min_val)
        ci95[0] = max(ci95[0], min_val)
        ci99[0] = max(ci99[0], min_val)
    if max_val is not None:
        ci90[1] = min(ci90[1], max_val)
        ci95[1] = min(ci95[1], max_val)
        ci99[1] = min(ci99[1], max_val)
    return (ci90, ci95, ci99)

def calculate_ci_proportion(occurrences, total, n_samples=None):
    if n_samples is None:
        n_samples = total
    proportion = occurrences / total
    ci90 = confidence_interval_proportion(proportion, n_samples, 0.90)
    ci95 = confidence_interval_proportion(proportion, n_samples, 0.95)
    ci99 = confidence_interval_proportion(proportion, n_samples, 0.99)
    return (ci90, ci95, ci99)

def find_outliers(values, keys):
    outliers = []

    import numpy

    numpy.seterr(all='raise')

    # avg = tmean(values)
    try:
        avg = median(values)
        bound = 0.01 * avg
    except FloatingPointError as fpe:
        return None, None

    try:
        max_val = avg + bound
    except FloatingPointError as fpe:
        return None, None
    try:
        min_val = avg - bound
    except FloatingPointError as fpe:
        return None, None

    if max_val < min_val:
        temp = max_val
        max_val = min_val
        min_val = temp
    distribution = (min_val, avg, max_val)
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
    return InterestingCases([is_less, is_greater])

def create_max_cases():
    return InterestingCases([is_greater])

def is_wider(pair1, pair2):
    width1 = pair1[1] - pair1[0]
    width2 = pair2[1] - pair2[0]
    return width1 > width2

is_narrower = negate(is_wider)

def create_max_spread_cases():
    return InterestingCases([is_wider])

class InterestingCase:
    def __init__(self, merge_predicate):
        self.normalized = None
        self.raw = None
        self.key = None
        self.merge_predicate = merge_predicate
    def merge(self, key, normalized, raw):
        if self.normalized is None or self.merge_predicate(normalized, self.normalized):
            self.normalized = normalized
            self.key = key
            self.raw = raw
    def pprint(self):
        return f'{self.key} {self.normalized} ({self.raw})'

class InterestingCases:
    def __init__(self, merge_predicates):
        self.cases = {}
        self.merge_predicates = merge_predicates
    def iterate(self):
        return iter(self.cases.items())
    def merge(self, key, new_value, raw):
        cases_key = key[:-1]
        if len(cases_key) == 1:
            cases_key = cases_key[0]
        if cases_key not in self.cases:
            self.cases[cases_key] = [InterestingCase(p) for p in self.merge_predicates]
        for outlier in self.cases[cases_key]:
            outlier.merge(key, new_value, raw)
    def pprint(self, keys=None):
        lines = []
        keys = keys if keys is not None else self.cases.keys()
        for key in keys:
            if key in self.cases:
                for case in self.cases[key]:
                    lines.append(f'Interesting case: {case.pprint()}')
        return '\n'.join(lines)

class Stats:
    def __init__(self, name, cis, interesting_cases):
        self.name = name
        self.cis = cis
        self.interesting_cases = interesting_cases
    def pprint(self):
        lines = [self.name]
        for key, ci in self.cis.items():
            lines.append(f'{key}')
            lines.append(f'95% CI {ci[1]}')
            if self.interesting_cases is not None:
                if key in self.interesting_cases.cases:
                    for case in self.interesting_cases.cases[key]:
                        lines.append(f'Interesting case: {case.raw}')
                else:
                    lines.append(f'No interesting cases')
        return '\n'.join(lines)
    def keys(self):
        return self.cis.keys()
    def format_ci_row(self, name, order):
        row = [name]
        for ci_key in order:
            if ci_key in self.cis:
                ci = self.cis[ci_key]
                row.append(f'[{ci[1][0]:.2f}, {ci[1][1]:.2f}]')
            else:
                row.append('N/A')
        return row
    def format_interesting_case_row(self, name, order, format_raw):
        row = [name]
        for key in order:
            if self.interesting_cases is None:
                row.append('N/A')
            else:
                if key not in self.interesting_cases.cases:
                    row.append('N/A')
                else:
                    lines = []
                    for case in self.interesting_cases.cases[key]:
                        lines.append(format_raw(case.raw))
                    row.append('\n'.join(lines))
        return row
