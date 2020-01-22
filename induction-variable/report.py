import delegator
import os
import os.path
from config import compilers, executables, Compiler, vtune_rounds
import argparse
import xml.etree.ElementTree as ET
import shutil
import statistics

class Metrics:
    # all of these are supposed to have a function with name format_*
    def get_attribute_names():
        return [
            'runtime',
        ]

    def __init__(self):
        self.runtimes = []

    def format_values(self, values):
        if not values:
            return 'N/A'
        return self.format_range(values)

    def format_range(self, values):
        # print(values)
        mean = statistics.mean(values)
        stddev = statistics.stdev(values) if len(values) > 1 else 0
        return f'{mean:.2f} ± {stddev:.2f}'

    def format_runtime(self):
        return self.format_values(self.runtimes)

    def parse_runtimes(self, path):
        if not os.path.exists(path):
            return
        runtimes = []
        with open(path) as f:
            for line in f:
                self.runtimes.append(int(line.split()[2]))

def parse_metrics(args):
    metrics = {}
    build_path = args.build_root_dir
    compiler_names = [c.name for c in compilers]
    for compiler_name in compiler_names:
        metrics[compiler_name] = {}
        for executable_name, _ in executables:
            metric = Metrics()
            runtime_path = f'{build_path}/{compiler_name}/{executable_name}.runtimes'
            metric.parse_runtimes(runtime_path)
            metrics[compiler_name][executable_name] = metric
    return metrics

def get_runtime(compiler, executable, table):
    runtime_range = table[compiler]['runtime'][executable]
    runtime = float(runtime_range.split()[0])
    return runtime

def get_stability_index(runtimes, base, threshold):
    n_stable = sum(((r - base) / base) < threshold for r in runtimes)
    return float(n_stable) / len(runtimes)

def get_speedup(runtimes, base):
    return statistics.mean([r / base for r in runtimes])

class Agg:
    def __init__(self, runtimes):
        self.mean = statistics.mean(runtimes)
        self.min = min(runtimes)

def get_aggregate(runtimes):
    return Agg(runtimes)

def get_vector_opportunity(scalar_runtimes, vector_runtimes):
    return statistics.geometric_mean([s/v for s, v in zip(scalar_runtimes, vector_runtimes)])

def format_for_latex(compiler_name, rows):
    print('\\hline')
    # print(f'\\multicolumn{{6}}{{| c |}}{{{compiler_name}}} \\\\')
    # print('\\hline')
    print(f'\\multirow{{10}}{{*}}{{{compiler_name}}}')
    for row in rows:
        print(' & '.join(row) + ' \\\\')

def gather_program_names():
    program_names = []
    for executable_name, _ in executables:
        # The executable_name should look like 'some_prefix_here_p01_v02_c'
        p = executable_name.split('_')[-3]
        if p not in program_names:
            program_names.append(p)
    return program_names

def gather_raw_data():
    parser = argparse.ArgumentParser()
    parser.add_argument('--build_root_dir', required=True)
    args = parser.parse_args()
    metrics = parse_metrics(args)

    raw_data = {}
    for compiler_name in [c.name for c in compilers]:
        raw_data[compiler_name] = {}
        for attribute_name in Metrics.get_attribute_names():
            raw_data[compiler_name][attribute_name] = {}
            for executable_name, _ in executables:
                metric = metrics[compiler_name][executable_name]
                formatter = getattr(metric, f'format_{attribute_name}')
                raw_data[compiler_name][attribute_name][executable_name] = formatter()
    return raw_data

def gather_runtimes(raw_data, compiler_names, program_names):
    runtimes = {}
    for compiler_name in compiler_names:
        scalar = compiler_name + '_s'
        vector = compiler_name + '_v'

        for c in [scalar, vector]:
            runtimes[c] = {}
            for p in program_names:
                runtimes[c][p] = []


            for executable_name, _ in executables:
                program_name = executable_name.split('_')[-3]
                runtimes[c][program_name].append(get_runtime(c, executable_name, raw_data))
    return runtimes

