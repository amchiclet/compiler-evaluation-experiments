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

def read_runtime(base_dir, key):
    path = PathBuilder(*key).runtimes_ns_path()
    full_path = f'{base_dir}/{path}'
    if os.path.exists(full_path):
        with open(full_path) as f:
            runtimes_str = f.read()
            runtime = tmean(list(map(int, runtimes_str.split())))
            return (key, runtime)
    raise RuntimeError(f'File not found {full_path}')

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
    return dict(Pool().map(f, mutations(patterns)))

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
                ok_mutations = []
                for m in mutations:
                    pb = PathBuilder(pattern=p, program=i, mutation=m)
                    full_path = f'{base_dir}/{pb.core_path()}'
                    filehash = compute_file_md5(full_path)
                    if filehash not in hashes:
                        hashes.add(filehash)
                        ok_mutations.append(m)
                    else:
                        n_duplicate_mutations += 1
                if len(ok_mutations) > 1:
                    ok_instances.append((i, ok_mutations))
                    n_ok_samples += len(ok_mutations)
                else:
                    n_singleton_mutations += 1
            else:
                n_fpe_samples += len(mutations)
            n_samples += len(mutations)
        ok_patterns.append((p, ok_instances))

    print(f'Total generated mutations: {n_samples}\n'
          f'Mutations that could not be validated: {n_fpe_samples}\n'
          f'Duplicate mutations: {n_duplicate_mutations}\n'
          f'Singleton mutations: {n_singleton_mutations}\n'
          f'Remaining mutations included in experiment: {n_ok_samples}\n')
    return ok_patterns

def generate_report(base_dir=None):
    if base_dir is None:
        base_dir = os.getcwd()
    ok_patterns = get_ok_patterns(base_dir)
    runtimes = read_runtimes_database(base_dir, ok_patterns)

    interesting_mutations = set()

    runtime_stats = report.runtime.get_stats(runtimes)

    ci_table_1 = []
    cases_table_1 = []
    compiler_order = sorted(runtime_stats.keys())

    ci_table_1.append(
        runtime_stats.format_ci_row('runtime stability',
                                    compiler_order))
    cases_table_1.append(
        runtime_stats.format_interesting_case_row('runtime',
                                                  compiler_order,
                                                  report.runtime.format_raw))
    interesting_mutations.update(report.runtime.get_paths(runtime_stats))

    vec_speedup_stats = report.vector_speedup.get_stats(runtimes)

    ci_table_1.append(
        vec_speedup_stats.format_ci_row('vec speedup stability',
                                        compiler_order))
    cases_table_1.append(
        vec_speedup_stats.format_interesting_case_row('vector speedup',
                                                      compiler_order,
                                                      report.vector_speedup.format_raw))
    interesting_mutations.update(report.vector_speedup.get_paths(vec_speedup_stats))

    vectorizable_stats = report.vectorizable.get_stats(runtimes)
    ci_table_1.append(
        vectorizable_stats.format_ci_row('vectorizability stability',
                                         [c for c in compiler_order]))

    cost_model_stats = report.cost_model.get_stats(runtimes)
    ci_table_1.append(cost_model_stats.format_ci_row('cost model stability', compiler_order))
    cases_table_1.append(
        cost_model_stats.format_interesting_case_row('cost model',
                                                     compiler_order,
                                                     report.cost_model.format_raw))

    interesting_mutations.update(report.cost_model.get_paths(cost_model_stats))

    peer_table_map = {}
    peer_cases_map = {}

    peer_speedup_stats = report.peer_speedup.get_stats(runtimes)

    peer_rank_stats = report.peer_rank.get_stats(runtimes)
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

    interesting_mutations.update(report.peer_speedup.get_paths(peer_speedup_stats))

    approximates_table = []
    approximate_keys = [key for key in compiler_pair_order
                        if is_approximate_key(key)]
    approximates_table.append(peer_speedup_stats.format_ci_row('peer speedup',
                                                                approximate_keys))
    approximates_table.append(
        peer_rank_stats.format_ci_row('peer proportion',
                                      approximate_keys))


    table_1_header = ['', *[c for c in compiler_order]]

    print('Confidence intervals\n')
    print(tabulate(ci_table_1, headers=table_1_header))
    print()
    for compiler in compilers:
        peer_table, pair_order = peer_table_map[compiler]
        header = ['', *pair_order]
        print(tabulate(peer_table, headers=header))
        print()
    approximate_header = ['', *approximate_keys]
    print(tabulate(approximates_table, headers=approximate_header))
    print()

    print('Interesting cases')
    print()
    print(tabulate(cases_table_1, headers=table_1_header))
    print()
    for compiler in compilers:
        peer_case, pair_order = peer_cases_map[compiler]
        header = ['', *pair_order]
        print(tabulate([peer_case], headers=header))
        print()

    print('Raw runtimes')
    print()
    # rows = []
    # header = ['mutation-id']
    # for compiler, mode in iterate_compiler_modes():
    #     header.append(f'{compiler}-{mode}')
    # sorted_mutation_ids = sorted(list(interesting_mutations))
    # for (pattern, program, mutation) in sorted_mutation_ids:
    #     row = [(pattern, program, mutation)]
    #     for compiler, mode in iterate_compiler_modes():
    #         key = (compiler, mode, pattern, program, mutation)
    #         row.append(runtimes[key])
    #     rows.append(row)

    # print(tabulate(rows, headers=header, floatfmt='.2f'))

    sorted_mutation_ids = sorted(list(interesting_mutations))
    for compiler in compilers:
        rows = []
        header = ['mutation-id']
        for (pattern, program, mutation) in sorted_mutation_ids:
            row = [(pattern, program, mutation)]
            for mode in iterate_modes():
                header.append(f'{compiler}-{mode}')
                key = (compiler, mode, pattern, program, mutation)
                row.append(runtimes[key])
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
