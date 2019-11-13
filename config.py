import os.path

# BUILD_DIR = 'build'

def underscorify(s):
    return s.replace('/', '_').replace('.', '_')

class Compiler:
    def __init__(self, name, cpp, extra_args = ''):
        self.name = name
        self.cpp = cpp
        # self.build_dir = os.path.join(BUILD_DIR, name)
        self.build_dir = name
        self.extra_args = extra_args

compilers = [
    # Compiler('pgi_0', 'pgcc', '-D localstatedir=no_optimization'),
    Compiler('pgi_s', 'pgcc', '-D localstatedir=no_vec'),
    Compiler('pgi_v', 'pgcc'),
    # Compiler('clang_0', 'clang', '-D localstatedir=no_optimization'),
    Compiler('clang_s', 'clang', '-D localstatedir=no_vec'),
    Compiler('clang_v', 'clang'),
    # Compiler('gcc_0', 'gcc', '-D localstatedir=no_optimization'),
    Compiler('gcc_s', 'gcc', '-D localstatedir=no_vec'),
    Compiler('gcc_v', 'gcc'),
    # Compiler('icc_0', 'icc', '-D localstatedir=no_optimization'),
    Compiler('icc_s', 'icc', '-D localstatedir=no_vec'),
    Compiler('icc_v', 'icc'),
]

report_order = [
    'pgi_0', 'pgi_s', 'pgi_v',
    'clang_0', 'clang_s', 'clang_v',
    'gcc_0', 'gcc_s', 'gcc_v',
    'icc_0', 'icc_s', 'icc_v',
]

vtune_rounds = 5

import benchmarks
executables = benchmarks.executables
