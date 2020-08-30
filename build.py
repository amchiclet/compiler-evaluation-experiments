from compilers import compilers, base_command, novec_flags, nopredict_flags
import inspect
from pathlib import Path

class PathBuilder:
    build_dir = 'build'
    results_dir = 'results'
    Path(build_dir).mkdir(parents=True, exist_ok=True)
    Path(results_dir).mkdir(parents=True, exist_ok=True)

    def __init__(self, compiler=None, mode=None, pattern=None, program=None, mutation=None):
        self.compiler = compiler
        self.mode = mode
        self.pattern = pattern
        self.program = program
        self.mutation = mutation

    def compiler_str(self, compiler=None):
        return compiler if compiler else (self.compiler if self.compiler else '')
    def mode_str(self, mode=None):
        return mode if mode else (self.mode if self.mode else '')
    def pattern_str(self, pattern=None):
        return pattern if pattern else (self.pattern if self.pattern else '')
    def program_str(self, program=None):
        return program if program else (self.program if self.program else '')
    def mutation_str(self, mutation=None):
        return mutation if mutation else (self.mutation if self.mutation else '')
    def prefix(self, compiler=None, mode=None, pattern=None, program=None, mutation=None):
        return '.'.join(filter(lambda i: len(i) > 0,
                               [ self.source_part(pattern, program, mutation),
                                 self.compiler_part(compiler, mode)
                               ]))
    def build_prefix(self):
        return f'{self.build_dir}/{self.prefix()}'
    def results_prefix(self):
        return f'{self.results_dir}/{self.prefix()}'
    def compiler_part(self, compiler=None, mode=None):
        return '.'.join(filter(lambda i: len(i) > 0,
                               [ self.compiler_str(compiler),
                                 self.mode_str(mode)
                               ]))
    def source_part(self, pattern=None, program=None, mutation=None):
        return '.'.join(filter(lambda i: len(i) > 0,
                               [ self.pattern_str(pattern),
                                 self.program_str(program),
                                 self.mutation_str(mutation),
                               ]))

    def clone(self, compiler=None, mode=None, pattern=None, program=None, mutation=None):
        pb = PathBuilder(self.compiler, self.mode, self.pattern, self.program, self.mutation)
        if compiler:
            pb.compiler = compiler
        if mode:
            pb.mode = mode
        if pattern:
            pb.pattern = pattern
        if program:
            pb.program = program
        if mutation:
            pb.mutation = mutation
        return pb

    def exe_path(self):
        return f'{self.build_prefix()}.exe'

    def main_path(self):
        return f'main.c'
    def main_obj_path(self):
        return f'{self.build_prefix()}.main.o'

    def core_path(self):
        return f'{self.source_part()}.c'

    def core_obj_path(self):
        return f'{self.build_prefix()}.o'

    def wrapper_path(self):
        return f'{self.source_part()}.wrapper.c'

    def wrapper_obj_path(self):
        return f'{self.build_prefix()}.wrapper.o'

    def assembly_path(self):
        return f'{self.build_prefix()}.s'

    def runtimes_ns_path(self, mutation=None):
        return f'{self.results_prefix()}.nanosec_runtimes'

    def ns_per_iteration_path(self):
        return f'{self.results_prefix()}.nanosec_per_iteration'

    def vector_rate_path(self):
        return f'{self.results_prefix()}.vector_rate'

    def checksum_path(self):
        return f'{self.results_prefix()}.checksum'

class CommandBuilder:
    def link_objects(self, compiler, mode, objects, libs, output):
        return compiler_command_map[mode][compiler] + ['-o', output] + objects + libs
    def build_object(self, compiler, mode, source, output):
        return compiler_command_map[mode][compiler] + ['-c', '-o', output, source]
    def build_assembly(self, compiler, mode, source, output):
        return compiler_command_map[mode][compiler] + ['-S', '-o', output, source]

def create_compiler_command_map():
    m = {
        'fast':{},
        'novec':{},
        'nopredict':{}
    }
    for c in compilers:
        if c in base_command:
            fast = base_command[c]
            m['fast'][c] = fast
            if c in novec_flags:
                m['novec'][c] = fast + novec_flags[c]
            if c in nopredict_flags:
                m['nopredict'][c] = fast + nopredict_flags[c]
    return m

def iterate_modes():
    yield 'fast'
    yield 'novec'
    yield 'nopredict'

compiler_command_map = create_compiler_command_map()

def gen(f, *argv):
    if inspect.isgeneratorfunction(f):
        yield from f(*argv)
    else:
        yield f(*argv)

def iterate_compiler_vec_novec():
    for compiler in compiler_command_map['fast']:
        if compiler in compiler_command_map['novec']:
            yield compiler

def iterate_compiler_fast():
    for compiler in compiler_command_map['fast'].keys():
        yield compiler

def iterate_compiler_pair_fast():
    compilers = sorted(compiler_command_map['fast'].keys())
    for i, c1 in enumerate(compilers[:-1]):
        for c2 in compilers[i+1:]:
            yield (c1, c2)

def iterate_mutations(patterns):
    for pattern, program, mutations in iterate_programs(patterns):
        for mutation in mutations:
            yield (pattern, program, mutation)

def iterate_programs(patterns):
    for pattern, programs in patterns:
        for program, mutations in programs:
            yield (pattern, program, mutations)

def iterate_compiler_modes():
    for mode, compilers in compiler_command_map.items():
        for compiler in compilers:
            yield (compiler, mode)