def gather_winners(compiler_name, program_names, runtimes):
    scalar = compiler_name + '_s'
    vector = compiler_name + '_v'

    winners = {}
    for c in [scalar, vector]:
        winners[c] = {}
        for p in program_names:
            winners[c][p] = min(runtimes[c][p])
    return winners

def gather_slowdowns(compiler_name, program_names, runtimes, winners):
    scalar = compiler_name + '_s'
    vector = compiler_name + '_v'

    slowdowns = {}
    for c in [scalar, vector]:
        slowdowns[c] = {}
        for p in program_names:
            w = winners[c][p]
            slowdowns[c][p] = [r / w for r in runtimes[c][p]]
    return slowdowns

def gather_stabilities(compiler_name, program_names, runtimes, winners, threshold):
    scalar = compiler_name + '_s'
    vector = compiler_name + '_v'

    stabilities = {}
    for c in [scalar, vector]:
        stabilities[c] = {}
        for p in program_names:
            stabilities[c][p] = get_stability_index(runtimes[c][p],
                                                    winners[c][p],
                                                    threshold)
    return stabilities

def gather_vector_opportunities(compiler_name, program_names, runtimes):
    scalar = compiler_name + '_s'
    vector = compiler_name + '_v'

    vector_opportunities = {}
    for p in program_names:
        vector_opportunities[p] = []

    for p in program_names:
        runtimes_s = runtimes[scalar][p]
        runtimes_v = runtimes[vector][p]
        for s, v in zip(runtimes_s, runtimes_v):
            vector_opportunities[p].append(s / v)

    return vector_opportunities

def gather_stabilized_vector_opportunities(compiler_name, program_names, winners):
    scalar = compiler_name + '_s'
    vector = compiler_name + '_v'

    svos = {}
    for p in program_names:
        svos[p] = winners[scalar][p] / winners[vector][p]
    return svos

def gather_top_speeds(compiler_name, program_names, winners):
    scalar = compiler_name + '_s'
    vector = compiler_name + '_v'

    top_speeds = {}
    for p in program_names:
        top_speeds[p] = min(winners[scalar][p], winners[vector][p])
    return top_speeds

def gather_best_runtimes(compiler_name, program_names, runtimes):
    scalar = compiler_name + '_s'
    vector = compiler_name + '_v'

    best_runtimes = {}
    for p in program_names:
        runtimes_s = runtimes[scalar][p]
        runtimes_v = runtimes[vector][p]
        best_runtimes[p] = [min(s, v) for s, v in zip(runtimes_s, runtimes_v)]
    return best_runtimes

def prod(l):
    r = 1.0
    for i in l:
        r *= i
    return r

def gather_best_best_runtimes(program_names, all_best_runtimes):
    best_best_runtimes = {}
    for p in program_names:
        min_prod = None
        for best_runtimes in all_best_runtimes:
            new_prod = prod(best_runtimes[p])
            if not min_prod or new_prod < min_prod:
                min_prod = new_prod
                best_best_runtimes[p] = best_runtimes[p]
    return best_best_runtimes
    
def gather_peer_headrooms(program_names, best_best_runtimes, best_runtimes):
    peer_headrooms = {}
    for p in program_names:
        peer_headrooms[p] = [best / me for best, me in zip(best_best_runtimes[p], best_runtimes[p])]
    return peer_headrooms

def gather_best_top_speeds(program_names, all_top_speeds):
    best_top_speeds = {}
    for p in program_names:
        best_top_speeds[p] = None
        for top_speeds in all_top_speeds:
            if not best_top_speeds[p] or top_speeds[p] < best_top_speeds[p]:
                best_top_speeds[p] = top_speeds[p]
    return best_top_speeds
            
def gather_stabilized_peer_headrooms(program_names, best_top_speeds, top_speeds):
    sphs = {}
    for p in program_names:
        sphs[p] = best_top_speeds[p] / top_speeds[p]
    return sphs

