from build import PathBuilder, iterate_compiler_modes, iterate_mutations
from scipy.stats import tmean
from scipy import log
from compilers import compilers

def debug(d):
    for k, v in d.items():
        print(f'{k} => {v}')

import sys
import os

base_dir = os.getcwd()
sys.path = [base_dir] + sys.path
from patterns import patterns

class Outlier:
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
    def __repr__(self):
        return f'{self.raw}({self.key})({self.normalized})'

def is_greater(x, y):
    return x > y

def is_less(x, y):
    return x < y

def create_min_max_outliers():
    return Outliers([is_greater, is_less])

def is_wider(outlier_pair_1, outlier_pair_2):
    pass

def create_spread_outliers():
    return Outliers([is_greater, is_less])

class Outliers:
    def __init__(self, merge_predicates):
        self.outliers = {}
        self.merge_predicates = merge_predicates
    def merge(self, key, new_value, raw):
        outliers_key = key[:-1]
        if outliers_key not in self.outliers:
            self.outliers[outliers_key] = [Outlier(p) for p in self.merge_predicates]
        for outlier in self.outliers[outliers_key]:
            outlier.merge(key, new_value, raw)
    def debug(self):
        debug(self.outliers)

def read_runtimes_database():
    database = {}
    for compiler, mode in iterate_compiler_modes():
        for pattern, program, mutation in iterate_mutations(patterns):
            key = (compiler, mode, pattern, program, mutation)
            path = PathBuilder(*key).runtimes_ns_path()
            if os.path.exists(path):
                with open(path) as f:
                    runtimes_str = f.read()
                    database[key] = tmean(list(map(int, runtimes_str.split())))
    return database

def get_mutations(runtimes):
    mutations = set()
    for (_, _, pattern, program, mutation) in runtimes:
        mutations.add((pattern, program, mutation))
    return mutations

def read_vector_rates_database():
    database = {}
    for compiler, mode in iterate_compiler_modes():
        for pattern, program, mutation in iterate_mutations(patterns):
            key = (compiler, mode, pattern, program, mutation)
            path = PathBuilder(*key).vector_rate_path()
            if os.path.exists(path):
                with open(path) as f:
                    database[key] = float(f.read())
    return database

def merge_value(database, key, value, merge_function):
    if key not in database:
        database[key] = value
    else:
        database[key] = merge_function(database[key], value)

def update_dict_dict(d, k1, k2, v):
    if k1 not in d:
        d[k1] = {}
    d[k1][k2] = v

def get_normalized_runtimes(runtimes):
    best_mutations = {}
    for key, runtime in runtimes.items():
        merge_value(best_mutations, key[:-1], runtime, min)

    outliers = create_min_max_outliers()
    normalized = {}
    for key, runtime in runtimes.items():
        normalized[key] = best_mutations[key[:-1]] / runtime
        outliers.merge(key, normalized[key], runtime)

    return normalized, outliers

def get_normalized_vector_rates(vector_rates):
    best_mutations = {}
    for key, vector_rate in vector_rates.items():
        merge_value(best_mutations, key[:-1], vector_rate, max)

    outliers = create_min_max_outliers()
    normalized = {}
    for key, vector_rate in vector_rates.items():
        if best_mutations[key[:-1]] > 0:
            normalized[key] = vector_rate / best_mutations[key[:-1]]
            outliers.merge(key, normalized[key], vector_rate)

    return normalized, outliers

def get_normalized_vec_speedups(runtimes):
    grouped = {}
    for (compiler, mode, pattern, program, mutation), runtime in runtimes.items():
        key = (compiler, pattern, program, mutation)
        update_dict_dict(grouped, key, mode, runtime)

    speedups = {}
    for key, mode_runtimes in grouped.items():
        if 'novec' in mode_runtimes and 'fast' in mode_runtimes:
            speedups[key] = mode_runtimes['novec'] / mode_runtimes['fast']

    best_speedups = {}
    for key, speedup in speedups.items():
        merge_value(best_speedups, key[:-1], speedup, max)

    outliers = create_min_max_outliers()
    normalized = {}
    for key, speedup in speedups.items():
        normalized[key] = speedup / best_speedups[key[:-1]]
        outliers.merge(key, normalized[key], speedup)

    return normalized, outliers

def get_normalized_cost_model_performance(runtimes):
    grouped = {}
    for (compiler, mode, pattern, program, mutation), runtime in runtimes.items():
        key = (compiler, pattern, program, mutation)
        update_dict_dict(grouped, key, mode, runtime)

    n_cost_model_good = {}
    n_total_mutations = {}
    for compiler in compilers:
        n_cost_model_good[compiler] = 0
        n_total_mutations[compiler] = 0

    for key, mode_runtimes in grouped.items():
        if 'nopredict' in mode_runtimes and 'fast' in mode_runtimes:
            compiler = key[0]
            with_cost_model = mode_runtimes['fast'] * 0.95
            if mode_runtimes['nopredict'] >= with_cost_model:
                n_cost_model_good[compiler] += 1
            n_total_mutations[compiler] += 1

    normalized = {}
    for key, n_total in n_total_mutations.items():
        if n_total > 0:
            normalized[key] = n_cost_model_good[key] / n_total

    return normalized

