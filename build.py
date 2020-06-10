from compilers import base_command, novec_flag

def build_commands(compiler, mode, test):
    command = base_command[compiler]
    if mode == 'novec':
        command.append(novec_flag[compiler])

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
