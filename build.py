from compilers import compilers, base_command, novec_flag, nopredict_flag
import inspect

# def program_str(p):
#     return f'p{p:04d}'
# def mutation_str(m):
#     return f'm{m:04d}'
# def filename(pattern, p, m):
#     program = program_str(p) if isinstance(p, int) else p
#     mutation = mutation_str(m) if isinstance(m, int) else m
#     return f'{pattern}.{program}.{mutation}.c'

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

    def source_code_path(self):
        return f'{self.source_part()}.c'

    def assembly_path(self):
        return f'{self.prefix()}.s'

    def runtimes_path(self, mutation=None):
        return f'{self.prefix(mutation=mutation)}.runtimes'

    def n_iterations_path(self):
        return f'{self.prefix()}.n_iterations'

    def test_result_path(self):
        return f'{self.prefix()}.test_result'

    def summary_path(self, pattern=None, program=None, mutation=None):
        prefix = self.prefix(pattern=pattern, program=program, mutation=mutation)
        return f'{prefix}.summary'

    def min_path(self, pattern=None, program=None):
        prefix = self.prefix(pattern=pattern, program=program)
        return f'{prefix}.min'

    def perf_stability_path(self, pattern=None, program=None, mutation=None):
        prefix = self.prefix(pattern=pattern, program=program, mutation=mutation)
        return f'{prefix}.perf_stability'

class CommandBuilder:
    def build_exe(self, compiler, mode, test, output):
        return compiler_command_map[mode][compiler] + ['-o', output, test]

    def build_assembly(self, compiler, mode, test, output):
        return compiler_command_map[mode][compiler] + ['-S', '-o', output, test]

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
            if c in novec_flag:
                m['novec'][c] = fast + [novec_flag[c]]
            if c in nopredict_flag:
                m['nopredict'][c] = fast + [nopredict_flag[c]]
    return m

compiler_command_map = create_compiler_command_map()

def gen(f, *argv):
    if inspect.isgeneratorfunction(f):
        yield from f(*argv)
    else:
        yield f(*argv)

def iterate_mutations(patterns):
    for pattern, programs in patterns:
        for program, mutations in programs:
            for mutation in mutations:
                yield (pattern, program, mutation)

def forall_modes(patterns, f):
    for mode, compilers in compiler_command_map.items():
        for compiler in compilers:
            yield from gen(f, compiler, mode, patterns)

def forall_patterns(patterns, f):
    def wrap(compiler, mode, patterns):
        for pattern, programs in patterns:
            yield from gen(f, compiler, mode, pattern, programs)
    yield from forall_modes(patterns, wrap)

def forall_programs(patterns, f):
    def wrap(compiler, mode, pattern, programs):
        for program, mutations in programs:
            yield from gen(f, compiler, mode, pattern, program, mutations)
    yield from forall_patterns(patterns, wrap)

def forall_mutations(patterns, f):
    def wrap(compiler, mode, pattern, program, mutations):
        for mutation in mutations:
            yield from gen(f, compiler, mode, pattern, program, mutation)
    yield from forall_programs(patterns, wrap)
