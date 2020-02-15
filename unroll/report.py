import delegator
import os
import os.path
import argparse
import xml.etree.ElementTree as ET
import shutil
import statistics
from decimal import *
program_name = 'unroll'
program_names = [program_name]
compiler_names = ['pgi', 'clang', 'gcc', 'icc']

def gather_runtimes_unroll_log():
    def gather_parts(line, ty):
        parts = line.split(',')
        return [
            ty(parts[1]),
            ty(parts[2]),
            ty(parts[3]),
            ty(parts[4]),
            ty(parts[5]),
            ty(parts[6]),
            ty(parts[7]),
            ty(parts[8]),
        ]

    with open('unroll.log') as f:
        # skip first line
        for line in f:
            compilers = gather_parts(line.strip(), str)
            break

        print(compilers)
        runtimes = {}
        for c in compilers:
            runtimes[c] = {}
            runtimes[c][program_name] = []

        for line in f:
            row = gather_parts(line, Decimal)
            for c, runtime in zip(compilers, row):
                runtimes[c][program_name].append(runtime)
    return runtimes

def get_stability_index(runtimes, base, threshold):
    n_stable = sum(((r - base) / base) < threshold for r in runtimes)
    return float(n_stable) / len(runtimes)


def format_for_latex(compiler_name, rows):
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
            print(new_prod)
            if not min_prod or new_prod < min_prod:
                min_prod = new_prod
                best_best_runtimes[p] = best_runtimes[p]
    return best_best_runtimes

# def gather_peer_headrooms(program_names, best_best_runtimes, best_runtimes):
#     peer_headrooms = {}
#     for p in program_names:
#         peer_headrooms[p] = [best / me for best, me in zip(best_best_runtimes[p], best_runtimes[p])]
#     return peer_headrooms

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

def gather_global_variance_across_mutations(best_runtimes):
    g_vam = []
    for program_name, mutations in best_runtimes.items():
        fastest_mutation = min(mutations)
        g_vam += [(mutation - fastest_mutation) / mutation for mutation in mutations]
    return g_vam

def gather_global_n_stables(variances, threshold):
    return sum(1 for v in variances if v < threshold)

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

def gather_peer_headrooms(program_names, best_across_compilers, best_runtimes):
    peer_headrooms = {}
    for program_name in program_names:
        mines = best_runtimes[program_name]
        bests = best_across_compilers[program_name]
        peer_headrooms[program_name] = [best / mine for best, mine in zip(bests, mines)]
    return peer_headrooms

def gather_global_peer_headroom(peer_headrooms):
    result = []
    for headrooms in peer_headrooms.values():
        result += headrooms
    return result

class InterCompiler:
    def __init__(self, intra_compiler, program_names, best_best_runtimes, best_top_speeds, all_best_runtimes):
        # self.phs = gather_peer_headrooms(program_names,
        #                                  best_best_runtimes,
        #                                  intra_compiler.best_runtimes)
        self.bacs = gather_best_across_compilers(program_names, all_best_runtimes)
        self.phs = gather_peer_headrooms(program_names,
                                         self.bacs,
                                         intra_compiler.best_runtimes)
        self.gphs = gather_global_peer_headroom(self.phs)
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
                        best_top_speeds,
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

        # variance across mutation
        g_vam = geomean(intra.g_vams)

        # distribution across mutations
        g_dam = intra.g_n_stables / len(intra.g_vams)
    
        g_ph = geomean(inter_compilers[c].gphs)
        
        g_sph = geomean(inter_compilers[c].sphs.values())

        row = [format_percent(v) for v in [g_vam, g_dam, g_ph, g_sph]]
        rows.append(row)
        format_for_latex(c, rows)

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

        assert(len(program_names) == 1)

        g_vo = geomean(intra.vos[program_names[0]])

        g_svo = geomean(intra.svos.values())

        row = [
            f'{g_vo:.2f}', f'{g_svo:.2f}',
        ]
        rows.append(row)
        format_for_latex(c, rows)

    print('\\hline')
    print('\\end{tabular}')

def report_summary(compiler_names, program_names, intra_compilers, inter_compilers):
    print('report perf')
    report_perf(compiler_names, program_names, intra_compilers, inter_compilers)
    print('report vec')
    report_vec(compiler_names, program_names, intra_compilers, inter_compilers)

def report(compiler_names, program_names, intra_compilers, inter_compilers):
    mean = geomean
    # mean = statistics.mean
    # header
    header_row = [
        'Compiler',
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
            s_s = mean(intra.slowdowns[scalar][p])
            si_s = intra.stabilities[scalar][p]
            s_v = mean(intra.slowdowns[vector][p])
            si_v = intra.stabilities[vector][p]
            vo = mean(intra.vos[p])
            svo = intra.svos[p]
            ph = mean(inter.phs[p])
            sph = inter.sphs[p]
            row = [
                f'{s_s:.2f}', f'{int(si_s*100)}\\%',
                f'{s_v:.2f}', f'{int(si_v*100)}\\%',
                f'{vo:.2f}', f'{svo:.2f}',
                f'{int(ph*100)}\\%', f'{int(sph*100)}\\%',
            ]

            # Each row won't have the compiler name
            assert(len(row) + 1 == len(header_row))
            rows.append(row)
        format_for_latex(c, rows)

    print('\\hline')
    print('\\end{tabular}')

if __name__ == '__main__':
    # raw_data = gather_raw_data()
    # compiler_names = gather_compiler_names()
    # program_names = gather_program_names()
    runtimes = gather_runtimes_unroll_log()

    threshold = 0.15  # hardcoded
    intra_compilers = gather_intra_compilers(compiler_names,
                                             program_names,
                                             runtimes,
                                             threshold)
    inter_compilers = gather_inter_compilers(intra_compilers,
                                             program_names)

    report_summary(compiler_names, program_names, intra_compilers, inter_compilers)
    report(compiler_names, program_names, intra_compilers, inter_compilers)
    
