from compilers import compilers, base_command, novec_flag, nopredict_flag
import inspect

def program_str(p):
    return f'p{p:04d}'
def mutation_str(m):
    return f'm{m:04d}'
def filename(pattern, p, m):
    program = program_str(p) if isinstance(p, int) else p
    mutation = mutation_str(m) if isinstance(m, int) else m
    return f'{pattern}.{program}.{mutation}.c'

class PathBuilder:
    def __init__(self, compiler=None, mode=None, pattern=None, program=None, mutation=None):
        self.compiler = compiler
        self.mode = mode
        self.pattern = pattern
        self.program = program
        self.mutation = mutation

    def clone(self):
        return PathBuilder(self.compiler, self.mode, self.pattern, self.program, self.mutation)

    def program_prefix(self):
        return f'{self.pattern}.{self.program}'

    def mutation_prefix(self):
        return f'{self.program_prefix()}.{self.mutation}'

    def source_code_path(self):
        return f'{self.mutation_prefix()}.c'

    def full_prefix(self):
        return f'{self.mutation_prefix()}.{self.compiler}.{self.mode}'

    # def exe_path(self):
    #     return f'{self.source_code_path()}.{self.compiler}.{self.mode}'

    def assembly_path(self):
        return f'{self.full_prefix()}.s'

    def runtimes_path(self):
        return f'{self.full_prefix()}.runtimes'

    def n_iterations_path(self):
        return f'{self.full_prefix()}.n_iterations'

    def test_result_path(self):
        return f'{self.full_prefix()}.test_result'

    def mutation_summary_path(self):
        return f'{self.full_prefix()}.summary'

    def min_of_program_path(self):
        return f'{self.program_prefix()}.{self.compiler}.{self.mode}.min'

    def program_summary_path(self):
        return f'{self.program_prefix()}.{self.compiler}.{self.mode}.summary'

    def program_stability_path(self):
        return f'{self.program_prefix()}.{self.compiler}.{self.mode}.stability'

class CommandBuilder:
    def __init__(self, path_builder):
        self.path_builder = path_builder

    def build_exe(self):
        test = self.path_builder.source_code_path()
        output = self.path_builder.full_prefix()
        mode = self.path_builder.mode
        compiler = self.path_builder.compiler
        return compiler_command_map[mode][compiler] + ['-o', output, test]

    def build_assembly(self):
        test = self.path_builder.source_code_path()
        output = self.path_builder.assembly_path()
        mode = self.path_builder.mode
        compiler = self.path_builder.compiler
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

def forall_patterns(patterns, f):
    for mode, compilers in compiler_command_map.items():
        for compiler in compilers:
            for pattern, programs in patterns:
                if inspect.isgeneratorfunction(f):
                    yield from f(compiler, mode, pattern, programs)
                else:
                    yield f(compiler, mode, pattern, programs)

def forall_programs(patterns, f):
    def wrap(compiler, mode, pattern, programs):
        for program, mutations in programs:
            if inspect.isgeneratorfunction(f):
                yield from f(compiler, mode, pattern, program, mutations)
            else:
                yield f(compiler, mode, pattern, program, mutations)
    yield from forall_patterns(patterns, wrap)

def forall_mutations(patterns, f):
    def wrap(compiler, mode, pattern, program, mutations):
        for mutation in mutations:
            if inspect.isgeneratorfunction(f):
                yield from f(compiler, mode, pattern, program, mutation)
            else:
                yield f(compiler, mode, pattern, program, mutation)
    yield from forall_programs(patterns, wrap)
