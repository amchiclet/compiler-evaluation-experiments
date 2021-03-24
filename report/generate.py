from build import \
    PathBuilder, \
    iterate_compiler_modes, \
    iterate_mutations, \
    iterate_modes
from scipy.stats import tmean
from compilers import compilers
import os

import report.runtime
import report.vector_speedup
import report.vectorizable
import report.cost_model
import report.peer_speedup
import report.peer_rank
import importlib.util

from report.peer_metrics import is_approximate_key, x_approximates_y_key
from report.vector_rate import get_vector_rate_stats

from build import PathBuilder
from random import sample

def import_patterns(base_dir=None):
    if base_dir is None:
        base_dir = os.getcwd()
    spec = importlib.util.spec_from_file_location('patterns', f'{base_dir}/patterns.py')
    foo = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(foo)
    return foo.patterns

def import_blacklist(base_dir):
    if base_dir is None:
        base_dir = os.getcwd()
    path = f'{base_dir}/blacklist.py'
    if os.path.exists(path):
        spec = importlib.util.spec_from_file_location('blacklist', path)
        foo = importlib.util.module_from_spec(spec)
        spec.loader.exec_module(foo)
        return foo.blacklist
    else:
        return []

from multiprocessing import Pool, Manager
from functools import partial

def read_runtime_multi_experiment(base_dir, key):
    path = PathBuilder(*key).runtimes_ns_path()
    full_path = f'{base_dir}/{path}'
    if os.path.exists(full_path):
        with open(full_path) as f:
            runtimes_str = f.read()
            runtime = tmean(list(map(int, runtimes_str.split())))
            c, m, p, i, mu = key
            new_key = (c, m, f'{base_dir}.{p}', i, mu)
            return (new_key, runtime)
    raise RuntimeError(f'File not found {full_path}')

def read_runtime(base_dir, key):
    path = PathBuilder(*key).runtimes_ns_path()
    full_path = f'{base_dir}/{path}'
    if os.path.exists(full_path):
        with open(full_path) as f:
            runtimes_str = f.read()
            runtime = tmean(list(map(int, runtimes_str.split())))
            return (key, runtime)
    raise RuntimeError(f'File not found {full_path}')

def read_runtime_fully_qualified(key):
    compiler, mode, (base_dir, p), i, m = key
    path = PathBuilder(compiler, mode, p, i, m).runtimes_ns_path()
    full_path = f'{base_dir}/{path}'
    if os.path.exists(full_path):
        with open(full_path) as f:
            runtimes_str = f.read()
            runtime = tmean(list(map(int, runtimes_str.split())))
            return (key, runtime)
    # raise RuntimeError(f'File not found {full_path}')
    print(f'File not found {full_path}')
    return None

def read_vector_rate(key):
    path = PathBuilder(*key).vector_rate_path()
    if os.path.exists(path):
        with open(path) as f:
            vector_rate = float(f.read())
            return (key, vector_rate)

def mutations(patterns):
    for compiler, mode in iterate_compiler_modes():
        for pattern, program, mutation in iterate_mutations(patterns):
            yield compiler, mode, pattern, program, mutation

def read_runtimes_database(base_dir, patterns):
    f = partial(read_runtime, base_dir)
    return dict(Pool(1).map(f, mutations(patterns)))

def read_runtimes_database_fully_qualified(patterns):
    # return dict(Pool().map(read_runtime_fully_qualified, mutations(patterns)))
    pairs = Pool().map(read_runtime_fully_qualified, mutations(patterns))
    pairs[:] = [pair for pair in pairs if pair is not None]
    return dict(pairs)

def read_runtimes_database_multi_experiment(base_dir, patterns):
    f = partial(read_runtime_multi_experiment, base_dir)
    return dict(Pool(1).map(f, mutations(patterns)))

def read_vector_rates_database(patterns):
    return dict(Pool().map(read_vector_rate, mutations(patterns)))

def read_function(path):
    core = []
    with open(path) as f:
        for line in f:
            if not line or line == '\n' or '#include' in line:
                continue
            core.append(line)
    return ''.join(core)

from tabulate import tabulate
from hashlib import md5
from loguru import logger

def compute_file_md5(path):
    with open(path) as f:
        m = md5()
        m.update(f.read().encode('utf-8'))
        return m.digest()