class IntraCompiler:
    def __init__(self, compiler_name, program_names, runtimes, threshold):
        self.winners = gather_winners(compiler_name,
                                      program_names,
                                      runtimes)
        self.slowdowns = gather_slowdowns(compiler_name,
                                          program_names,
                                          runtimes,
                                          self.winners)
        self.stabilities = gather_stabilities(compiler_name,
                                              program_names,
                                              runtimes,
                                              self.winners,
                                              threshold)
        self.vos = gather_vector_opportunities(compiler_name,
                                               program_names,
                                               runtimes)
        self.svos = gather_stabilized_vector_opportunities(compiler_name,
                                                           program_names,
                                                           self.winners)
        self.best_runtimes = gather_best_runtimes(compiler_name,
                                                  program_names,
                                                  runtimes)
        self.top_speeds = gather_top_speeds(compiler_name,
                                            program_names,
                                            self.winners)

def gather_intra_compilers(compiler_names, program_names, runtimes, threshold):
    intra_compilers = {}
    for c in compiler_names:
        intra_compilers[c] = IntraCompiler(c, program_names, runtimes, threshold)
    return intra_compilers

class InterCompiler:
    def __init__(self, intra_compiler, program_names, best_best_runtimes, best_top_speeds):
        self.phs = gather_peer_headrooms(program_names,
                                         best_best_runtimes,
                                         intra_compiler.best_runtimes)
        self.sphs =  gather_stabilized_peer_headrooms(program_names,
                                                      best_top_speeds,
                                                      intra_compiler.top_speeds)

def gather_inter_compilers(intra_compilers, program_names):
    all_best_runtimes = [c.best_runtimes for c in intra_compilers.values()]
    best_best_runtimes = gather_best_best_runtimes(program_names, all_best_runtimes)

    all_top_speeds = [c.top_speeds for c in intra_compilers.values()]
    best_top_speeds = gather_best_top_speeds(program_names, all_top_speeds)

    inter_compilers = {
        c:InterCompiler(intra_compiler,
                        program_names,
                        best_best_runtimes,
                        best_top_speeds)
        for c, intra_compiler in intra_compilers.items()
    }
    return inter_compilers

def gather_compiler_names():
    names = []
    for c in compilers:
        canonical_name = c.name[:-2]
        if not canonical_name in names:
            names.append(canonical_name)
    return names

def report(compiler_names, program_names, intra_compilers, inter_compilers):
    for c in compiler_names:
        print(f'Compiler {c}:')
        intra = intra_compilers[c]
        inter = inter_compilers[c]
        scalar = c + '_s'
        vector = c + '_v'
        for p in program_names:
            s_s = statistics.mean(intra.slowdowns[scalar][p])
            si_s = intra.stabilities[scalar][p]
            s_v = statistics.mean(intra.slowdowns[vector][p])
            si_v = intra.stabilities[vector][p]
            vo = statistics.mean(intra.vos[p])
            svo = intra.svos[p]
            ph = statistics.mean(inter.phs[p])
            sph = inter.sphs[p]
            print(f'{p} {s_s:.2f} {si_s:.2f} {s_v:.2f} {si_v:.2f} {vo:.2f} {svo:.2f} {ph:.2f} {sph:.2f}')

if __name__ == '__main__':
    raw_data = gather_raw_data()
    compiler_names = gather_compiler_names()
    program_names = gather_program_names()
    runtimes = gather_runtimes(raw_data, compiler_names, program_names)

    threshold = 0.15  # hardcoded
    intra_compilers = gather_intra_compilers(compiler_names,
                                             program_names,
                                             runtimes,
                                             threshold)
    inter_compilers = gather_inter_compilers(intra_compilers,
                                             program_names)

    report(compiler_names, program_names, intra_compilers, inter_compilers)
# def gather_for_compiler(compiler_name, table, program_names, runtime_map, speedups, stability_report, vector_opportunity, top_speed):
#     scalar = compiler_name + '_s'
#     vector = compiler_name + '_v'
#     full_compiler_names = [scalar, vector]

#     for c in full_compiler_names:
#         runtime_map[c] = {}
#         for executable_name, _ in executables:
#             # The executable_name should look like 'some_prefix_here_p01_v02_c'
#             p = executable_name.split('_')[-3]
#             if p not in program_names:
#                 program_names.append(p)
#             if p not in runtime_map[c]:
#                 runtime_map[c][p] = []
#             runtime_map[c][p].append(get_runtime(c, executable_name, table))

