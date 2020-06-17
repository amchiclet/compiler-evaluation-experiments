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
    # return format_runtimes(runtimes)
    return Summary().init(runtimes).pprint()

class Summary:
    def __init__(self, count=None, mean=None, std=None, gmean=None, gstd=None,
                 mode=None, median=None, min_val=None, max_val=None):
        self.count = count
        self.mean = mean
        self.std = std
        self.gmean = gmean
        self.gstd = gstd
        self.mode = mode
        self.median = median
        self.min_val = min_val
        self.max_val = max_val
    def parse(self, path):
        runtimes = []
        with open(path) as f:
            for line in f:
                # ignore first line
                n_iterations = int(line.split()[2])
                break
            for line in f:
                r = int(line.split()[2])
                runtimes.append(r)
        self.init(runtimes)
    def init(self, runtimes):
        self.count = len(runtimes)
        self.mean = stats.tmean(runtimes)
        self.std = stats.tstd(runtimes)
        self.gmean = stats.gmean(runtimes)
        self.gstd = stats.gstd(runtimes)
        self.mode = stats.mode(runtimes)[0][0]
        self.median = median(runtimes)
        self.min_val = min(runtimes)
        self.max_val = max(runtimes)
    def pprint(self):
        return (f'count:{self.count} '
                f'mean:{self.mean:.2f} '
                f'std:{self.std:.2f} '
                f'gmean:{self.gmean:.2f} '
                f'gstd:{self.gstd:.2f} '
                f'mode:{self.mode} '
                f'median:{self.median} '
                f'min:{self.min_val} '
                f'max:{self.max_val}')
    def merge_min(self, other):
        self.count = min(self.count, other.count)
        self.mean = min(self.mean, other.mean)
        self.std = min(self.std, other.std)
        self.gmean = min(self.gmean, other.gmean)
        self.gstd = min(self.gstd, other.gstd)
        self.mode = min(self.mode, other.mode)
        self.median = min(self.median, other.median)
        self.min_val = min(self.min_val, other.min_val)
        self.max_val = min(self.max_val, other.max_val)

# def format_runtimes(runtimes):
#     return (f'count:{len(runtimes)} '
#             f'mean:{stats.tmean(runtimes):.2f} '
#             f'std:{stats.tstd(runtimes):.2f} '
#             f'gmean:{stats.gmean(runtimes):.2f} '
#             f'gstd:{stats.gstd(runtimes):.2f} '
#             f'mode:{stats.mode(runtimes)[0][0]} '
#             f'median:{median(runtimes)} '
#             f'min:{min(runtimes)} '
#             f'max:{max(runtimes)}')


def parse_mean(line):
    return float(line.split()[1].split(':')[1])

def summarize_mutation(compiler, mode, pattern, program, mutation):
    path_builder = PathBuilder(compiler, mode, pattern, program, mutation)
    summary_path = path_builder.mutation_summary_path()
    with open(summary_path, 'w') as f:
        f.write(format_runtimes_file(path_builder.runtimes_path()))

def find_min_for_program(compiler, mode, pattern, program, mutations):
    assert(len(mutations) > 0)
    summaries = []
    for mutation in mutations:
        path_builder = PathBuilder(compiler, mode, pattern, program, mutation)
        runtimes_path = path_builder.runtimes_path()
        summary = Summary()
        summary.parse(runtimes_path)
        summaries.append(summary)
    min_summary = summaries[0]
    for other_summary in summaries[1:]:
        min_summary.merge_min(other_summary)
    min_path = path_builder.min_of_program_path()        
    with open(min_path, 'w') as f:
        f.write(min_summary.pprint())
