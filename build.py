from compilers import compilers, base_command, novec_flag, nopredict_flag

def program_str(p):
    return f'p{p:04d}'
def mutation_str(m):
    return f'm{m:04d}'
def filename(pattern, p, m):
    program = program_str(p) if isinstance(p, int) else p
    mutation = mutation_str(m) if isinstance(m, int) else m
    return f'{pattern}.{program}.{mutation}.c'

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

def forall_compilations(f, patterns):
    for mode, compilers in compiler_command_map.items():
        for compiler in compilers:
            for pattern, programs in patterns:
                for program, mutations in programs:
                    for mutation in mutations:
                        test = filename(pattern, program, mutation)
                        yield from f(compiler, mode, test)

def build_commands(compiler, mode, test):
    command = compiler_command_map[mode][compiler]
    def assembly(output):
        return command + ['-S', '-o', output, test]
    def exe(output):
        return command + ['-o', output, test]
    return assembly, exe

def get_exe_name(compiler, mode, test):
    return f'{test}.{compiler}.{mode}'

def get_measure_name(compiler, mode, test):
    return f'{get_exe_name(compiler, mode, test)}.runtimes'

def get_n_iterations_name(compiler, mode, test):
    return f'{get_exe_name(compiler, mode, test)}.n_iterations'