#     agg_report = {}
#     threshold = 0.15
#     for c in full_compiler_names:
#         agg_report[c] = {}
#         speedups[c] = {}
#         stability_report[c] = {}
#         for p in program_names:
#             runtimes = runtime_map[c][p]
#             agg_report[c][p] = get_aggregate(runtimes)
#             base = agg_report[c][p].min
#             speedups[c][p] = get_speedup(runtimes, base)
#             stability_report[c][p] = get_stability_index(runtimes,
#                                                          base,
#                                                          threshold)

#     for p in program_names:
#         vector_opportunity[p] = agg_report[scalar][p].min / agg_report[vector][p].min
#         top_speed[p] = min(agg_report[scalar][p].min, agg_report[vector][p].min)

# def report_for_compiler(compiler_name, program_names, speedups, stability_report, vector_opportunity, peer_headroom):
#     scalar = compiler_name + '_s'
#     vector = compiler_name + '_v'

#     rows = []
#     for p in program_names:
#         row = [
#             f'&{p}',
#             f'{speedups[scalar][p]:.2f}',
#             f'{stability_report[scalar][p]:.2f}',
#             f'{speedups[vector][p]:.2f}',
#             f'{stability_report[vector][p]:.2f}',
#             f'{vector_opportunity[p]:.2f}',
#             f'{peer_headroom[p]:.2f}',
#         ]
#         rows.append(row)
#     format_for_latex(compiler_name, rows)

# if __name__ == '__main__':
#     parser = argparse.ArgumentParser()
#     parser.add_argument('--build_root_dir', required=True)
#     args = parser.parse_args()
#     metrics = parse_metrics(args)

#     table = {}
#     compiler_names = [c.name for c in compilers]
#     for compiler_name in compiler_names:
#         table[compiler_name] = {}
#         for attribute_name in Metrics.get_attribute_names():
#             table[compiler_name][attribute_name] = {}
#             for executable_name, _ in executables:
#                 metric = metrics[compiler_name][executable_name]
#                 formatter = getattr(metric, f'format_{attribute_name}')
#                 table[compiler_name][attribute_name][executable_name] = formatter()
#     compilers = ['pgi', 'clang', 'gcc', 'icc']
#     # compilers = ['pgi_s', 'pgi_v', 'clang_s', 'clang_v', 'gcc_s', 'gcc_v', 'icc_s', 'icc_v']

#     program_names = []
#     speedups = {}
#     stability_report = {}
#     vector_opportunities = {}
#     top_speeds = {}
#     runtime_map = {}
#     for c in compilers:
#         top_speeds[c] = {}
#         svos[c] = {} # stabilized vector opportunities
#         gather_for_compiler(c, table, program_names, runtime_map, speedups, stability_report, vector_opporunities, svos[c], top_speeds[c])

#     ##########################
#     # peer headroom
#     #########################
#     runtime_prods = {}
#     for c in compiler_names:
#         scalar = c + '_s'
#         vector = c + '_v'
#         runtime_prods[c] = {}
#         for p in program_names:
#             runtimes_s = runtime_map[scalar][p]
#             runtimes_v = runtime_map[vector][p]

#             runtime_prods[c][p] = 1.0
#             for s, v in zip(runtimes_s, runtimes_v):
#                 runtime_prods[c][p] *= min(s, v)

#     best_prod = {}
#     for p in program_names:
#         best_prod[p] = min([runtime_prods[c][p] for c in compiler_names])
#     peer_headrooms = {}
#     for c in compiler_names:
#         peer_headrooms[p] = {}
#         for p in program_names:
#             peer_headrooms[c][p] = best_prod[p] / runtime_prods[c][p]


#     top_top_speed = {}
#     for p in program_names:
#         top_top_speed[p] = min([top_speeds[c][p] for c in compilers])
#     sphs = {} # stabilized peer headrooms
#     for c in compilers:
#         peer_headrooms[c] = {}
#         sphs[c] = {}
#         for p in program_names:

#             sphs[c][p] = top_top_speed[p] / top_speeds[c][p]

#     for c in compilers:
#         report_for_compiler(c, program_names, speedups, stability_report, vector_opportunities, svos[c], peer_headroom[c])

    
