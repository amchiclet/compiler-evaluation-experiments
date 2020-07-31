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

checksums_db = read_checksum_database()
for (pattern, program), checksums in checksums_db.items():
    distribution, outliers = find_outliers(checksums.vals, checksums.keys)
    if len(outliers) > 0:
        print(distribution)
        print(outliers)
