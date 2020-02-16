import delegator
import os
import os.path
from config import compilers, executables, Compiler, vtune_rounds
import argparse
import xml.etree.ElementTree as ET
import shutil
import statistics
from decimal import *
import itertools

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
    runtime = Decimal(runtime_range.split()[0])
    return runtime

def get_n_stable(runtimes, base, threshold):
    n_stable = sum(((r - base) / base) < threshold for r in runtimes)
    return n_stable

def format_for_latex(compiler_name, rows):
    if len(compiler_name) <= 3:
        c = compiler_name.upper()
    else:
        c = compiler_name.title()

    print('\\hline')
    print(f'\\multirow{{{len(rows)}}}{{*}}{{{c}}}')
    for row in rows[:-1]:
        print('& ' + ' & '.join(row) + ' \\\\')
    print(f'\\cline{{2-{len(row)+1}}}')
    print('& ' + ' & '.join(rows[-1]) + ' \\\\')

def format_summary_for_latex(compiler_name, rows):
    if len(compiler_name) <= 3:
        c = compiler_name.upper()
    else:
        c = compiler_name.title()

    print('\\hline')
    for row in rows:
        print(c + ' & ' + ' & '.join(row) + ' \\\\')

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

def gather_n_stables(compiler_name, program_names, runtimes, winners, threshold):
    scalar = compiler_name + '_s'
    vector = compiler_name + '_v'

    n_stables = {}
    for c in [scalar, vector]:
        n_stables[c] = {}
        for p in program_names:
            n_stables[c][p] = get_n_stable(runtimes[c][p],
                                           winners[c][p],
                                           threshold)
    return n_stables

def gather_n_mutations(compiler_name, program_names, runtimes):
    scalar = compiler_name + '_s'
    vector = compiler_name + '_v'

    n_mutations = {}
    for c in [scalar, vector]:
        n_mutations[c] = {}
        for p in program_names:
            n_mutations[c][p] = len(runtimes[c][p])

    return n_mutations

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

def gather_global_stabilized_vector_opportunities(program_names, svos):
    return geomean(svos.values())

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

def gather_global_variance_across_mutations(best_runtimes):
    g_vam = []
    for program_name, mutations in best_runtimes.items():
        fastest_mutation = min(mutations)        
        g_vam += [(mutation - fastest_mutation) / mutation for mutation in mutations]
    return g_vam

def gather_global_n_stables(variances, threshold):
    return sum(1 for v in variances if v < threshold)

def gather_global_best_runtimes(compiler_name, program_names, runtimes):
    scalar = compiler_name + '_s'
    vector = compiler_name + '_v'

    global_best_runtimes = []
    for p in program_names:
        runtimes_s = runtimes[scalar][p]
        runtimes_v = runtimes[vector][p]
        global_best_runtimes += [min(s, v) for s, v in zip(runtimes_s, runtimes_v)]
    return global_best_runtimes

def prod(l):
    r = Decimal(1.0)
    for i in l:
        r *= i
    return r

def geomean_inner(l):
    if not type(l) is list:
        l = list(l)
    return prod(l) ** (Decimal(1.0) / len(l))

def geomean(l):
    skew = Decimal('1')
    return geomean_inner([i + skew for i in l]) - skew

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

def gather_global_best_best_runtimes(program_names, all_global_best_runtimes):
    global_best_best_runtimes = None
    min_prod = None
    for best_runtimes in all_global_best_runtimes:
        new_prod = prod(best_runtimes)
        if not min_prod or new_prod < min_prod:
            min_prod = new_prod
            global_best_best_runtimes = best_runtimes
    return global_best_best_runtimes

# def gather_peer_headrooms(program_names, best_best_runtimes, best_runtimes):
#     peer_headrooms = {}
#     for p in program_names:
#         peer_headrooms[p] = [best / me for best, me in zip(best_best_runtimes[p], best_runtimes[p])]
#     return peer_headrooms

def gather_global_peer_headroom(program_names, global_best_best_runtimes, global_best_runtimes):
    return [best / me for best, me in zip(global_best_best_runtimes, global_best_runtimes)]

def gather_global_peer_headroom_v2(peer_headrooms_v2):
    result = []
    for headrooms in peer_headrooms_v2.values():
        result += headrooms
    return result