def get_ok_patterns(base_dir):
    n_samples = 0
    n_ok_samples = 0
    n_fpe_samples = 0
    n_duplicate_mutations = 0
    n_singleton_mutations = 0

    patterns = import_patterns(base_dir)
    blacklist = import_blacklist(base_dir)
    ok_patterns = []
    hashes = set()
    for p, instances in patterns:
        ok_instances = []
        for i, mutations in instances:
            if (p, i) not in blacklist:
                ok_instances.append((i, mutations))
                n_ok_samples += len(mutations)

                # This section is commented out for now
                # Currently the plan is to allow de-duplication and handle
                # singletons during the generation phase

                # ok_mutations = []
                # for m in mutations:
                #     pb = PathBuilder(pattern=p, program=i, mutation=m)
                #     full_path = f'{base_dir}/{pb.core_path()}'
                #     filehash = compute_file_md5(full_path)
                #     if filehash not in hashes:
                #         hashes.add(filehash)
                #         ok_mutations.append(m)
                #     else:
                #         n_duplicate_mutations += 1
                # if len(ok_mutations) > 1:
                #     ok_instances.append((i, ok_mutations))
                #     n_ok_samples += len(ok_mutations)
                # else:
                #     n_singleton_mutations += 1

            else:
                n_fpe_samples += len(mutations)
            n_samples += len(mutations)
        if len(ok_instances) > 0:
            ok_patterns.append((p, ok_instances))

    print(f'Total generated mutations: {n_samples}\n'
          f'Mutations that could not be validated: {n_fpe_samples}\n'
          f'Duplicate mutations: {n_duplicate_mutations}\n'
          f'Singleton mutations: {n_singleton_mutations}\n'
          f'Remaining mutations included in experiment: {n_ok_samples}\n')
    return ok_patterns

def get_ok_patterns_fully_qualified(base_dir):
    ok_patterns = get_ok_patterns(base_dir)
    return [((base_dir, p), instances) for p, instances in ok_patterns]

def filter_patterns(patterns, n_instances, n_mutations):
    filtered_patterns = []
    for p, instances in patterns:
        filtered_instances = []
        for i, mutations in instances:
            if len(mutations) < n_mutations:
                continue
            mutation_samples = sample(mutations, k=n_mutations)
            filtered_instances.append((i, mutation_samples))

        if len(filtered_instances) < n_instances:
            continue
        instance_samples = sample(filtered_instances, k=n_instances)
        filtered_patterns.append((p, instance_samples))
    return filtered_patterns

def check_structure(pattern, n_instances, n_mutations):
    p, instances = pattern
    if len(instances) != n_instances:
        return False
    for i, mutations in instances:
        if len(mutations) != n_mutations:
            print('BAD', p, i, mutations, f'wanted {n_mutations} but got {len(mutations)}')
            return False
    return True

def get_popular_pattern_structure(patterns):
    most_popular_structure = None
    most_popular_count = None
    counts = {}
    for p, instances in patterns:
        for i, mutations in instances:
            key = (len(instances), len(mutations))
            if key not in counts:
                counts[key] = 0
            counts[key] += 1
            if most_popular_count is None or counts[key] > most_popular_count:
                most_popular_structure = key
    return most_popular_structure

def limit_patterns(patterns, n_instances, n_mutations):
    return [p for p in patterns if check_structure(p, n_instances, n_mutations)]