vectorizable_threshold = 1.00
def get_normalized_vectorizables(runtimes):
    grouped = {}
    for (compiler, mode, pattern, program, mutation), runtime in runtimes.items():
        key = (compiler, pattern, program, mutation)
        update_dict_dict(grouped, key, mode, runtime)

    speedups = {}
    for key, mode_runtimes in grouped.items():
        if 'novec' in mode_runtimes and 'fast' in mode_runtimes:
            speedups[key] = mode_runtimes['novec'] / mode_runtimes['fast']

    best_speedups = {}
    for key, speedup in speedups.items():
        merge_value(best_speedups, key[:-1], speedup, max)

    n_vectorizables = {}
    n_actually_vectorized = {}
    for compiler in compilers:
        n_vectorizables[compiler] = 0
        n_actually_vectorized[compiler] = 0

    for key, speedup in speedups.items():
        compiler = key[0]
        best_speedup = best_speedups[key[:-1]]
        if best_speedup > vectorizable_threshold:
            n_vectorizables[compiler] += 1
            if speedup > vectorizable_threshold:
                n_actually_vectorized[compiler] += 1

    normalized = {}
    for key, n_total in n_vectorizables.items():
        if n_total > 0:
            normalized[key] = n_actually_vectorized[key] / n_total

    return normalized

def get_normalized_peer_speedups(runtimes):
    grouped = {}
    for (compiler, mode, pattern, program, mutation), runtime in runtimes.items():
        if mode == 'fast':
            key = (pattern, program, mutation)
            update_dict_dict(grouped, key, compiler, runtime)

    keys_to_consider = []
    overall_runtime = {}
    for key, compiler_runtimes in grouped.items():
        if all([compiler in compiler_runtimes for compiler in compilers]):
            keys_to_consider.append(key)
            for compiler, runtime in compiler_runtimes.items():
                merge_value(overall_runtime, compiler, runtime,
                            lambda v1, v2: log(v1) + log(v2))

    ascend_perf_pairs = []
    for i, c1 in enumerate(compilers[:-1]):
        for c2 in compilers[i+1:]:
            # lower runtime means better performance
            ascend_perf = (c2, c1) if overall_runtime[c1] < overall_runtime[c2] else (c1, c2)
            ascend_perf_pairs.append(ascend_perf)

    speedups = {}
    for key in keys_to_consider:
        for (slower, faster) in ascend_perf_pairs:
            slower_key = (slower, 'fast', *key)
            faster_key = (faster, 'fast', *key)
            speedups[(slower, faster, *key)] = runtimes[slower_key] / runtimes[faster_key]

    best_speedups = {}
    for key, speedup in speedups.items():
        merge_value(best_speedups, key[:-1], speedup, max)

    outliers = create_min_max_outliers()
    normalized = {}
    for key, speedup in speedups.items():
        normalized[key] = speedup / best_speedups[key[:-1]]
        outliers.merge(key, normalized[key], speedup)

    return normalized, outliers

def get_normalized_peer_ranks(runtimes):
    grouped = {}
    for (compiler, mode, pattern, program, mutation), runtime in runtimes.items():
        if mode == 'fast':
            key = (pattern, program, mutation)
            update_dict_dict(grouped, key, compiler, runtime)

    keys_to_consider = []
    overall_runtime = {}
    for key, compiler_runtimes in grouped.items():
        if all([compiler in compiler_runtimes for compiler in compilers]):
            keys_to_consider.append(key)
            for compiler, runtime in compiler_runtimes.items():
                merge_value(overall_runtime, compiler, runtime,
                            lambda v1, v2: log(v1) + log(v2))

    ascend_perf_pairs = []
    for i, c1 in enumerate(compilers[:-1]):
        for c2 in compilers[i+1:]:
            # lower runtime means better performance
            ascend_perf = (c2, c1) if overall_runtime[c1] < overall_runtime[c2] else (c1, c2)
            ascend_perf_pairs.append(ascend_perf)

    correct_ranks = {}
    for key in ascend_perf_pairs:
        correct_ranks[key] = 0
    for key in keys_to_consider:
        for (slower, faster) in ascend_perf_pairs:
            slower_key = (slower, 'fast', *key)
            faster_key = (faster, 'fast', *key)
            if runtimes[slower_key] > runtimes[faster_key]:
                correct_ranks[(slower, faster)] += 1

    normalized = {}
    n_mutation_count = len(keys_to_consider)
    for key, count in correct_ranks.items():
        normalized[key] = count / n_mutation_count

    return normalized

runtimes = read_runtimes_database()
# normalized, outliers = get_normalized_runtimes(runtimes)
# normalized, outliers = get_normalized_vec_speedups(runtimes)
normalized, outliers = get_normalized_peer_speedups(runtimes)

# x3 = get_normalized_vectorizables(runtimes)
# x4 = get_normalized_peer_ranks(runtimes)
# x5 = get_normalized_cost_model_performance(runtimes)

debug(normalized)
outliers.debug()
# vector_rates = read_vector_rates_database()
# normalized_3, outliers_3 = get_normalized_vector_rates(vector_rates)

# for (pattern, p, m) in get_mutations(runtimes):
#     nopredict = runtimes[('icc', 'nopredict', pattern, p, m)]
#     fast = runtimes[('icc', 'fast', pattern, p, m)]
#     with_cost_model = fast * 0.95
#     is_prediction_good = nopredict >= with_cost_model
#     print(f'nopredict({nopredict:.2f}) > fast({fast:.2f})? {is_prediction_good}')
