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

def format_for_latex(compiler_name, rows):
    print('\\hline')
    # print(f'\\multicolumn{{6}}{{| c |}}{{{compiler_name}}} \\\\')
    # print('\\hline')
    print(f'\\multirow{{10}}{{*}}{{{compiler_name}}}')
    for row in rows:
        print(' & '.join(row) + ' \\\\')
    
def gather_for_compiler(compiler_name, table, program_names, speedups, stability_report, vector_opportunity, top_speed):
    scalar = compiler_name + '_s'
    vector = compiler_name + '_v'
    full_compiler_names = [scalar, vector]
    report = {}
    for c in full_compiler_names:
        report[c] = {}
        for executable_name, _ in executables:
            # The executable_name should look like 'some_prefix_here_p01_v02_c'
            p = executable_name.split('_')[-3]
            if p not in program_names:
                program_names.append(p)
            if p not in report[c]:
                report[c][p] = []
            report[c][p].append(get_runtime(c, executable_name, table))

    agg_report = {}
    threshold = 0.15
    for c in full_compiler_names:
        agg_report[c] = {}
        speedups[c] = {}
        stability_report[c] = {}
        for p in program_names:
            runtimes = report[c][p]
            agg_report[c][p] = get_aggregate(runtimes)
            base = agg_report[c][p].min
            speedups[c][p] = get_speedup(runtimes, base)
            stability_report[c][p] = get_stability_index(runtimes,
                                                         base,
                                                         threshold)

    for p in program_names:
        vector_opportunity[p] = agg_report[scalar][p].min / agg_report[vector][p].min
        top_speed[p] = min(agg_report[scalar][p].min, agg_report[vector][p].min)

def report_for_compiler(compiler_name, program_names, speedups, stability_report, vector_opportunity, peer_headroom):
    scalar = compiler_name + '_s'
    vector = compiler_name + '_v'

    rows = []
    for p in program_names:
        row = [
            f'&{p}',
            f'{speedups[scalar][p]:.2f}',
            f'{stability_report[scalar][p]:.2f}',
            f'{speedups[vector][p]:.2f}',
            f'{stability_report[vector][p]:.2f}',
            f'{vector_opportunity[p]:.2f}',
            f'{peer_headroom[p]:.2f}',
        ]
        rows.append(row)
    format_for_latex(compiler_name, rows)

if __name__ == '__main__':
    parser = argparse.ArgumentParser()
    parser.add_argument('--build_root_dir', required=True)
    args = parser.parse_args()
    metrics = parse_metrics(args)

    table = {}
    compiler_names = [c.name for c in compilers]
    for compiler_name in compiler_names:
        table[compiler_name] = {}
        for attribute_name in Metrics.get_attribute_names():
            table[compiler_name][attribute_name] = {}
            for executable_name, _ in executables:
                metric = metrics[compiler_name][executable_name]
                formatter = getattr(metric, f'format_{attribute_name}')
                table[compiler_name][attribute_name][executable_name] = formatter()
    compilers = ['pgi', 'clang', 'gcc', 'icc']
    # compilers = ['pgi_s', 'pgi_v', 'clang_s', 'clang_v', 'gcc_s', 'gcc_v', 'icc_s', 'icc_v']

    program_names = []
    speedups = {}
    stability_report = {}
    vector_opportunities = {}
    top_speeds = {}
    for c in compilers:
        top_speeds[c] = {}
        vector_opportunities[c] = {}
        gather_for_compiler(c, table, program_names, speedups, stability_report, vector_opportunities[c], top_speeds[c])

    top_top_speed = {}
    for p in program_names:
        top_top_speed[p] = min([top_speeds[c][p] for c in compilers])

    peer_headroom = {}
    for c in compilers:
        peer_headroom[c] = {}
        for p in program_names:
            peer_headroom[c][p] = top_top_speed[p] / top_speeds[c][p]

    for c in compilers:
        report_for_compiler(c, program_names, speedups, stability_report, vector_opportunities[c], peer_headroom[c])

    
