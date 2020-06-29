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

    normalized = {}
    for key, runtime in runtimes.items():
        normalized[key] = best_mutations[key[:-1]] / runtime
    return normalized

def get_normalized_vector_rates(vector_rates):
    best_mutations = {}
    for key, vector_rate in vector_rates.items():
        merge_value(best_mutations, key[:-1], vector_rate, max)

    normalized = {}
    for key, vector_rate in vector_rates.items():
        if best_mutations[key[:-1]] > 0:
            normalized[key] = vector_rate / best_mutations[key[:-1]]
    return normalized

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

    normalized = {}
    for key, speedup in speedups.items():
        normalized[key] = speedup / best_speedups[key[:-1]]

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
    debug(best_speedups)
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

    normalized = {}
    for key, speedup in speedups.items():
        normalized[key] = speedup / best_speedups[key[:-1]]

    return normalized

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
debug(runtimes)
# x = get_normalized_peer_ranks(runtimes)
# vector_rates = read_vector_rates_database()
# x = get_normalized_vectorizables(runtimes)
# debug(x)
