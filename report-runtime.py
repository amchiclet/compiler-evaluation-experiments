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

def report_for_compiler_group(compiler_names, table):
    header = ['program']
    for c in compiler_names:
        header.append(c + '_s')
        header.append(c + '_v')
        header.append('speed up')
    print(','.join(header))
    for executable_name, _ in executables:
        row = [executable_name]
        for c in compiler_names:
            compiler_s = c + '_s'
            value_s = 'N/A'
            runtime_s = None
            if compiler_s in table and \
               executable_name in table[compiler_s]['runtime']:
                value_s = table[compiler_s]['runtime'][executable_name]
                runtime_s = float(value_s.split()[0])

            compiler_v = c + '_v'
            value_v = 'N/A'
            runtime_v = None
            speed_up = 'N/A'
            if compiler_v in table and \
               executable_name in table[compiler_v]['runtime']:
                value_v = table[compiler_v]['runtime'][executable_name]
                runtime_v = float(value_v.split()[0])
                if runtime_s is not None:
                    speed_up = str(runtime_s / runtime_v)

            row.append(value_s)
            row.append(value_v)
            row.append(speed_up)

        print(','.join(row))

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
    report_for_compiler_group(compilers, table)

    
