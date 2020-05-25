import os
import os.path
from compilers import compilers
from tests import tests
from tabulate import tabulate
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

def full_compiler_name(compiler, is_vector_mode):
    return compiler + ('_v' if is_vector_mode else '_s')

def mode_name(is_vector_mode):
    return 'vec' if is_vector_mode else 'novec'

def runtime_path(compiler, test, is_vector_mode):
    return f'{test}.{compiler}.{mode_name(is_vector_mode)}.runtimes'

def parse_metrics():
    metrics = {}
    for compiler in compilers:
        for is_vector_mode in [True, False]:
            key = full_compiler_name(compiler, is_vector_mode)
            metrics[key] = {}
            for test in tests:
                metric = Metrics()
                metric.parse_runtimes(runtime_path(compiler, test, is_vector_mode))
                metrics[key][test] = metric
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
    print(f'\\multicolumn{{6}}{{| c |}}{{{compiler_name}}} \\\\')
    print('\\hline')
    for row in rows:
        print(' & '.join(row) + ' \\\\')
    
def report_for_compiler(compiler, table):
    report = {}
    program_names = []
    is_vector_mode = True
    vector = full_compiler_name(compiler, is_vector_mode)
    scalar = full_compiler_name(compiler, not is_vector_mode)
    for c in [vector, scalar]:
        report[c] = {}
        for t in tests:
            # The executable_name should look like 'some_prefix.mutation_number.c'
            p = ''.join(t.split('.')[0:-2])
            if p not in program_names:
                program_names.append(p)
            if p not in report[c]:
                report[c][p] = []
            report[c][p].append(get_runtime(c, t, table))

    agg_report = {}
    speedups = {}
    stability_report = {}
    threshold = 0.15
    for c in [vector, scalar]:
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

    vector_opportunity = {}
    for p in program_names:
        is_vector_mode = True
        vector_opportunity[p] = agg_report[scalar][p].min / agg_report[vector][p].min

    # rows = [['program'] + full_compiler_names]
    # header = ['program', 'avg speedup', 'scalar stability', 'vector stability']
    rows = []
    for p in program_names:
        row = [
            p,
            f'{speedups[scalar][p]:.2f}',
            f'{stability_report[scalar][p]:.2f}',
            f'{speedups[vector][p]:.2f}',
            f'{stability_report[vector][p]:.2f}',
            f'{vector_opportunity[p]:.2f}'
        ]
        rows.append(row)
    print(f'==== {compiler} ====')
    print(tabulate(rows,
                   headers=[
                       'Program name',
                       'Avg speedup (scalar)',
                       'Stability (scalar)',
                       'Avg speedup (vector)',
                       'Stability (vector)',
                       'Avg scalar/vector']))
    print()

if __name__ == '__main__':
    metrics = parse_metrics()
    table = {}
 
    for compiler in compilers:
        for is_vector_mode in [True, False]:
            compiler_name = full_compiler_name(compiler, is_vector_mode)
            table[compiler_name] = {}
            for attribute_name in Metrics.get_attribute_names():
                table[compiler_name][attribute_name] = {}
                for test in tests:
                    metric = metrics[compiler_name][test]
                    formatter = getattr(metric, f'format_{attribute_name}')
                    table[compiler_name][attribute_name][test] = formatter()

    for c in compilers:
        report_for_compiler(c, table)

    
