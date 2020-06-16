import argparse
from numpy import median
from scipy import stats
from build import forall_programs, PathBuilder

from patterns import patterns

# parser = argparse.ArgumentParser()
# parser.add_argument('--runtimes_file', required=True, type=str)
# parser.add_argument('--compiler', required=True, type=str)
# parser.add_argument('--mode', required=True, type=str)
# parser.add_argument('--pattern', required=True, type=str)
# parser.add_argument('--program', required=True, type=str)
# args = parser.parse_args()

def format_runtimes_file(path):
    runtimes = []
    with open(path) as f:
        for line in f:
            # ignore first line
            n_iterations = int(line.split()[2])
            break
        for line in f:
            r = int(line.split()[2])
            runtimes.append(r)
    return format(runtimes)

def format(runtimes):
    return (f'count:{len(runtimes)} '
            f'mean:{stats.tmean(runtimes):.2f} '
            f'std:{stats.tstd(runtimes):.2f} '
            f'gmean:{stats.gmean(runtimes):.2f} '
            f'gstd:{stats.gstd(runtimes):.2f} '
            f'mode:{stats.mode(runtimes)[0][0]} '
            f'median:{median(runtimes)} '
            f'min:{min(runtimes)} '
            f'max:{max(runtimes)}')

def parse_mean(line):
    return float(line.split()[1].split(':')[1])

def summarize_program(compiler, mode, pattern, program, mutations):
    path_builder = PathBuilder(compiler, mode, pattern, program)
    summary_path = path_builder.program_summary_path()
    with open(summary_path, 'w') as f:
        for m in mutations:
            path_builder.mutation = m
            f.write(format_runtimes_file(path_builder.runtimes_path()))
            f.write('\n')
    print(summary_path)