def gather_best_top_speeds(program_names, all_top_speeds):
    best_top_speeds = {}
    for p in program_names:
        best_top_speeds[p] = None
        for top_speeds in all_top_speeds:
            if not best_top_speeds[p] or top_speeds[p] < best_top_speeds[p]:
                best_top_speeds[p] = top_speeds[p]
    return best_top_speeds

def gather_global_best_top_speeds(program_names, all_top_speeds):
    global_best_top_speeds = None
    min_prod = None
    for top_speeds in all_top_speeds:
        new_prod = prod(top_speeds.values())
        if not min_prod or new_prod < min_prod:
            min_prod = new_prod
            global_best_top_speeds = top_speeds
    return global_best_top_speeds

def gather_global_best_top_speeds_v2(program_names, all_top_speeds):
    global_best_top_speeds = None
    min_prod = None
    for top_speeds in all_top_speeds:
        new_prod = prod(top_speeds.values())
        if not min_prod or new_prod < min_prod:
            min_prod = new_prod
            global_best_top_speeds = top_speeds
    return global_best_top_speeds

def gather_best_across_compilers(program_names, all_best_runtimes):
    boc = {}
    for p in program_names:
        assert(len(all_best_runtimes) > 0)
        n_mutations = len(all_best_runtimes[0][p])

        boc[p] = []
        for i in range(n_mutations):
            mutation_across_compilers = [best_runtimes[p][i] for best_runtimes in all_best_runtimes]
            best_across_compilers = min(mutation_across_compilers)
            boc[p].append(best_across_compilers)
    return boc

def gather_peer_headrooms_v2(program_names, best_across_compilers, best_runtimes):
    peer_headrooms = {}
    for program_name in program_names:
        mines = best_runtimes[program_name]
        bests = best_across_compilers[program_name]
        peer_headrooms[program_name] = [(mine - best) / mine for best, mine in zip(bests, mines)]
    return peer_headrooms

def gather_stabilized_peer_headrooms(program_names, best_top_speeds, top_speeds):
    sphs = {}
    for p in program_names:
        sphs[p] = (top_speeds[p] - best_top_speeds[p]) / top_speeds[p]
    return sphs

def gather_global_stabilized_peer_headrooms(program_names, global_best_top_speeds, top_speeds):
    result = []
    for p in program_names:
        me = top_speeds[p]
        best = global_best_top_speeds[p]
        result.append(best / me)
    return result

class IntraCompiler:
    def __init__(self, compiler_name, program_names, runtimes, threshold):
        self.winners = gather_winners(compiler_name,
                                      program_names,
                                      runtimes)
        self.slowdowns = gather_slowdowns(compiler_name,
                                          program_names,
                                          runtimes,
                                          self.winners)
        self.n_stables = gather_n_stables(compiler_name,
                                          program_names,
                                          runtimes,
                                          self.winners,
                                          threshold)
        self.n_mutations = gather_n_mutations(compiler_name,
                                              program_names,
                                              runtimes)
        self.vos = gather_vector_opportunities(compiler_name,
                                               program_names,
                                               runtimes)
        self.svos = gather_stabilized_vector_opportunities(compiler_name,
                                                           program_names,
                                                           self.winners)
        self.gsvos = gather_global_stabilized_vector_opportunities(program_names,
                                                                   self.svos)
        self.best_runtimes = gather_best_runtimes(compiler_name,
                                                  program_names,
                                                  runtimes)
        self.global_best_runtimes = gather_global_best_runtimes(compiler_name,
                                                                program_names,
                                                                runtimes)
        self.g_vams = gather_global_variance_across_mutations(self.best_runtimes)
        self.g_n_stables = gather_global_n_stables(self.g_vams, threshold)

        self.top_speeds = gather_top_speeds(compiler_name,
                                            program_names,
                                            self.winners)

def gather_intra_compilers(compiler_names, program_names, runtimes, threshold):
    intra_compilers = {}
    for c in compiler_names:
        intra_compilers[c] = IntraCompiler(c, program_names, runtimes, threshold)
    return intra_compilers

