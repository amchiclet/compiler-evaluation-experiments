from build import \
    PathBuilder, \
    iterate_compiler_modes, \
    iterate_mutations
from scipy.stats import tmean
from compilers import compilers
import os

from runtime import get_runtime_stats
from vector_speedup import get_vec_speedup_stats
from cost_model import get_cost_model_stats
from vectorizable import get_vectorizable_stats
from peer_speedup import get_peer_speedup_stats
from peer_rank import get_peer_rank_stats
from vector_rate import get_vector_rate_stats

def import_patterns():
    import sys
    base_dir = os.getcwd()
    sys.path = [base_dir] + sys.path
    from patterns import patterns
    return patterns

def read_runtimes_database(patterns):
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

def read_vector_rates_database(patterns):
    database = {}
    for compiler, mode in iterate_compiler_modes():
        for pattern, program, mutation in iterate_mutations(patterns):
            key = (compiler, mode, pattern, program, mutation)
            path = PathBuilder(*key).vector_rate_path()
            if os.path.exists(path):
                with open(path) as f:
                    database[key] = float(f.read())
    return database

def generate_report():
    patterns = import_patterns()

    runtimes = read_runtimes_database(patterns)

    runtime_stats = get_runtime_stats(runtimes)
    print(runtime_stats.pprint())
    print()
    vec_speedup_stats = get_vec_speedup_stats(runtimes)
    print(vec_speedup_stats.pprint())
    print()
    cost_model_stats = get_cost_model_stats(runtimes)
    print(cost_model_stats.pprint())
    print()
    vectorizable_stats = get_vectorizable_stats(runtimes)
    print(vectorizable_stats.pprint())
    print()
    peer_speedup_stats = get_peer_speedup_stats(runtimes)
    print(peer_speedup_stats.pprint())
    print()

    peer_rank_stats = get_peer_rank_stats(runtimes)
    print(peer_rank_stats.pprint())
    print()

    vector_rates = read_vector_rates_database(patterns)

    vector_rate_stats = get_vector_rate_stats(vector_rates)
    print(vector_rate_stats.pprint())

generate_report()
