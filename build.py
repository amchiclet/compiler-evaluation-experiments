from compilers import compilers, base_command, novec_flags, nopredict_flags
import inspect

class PathBuilder:
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
        return f'{self.prefix()}.exe'

    def main_path(self):
        return f'main.c'
    def main_obj_path(self):
        return f'{self.prefix()}.main.o'

    def core_path(self):
        return f'{self.source_part()}.c'
    def core_obj_path(self):
        return f'{self.prefix()}.o'

    def wrapper_path(self):
        return f'{self.source_part()}.wrapper.c'
    def wrapper_obj_path(self):
        return f'{self.prefix()}.wrapper.o'

    def assembly_path(self):
        return f'{self.prefix()}.s'

    def runtimes_path(self, mutation=None):
        return f'{self.prefix(mutation=mutation)}.runtimes'

    def runtimes_ns_path(self, mutation=None):
        return f'{self.prefix(mutation=mutation)}.nanosec_runtimes'

    def n_iterations_path(self):
        return f'{self.prefix()}.n_iterations'

    def ns_per_iteration_path(self):
        return f'{self.prefix()}.nanosec_per_iteration'

    def vector_rate_path(self):
        return f'{self.prefix()}.vector_rate'

    def test_result_path(self):
        return f'{self.prefix()}.test_result'

    def summary_path(self, compiler=None, mode=None, pattern=None, program=None, mutation=None):
        prefix = self.prefix(compiler=compiler, mode=mode, pattern=pattern, program=program, mutation=mutation)
        return f'{prefix}.summary'

    def min_path(self, pattern=None, program=None):
        prefix = self.prefix(pattern=pattern, program=program)
        return f'{prefix}.min'

    def perf_path(self, pattern=None, program=None, mutation=None):
        prefix = self.prefix(pattern=pattern, program=program, mutation=mutation)
        return f'{prefix}.perf'

    def perf_ci_path(self, pattern=None, program=None, mutation=None):
        prefix = self.prefix(pattern=pattern, program=program, mutation=mutation)
        return f'{prefix}.perf_ci'

    # VECTORIZATION
    def vec_speedup_path(self, compiler=None, pattern=None, program=None, mutation=None):
        prefix = self.prefix(compiler=compiler, pattern=pattern, program=program, mutation=mutation)
        return f'{prefix}.vec_speedup'

    def vec_speedup_ci_path(self, compiler=None, pattern=None, program=None, mutation=None):
        prefix = self.prefix(compiler=compiler, pattern=pattern, program=program, mutation=mutation)
        return f'{prefix}.vec_speedup_ci'

    def best_vec_speedup_path(self, mutation=None):
        prefix = self.prefix(mutation=mutation)
        return f'{prefix}.best_vec_speedup'

    def normalized_vec_speedup_path(self, compiler=None, pattern=None, program=None, mutation=None):
        prefix = self.prefix(compiler=compiler, pattern=pattern, program=program, mutation=mutation)
        return f'{prefix}.normalized_vec_speedup'

    def vec_success_path(self, compiler=None, pattern=None, program=None, mutation=None):
        prefix = self.prefix(compiler=compiler, pattern=pattern, program=program, mutation=mutation)
        return f'{prefix}.vec_success'

    # PEER
    def sum_of_logs_path(self, compiler=None, mode=None, pattern=None, program=None, mutation=None):
        prefix = self.prefix(compiler=compiler, mode=mode, pattern=pattern, program=program, mutation=mutation)
        return f'{prefix}.sum_of_logs'

    def peer_fraction_path(self, c1, c2, pattern=None, program=None, mutation=None):
        prefix = self.prefix(pattern=pattern, program=program, mutation=mutation)
        return f'{prefix}.{c1}.{c2}.fraction'

    def peer_fraction_ci_path(self, c1, c2, pattern=None, program=None, mutation=None):
        prefix = self.prefix(pattern=pattern, program=program, mutation=mutation)
        return f'{prefix}.{c1}.{c2}.fraction_ci'

    def best_peer_fraction_path(self, c1, c2, pattern=None, program=None, mutation=None):
        prefix = self.prefix(pattern=pattern, program=program, mutation=mutation)
        return f'{prefix}.{c1}.{c2}.best_fraction'

    def normalized_peer_fraction_path(self, c1, c2, pattern=None, program=None, mutation=None):
        prefix = self.prefix(pattern=pattern, program=program, mutation=mutation)
        return f'{prefix}.{c1}.{c2}.normalized_fraction'

    def peer_is_faster_path(self, c1, c2, pattern=None, program=None, mutation=None):
        prefix = self.prefix(pattern=pattern, program=program, mutation=mutation)
        return f'{prefix}.{c1}.{c2}.is_faster'

    def peer_is_faster_ci_path(self, c1, c2, pattern=None, program=None, mutation=None):
        prefix = self.prefix(pattern=pattern, program=program, mutation=mutation)
        return f'{prefix}.{c1}.{c2}.is_faster_ci'

class CommandBuilder:
    def link_objects(self, compiler, mode, objects, output):
        return compiler_command_map[mode][compiler] + ['-o', output] + objects
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