class InterCompiler:
    def __init__(self, intra_compiler, program_names, best_best_runtimes, global_best_best_runtimes, best_top_speeds, global_best_top_speeds, all_best_runtimes):
        # self.phs = gather_peer_headrooms(program_names,
        #                                  best_best_runtimes,
        #                                  intra_compiler.best_runtimes)
        self.gph = gather_global_peer_headroom(program_names,
                                               global_best_best_runtimes,
                                               intra_compiler.global_best_runtimes)
        self.sphs =  gather_stabilized_peer_headrooms(program_names,
                                                      best_top_speeds,
                                                      intra_compiler.top_speeds)
        self.gsphs =  gather_global_stabilized_peer_headrooms(program_names,
                                                              global_best_top_speeds,
                                                              intra_compiler.top_speeds)
        self.bacs = gather_best_across_compilers(program_names, all_best_runtimes)
        self.phr_v2 = gather_peer_headrooms_v2(program_names,
                                               self.bacs,
                                               intra_compiler.best_runtimes)
        self.gph_v2 = gather_global_peer_headroom_v2(self.phr_v2)

def gather_inter_compilers(intra_compilers, program_names):
    all_best_runtimes = [c.best_runtimes for c in intra_compilers.values()]
    best_best_runtimes = gather_best_best_runtimes(program_names, all_best_runtimes)
    all_global_best_runtimes = [c.global_best_runtimes for c in intra_compilers.values()]
    global_best_best_runtimes = gather_global_best_best_runtimes(program_names, all_global_best_runtimes)

    all_top_speeds = [c.top_speeds for c in intra_compilers.values()]
    best_top_speeds = gather_best_top_speeds(program_names, all_top_speeds)
    global_best_top_speeds = gather_global_best_top_speeds(program_names, all_top_speeds)

    inter_compilers = {
        c:InterCompiler(intra_compiler,
                        program_names,
                        best_best_runtimes,
                        global_best_best_runtimes,
                        best_top_speeds,
                        global_best_top_speeds,
                        all_best_runtimes)
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

def debug(compiler_names, program_names, intra_compilers, inter_compilers):
    mean = geomean
    for c in compiler_names:
        gph = mean(inter_compilers[c].gph)
        print(f'for compiler {c}, global peer headroom is {gph:.2f}')

def format_percent(d):
    if d < Decimal('0.001'):
        return f'{d * 100:.2f}\\%'
    elif d < Decimal('0.01'):
        return f'{d * 100:.1f}\\%'
    else:
        return f'{int(d * 100)}\\%'

def report_perf(compiler_names, program_names, intra_compilers, inter_compilers):
    # header
    header_row = [
        'Compiler',
        'Variance',
        'Distribution',
        'Average peer headroom',
        'Stabilized peer headroom',
    ]

    header_row_begin = '\\begin{tabular}{| c || '
    header_row_middle = ' | '.join(['c'] * (len(header_row) - 1))
    header_row_end = ' |}'
    print(header_row_begin + header_row_middle + header_row_end)
    print('\\hline')
    print(' & '.join(header_row) + ' \\\\')
    print('\\hline')

    for c in compiler_names:
        intra = intra_compilers[c]
        inter = inter_compilers[c]
        rows = []

        # compute global
        flatten = itertools.chain.from_iterable

        # variance across mutation
        g_vam = geomean(intra.g_vams)

        # distribution across mutations
        g_dam = intra.g_n_stables / len(intra.g_vams)
    
        g_ph = geomean(inter_compilers[c].gph_v2)
        
        g_sph = geomean(inter_compilers[c].sphs.values())
        row = [format_percent(v) for v in [g_vam, g_dam, g_ph, g_sph]]
        rows.append(row)
        format_summary_for_latex(c, rows)

    print('\\hline')
    print('\\end{tabular}')

def report_vec(compiler_names, program_names, intra_compilers, inter_compilers):
    # header
    header_row = [
        'Compiler',
        'Average vectorization speedup',
        'Stabilized vectorization speedup',
    ]

    header_row_begin = '\\begin{tabular}{| c || '
    header_row_middle = ' | '.join(['c'] * (len(header_row) - 1))
    header_row_end = ' |}'
    print(header_row_begin + header_row_middle + header_row_end)
    print('\\hline')
    print(' & '.join(header_row) + ' \\\\')
    print('\\hline')

    # report non-vectorization stuff
    for c in compiler_names:
        intra = intra_compilers[c]
        inter = inter_compilers[c]
        rows = []

        # compute global
        flatten = itertools.chain.from_iterable
    
        g_vo = geomean(flatten([intra.vos[p] for p in program_names]))
        g_svo = geomean(intra.svos.values())

        row = [
            f'{g_vo:.2f}', f'{g_svo:.2f}',
        ]
        rows.append(row)
        format_summary_for_latex(c, rows)

    print('\\hline')
    print('\\end{tabular}')

def report_summary(compiler_names, program_names, intra_compilers, inter_compilers):
    report_perf(compiler_names, program_names, intra_compilers, inter_compilers)
    report_vec(compiler_names, program_names, intra_compilers, inter_compilers)
    
def report(compiler_names, program_names, intra_compilers, inter_compilers):
    # header
    header_row = [
        'Compiler',
        'Loopset',
        '$\\ident{S}_s$',
        '$\\ident{SI}_s$',
        '$\\ident{S}_v$',
        '$\\ident{SI}_v$',
        '$\\ident{VO}$',
        '$\\ident{SVO}$',
        '$\\ident{PH}$',
        '$\\ident{SPH}$',
    ]

    header_row_begin = '\\begin{tabular}{| c || '
    header_row_middle = ' | '.join(['c'] * (len(header_row) - 1))
    header_row_end = ' |}'
    print(header_row_begin + header_row_middle + header_row_end)
    print('\\hline')
    print(' & '.join(header_row) + ' \\\\')
    print('\\hline')

    # for each compiler
    for c in compiler_names:
        intra = intra_compilers[c]
        inter = inter_compilers[c]
        scalar = c + '_s'
        vector = c + '_v'
        rows = []
        for p in program_names:
            s_s = geomean(intra.slowdowns[scalar][p])
            si_s = intra.n_stables[scalar][p] / intra.n_mutations[scalar][p]
            s_v = geomean(intra.slowdowns[vector][p])
            si_v = intra.n_stables[vector][p] / intra.n_mutations[vector][p]
            vo = geomean(intra.vos[p])
            svo = intra.svos[p]
            ph = geomean(inter.phs[p])
            sph = inter.sphs[p]
            row = [p,
                   f'{s_s:.2f}', f'{int(si_s*100)}\\%',
                   f'{s_v:.2f}', f'{int(si_v*100)}\\%',
                   f'{vo:.2f}', f'{svo:.2f}',
                   f'{int(ph*100)}\\%', f'{int(sph*100)}\\%',
            ]

            # Each row won't have the compiler name
            assert(len(row) + 1 == len(header_row))
            rows.append(row)
            
        # compute global
        flatten = itertools.chain.from_iterable
        g_s_s = geomean(flatten([intra.slowdowns[scalar][p] for p in program_names]))
        n_stables_scalar = [intra.n_stables[scalar][p] for p in program_names]
        n_mutations_scalar = [intra.n_mutations[scalar][p] for p in program_names]
        g_si_s = sum(n_stables_scalar) / sum(n_mutations_scalar)
        g_s_v = geomean(flatten([intra.slowdowns[vector][p] for p in program_names]))
        n_stables_vector = [intra.n_stables[vector][p] for p in program_names]
        n_mutations_vector = [intra.n_mutations[vector][p] for p in program_names]
        g_si_v = sum(n_stables_vector) / sum(n_mutations_vector)
        g_vo = geomean(flatten([intra.vos[p] for p in program_names]))
        g_svo = geomean(intra.svos.values())
        g_ph = geomean(inter_compilers[c].gph)
        g_sph = geomean(inter_compilers[c].gsphs)

        row = ['*',
               f'{g_s_s:.2f}', f'{int(g_si_s*100)}\\%',
               f'{g_s_v:.2f}', f'{int(g_si_v*100)}\\%',
               f'{g_vo:.2f}', f'{g_svo:.2f}',
               f'{int(g_ph*100)}\\%', f'{int(g_sph*100)}\\%',
        ]
        rows.append(row)
        format_for_latex(c, rows)

    print('\\hline')
    print('\\end{tabular}')

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

    report_summary(compiler_names, program_names, intra_compilers, inter_compilers)    
