from build import PathBuilder, iterate_compiler_modes, iterate_programs
from stats import find_outliers
import os
import sys

base_dir = os.getcwd()
sys.path = [base_dir] + sys.path
from patterns import patterns

def debug(d):
    for k, v in d.items():
        print(f'{k} => {v}')

class Checksums:
    def __init__(self):
        self.keys = []
        self.vals = []
    def add(self, key, val):
        self.keys.append(key)
        self.vals.append(val)

def read_checksum_database():
    database = {}
    for pattern, program, mutations in iterate_programs(patterns):
        database[(pattern, program)] = Checksums()
        for mutation in mutations:
            for compiler, mode in iterate_compiler_modes():
                key = (compiler, mode, pattern, program, mutation)
                path = PathBuilder(*key).checksum_path()
                if os.path.exists(path):
                    with open(path) as f:
                        checksum = float(f.read())
                    database[(pattern, program)].add(key, checksum)
    return database

def write_blacklist_file(blacklist, path):
    from pprint import PrettyPrinter
    with open(path, 'w') as f:
        f.write('blacklist =')
        PrettyPrinter(indent=2, stream=f).pprint(blacklist)

def format_mutation(mutation):
    return '.'.join(mutation)

checksums_db = read_checksum_database()
blacklist = []
for (pattern, program), checksums in checksums_db.items():
    distribution, outliers = find_outliers(checksums.vals, checksums.keys)
    if distribution is None:
        print(f'FAIL: {pattern} {program} (invalid floating point operation occurred)')
        blacklist.append((pattern, program))
    elif len(outliers) > 0:
        print(distribution)
        print(f'FAIL: {pattern} {program} (checksums do not match)')
        print('\n'.join([format_mutation(m) for (_, m) in outliers]))
        blacklist.append((pattern, program))
    else:
        print(f'PASS: {pattern} {program}')
blacklist_path = 'blacklist.py'
write_blacklist_file(blacklist, blacklist_path)