def generate_report(base_dir=None):
    if base_dir is None:
        base_dir = os.getcwd()
    ok_patterns = get_ok_patterns(base_dir)
    n_instances, n_mutations = get_popular_pattern_structure(ok_patterns)
    ok_patterns = limit_patterns(ok_patterns, n_instances, n_mutations)
    n_patterns = len(ok_patterns)

    runtimes = read_runtimes_database(base_dir, ok_patterns)

    report.runtime.add_plot_normalized_runtimes_v2(compilers, ok_patterns, runtimes)
    # report.vector_speedup.add_plot_normalized_vec_speedups(compilers, ok_patterns, runtimes, f'{base_dir}/vector_speedup.png')
    report.vectorizable.add_plot_vectorizables(compilers, ok_patterns, runtimes)
    # report.cost_model.add_plot_cost_model(compilers, ok_patterns, runtimes, f'{base_dir}/cost_model.png')
    # report.peer_speedup.add_plot_peer_speedups(compilers, ok_patterns, runtimes, f'{base_dir}/peer_speedup.png')
    # report.peer_rank.add_plot_rank_counts(compilers, ok_patterns, runtimes, f'{base_dir}/peer_rank.png')
    # return
    # report.vector_speedup.plot_vec_speedups(runtimes)
    # report.vectorizable.plot_vectorizables(runtimes)
    # report.cost_model.plot_cost_model(runtimes)
    # report.peer_speedup.plot_peer_speedups(runtimes)
    # report.peer_rank.plot_rank_counts(runtimes)

    # report.runtime.plot_ci_bar(n_patterns, runtimes)
    return
    runtime_stats = report.runtime.get_stats(runtimes)
    vec_speedup_stats = report.vector_speedup.get_stats(runtimes)
    vectorizable_stats = report.vectorizable.get_stats(runtimes)
    cost_model_stats = report.cost_model.get_stats(runtimes)
    peer_speedup_stats = report.peer_speedup.get_stats(runtimes)
    peer_rank_stats = report.peer_rank.get_stats(runtimes)

    compiler_order = sorted(runtime_stats.keys())

    ci_table_1 = []
    table_1_header = ['', *[c for c in compiler_order]]
    ci_table_1.append(
        runtime_stats.format_ci_row('runtime stability',
                                    compiler_order))
    ci_table_1.append(
        vec_speedup_stats.format_ci_row('vec speedup stability',
                                        compiler_order))
    ci_table_1.append(
        vectorizable_stats.format_ci_row('vectorizability stability',
                                         [c for c in compiler_order]))
    ci_table_1.append(cost_model_stats.format_ci_row('cost model stability', compiler_order))
    print('Confidence intervals\n')
    print(tabulate(ci_table_1, headers=table_1_header))
    print()

    peer_table_map = {}
    peer_cases_map = {}
    compiler_pair_keys = {*peer_speedup_stats.keys(),
                          *peer_rank_stats.keys()}
    compiler_pair_order = sorted(list(compiler_pair_keys))
    for compiler in compilers:
        peer_table = []
        pair_order = [key for key in compiler_pair_order
                      if key.startswith(compiler) and not is_approximate_key(key)]
        peer_table.append(peer_speedup_stats.format_ci_row('peer speedup',
                                                            pair_order))
        peer_table.append(peer_rank_stats.format_ci_row('peer proportion',
                                                         pair_order))
        peer_table_map[compiler] = (peer_table, pair_order)

        peer_case = peer_speedup_stats.format_interesting_case_row(
            'peer speedup',
            pair_order,
            report.peer_speedup.format_raw)
        peer_cases_map[compiler] = (peer_case, pair_order)

    approximates_table = []
    approximate_keys = [key for key in compiler_pair_order
                        if is_approximate_key(key)]
    approximates_table.append(peer_speedup_stats.format_ci_row('peer speedup',
                                                                approximate_keys))
    approximates_table.append(
        peer_rank_stats.format_ci_row('peer proportion',
                                      approximate_keys))

    for compiler in compilers:
        peer_table, pair_order = peer_table_map[compiler]
        header = ['', *pair_order]
        print(tabulate(peer_table, headers=header))
        print()
    approximate_header = ['', *approximate_keys]
    print(tabulate(approximates_table, headers=approximate_header))
    print()

    cases_table_1 = []
    cases_table_1.append(
        runtime_stats.format_interesting_case_row('runtime',
                                                  compiler_order,
                                                  report.runtime.format_raw))
    cases_table_1.append(
        vec_speedup_stats.format_interesting_case_row('vector speedup',
                                                      compiler_order,
                                                      report.vector_speedup.format_raw))
    cases_table_1.append(
        cost_model_stats.format_interesting_case_row('cost model',
                                                     compiler_order,
                                                     report.cost_model.format_raw))

    print('Interesting cases')
    print()
    print(tabulate(cases_table_1, headers=table_1_header))
    print()
    for compiler in compilers:
        peer_case, pair_order = peer_cases_map[compiler]
        header = ['', *pair_order]
        print(tabulate([peer_case], headers=header))
        print()

    interesting_mutations = set()
    interesting_mutations.update(report.runtime.get_paths(runtime_stats))
    interesting_mutations.update(report.vector_speedup.get_paths(vec_speedup_stats))
    interesting_mutations.update(report.cost_model.get_paths(cost_model_stats))
    interesting_mutations.update(report.peer_speedup.get_paths(peer_speedup_stats))
    print('Raw runtimes')
    print()
    sorted_mutation_ids = sorted(list(interesting_mutations))
    for compiler in compilers:
        rows = []
        header = ['mutation-id']
        for (pattern, program, mutation) in sorted_mutation_ids:
            row = [(pattern, program, mutation)]
            for mode in iterate_modes():
                header.append(f'{compiler}-{mode}')
                key = (compiler, mode, pattern, program, mutation)
                if key in runtimes:
                    row.append(runtimes[key])
                else:
                    row.append('N/A')
            rows.append(row)
        print(tabulate(rows, headers=header, floatfmt='.2f'))
        print()

    # print('Source code')
    # for (pattern, program, mutation) in sorted_mutation_ids:
    #     print(f'// {(pattern, program, mutation)}')
    #     path = PathBuilder(pattern=pattern,
    #                        program=program,
    #                        mutation=mutation).core_path()
    #     print(read_function(path))


    # vector_rates = read_vector_rates_database(patterns)

    # vector_rate_stats = get_vector_rate_stats(vector_rates)
    # print(vector_rate_stats.pprint())

if __name__ == '__main__':
    generate_report()
