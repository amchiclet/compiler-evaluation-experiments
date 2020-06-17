import argparse
from numpy import median
from scipy import stats
from build import forall_programs, PathBuilder

from patterns import patterns
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
    return Summary().init_from_runtimes(runtimes).pprint()

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

    def parse_from_runtimes(self, path):
        runtimes = []
        with open(path) as f:
            for line in f:
                # ignore first line
                n_iterations = int(line.split()[2])
                break
            for line in f:
                r = int(line.split()[2])
                runtimes.append(r)
        return self.init_from_runtimes(runtimes)

    def init_from_runtimes(self, runtimes):
        self.count = len(runtimes)
        self.mean = stats.tmean(runtimes)
        self.std = stats.tstd(runtimes)
        self.gmean = stats.gmean(runtimes)
        self.gstd = stats.gstd(runtimes)
        self.mode = stats.mode(runtimes)[0][0]
        self.median = median(runtimes)
        self.min_val = min(runtimes)
        self.max_val = max(runtimes)
        return self

    def pprint(self):
        return (f'count:{self.count} '
                f'mean:{self.mean} '
                f'std:{self.std} '
                f'gmean:{self.gmean} '
                f'gstd:{self.gstd} '
                f'mode:{self.mode} '
                f'median:{self.median} '
                f'min:{self.min_val} '
                f'max:{self.max_val}')

    def parse_from_summary(self, path):
        with open(path) as f:
            s = f.read()
            parts = s.split()
            for part in parts:
                subparts = part.split(':')
                if subparts[0] == 'count':
                    self.count = int(subparts[1])
                elif subparts[0] == 'mean':
                    self.mean = float(subparts[1])
                elif subparts[0] == 'std':
                    self.std = float(subparts[1])
                elif subparts[0] == 'gmean':
                    self.gmean = float(subparts[1])
                elif subparts[0] == 'gstd':
                    self.gstd = float(subparts[1])
                elif subparts[0] == 'mode':
                    self.mode = int(float(subparts[1]))
                elif subparts[0] == 'median':
                    self.median = int(float(subparts[1]))
                elif subparts[0] == 'min':
                    self.min_val = int(subparts[1])
                elif subparts[0] == 'max':
                    self.max_val = int(subparts[1])
        return self

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

def parse_mean(line):
    return float(line.split()[1].split(':')[1])

def summarize_mutation(compiler, mode, pattern, program, mutation):
    path_builder = PathBuilder(compiler, mode, pattern, program, mutation)
    summary_path = path_builder.summary_path()
    with open(summary_path, 'w') as f:
        f.write(format_runtimes_file(path_builder.runtimes_path()))

def find_min_for_program(compiler, mode, pattern, program, mutations):
    assert(len(mutations) > 0)
    summaries = []
    path_builder = PathBuilder(compiler, mode, pattern, program)
    for mutation in mutations:
        runtimes_path = path_builder.runtimes_path(mutation=mutation)
        summary = Summary()
        summary.parse_from_runtimes(runtimes_path)
        summaries.append(summary)
    min_summary = summaries[0]
    for other_summary in summaries[1:]:
        min_summary.merge_min(other_summary)
    min_path = path_builder.min_path()
    with open(min_path, 'w') as f:
        f.write(min_summary.pprint())
