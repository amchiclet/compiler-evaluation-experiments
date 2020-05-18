compilers = [
    'gcc',
    'icc',
    'pgi',
    'clang',
]

base_command = {
    'pgi': ['pgcc', '-Minfo', '-fast'],
    'gcc': ['gcc', '-march=native', '-Ofast'],
    'icc': ['icc', '-xCORE-AVX512', '-qopt-zmm-usage=high', '-Ofast'],
    'clang': ['clang', '-march=native', '-Ofast']
}

novec_flag = {
    'pgi': '-Mnovect',
    'gcc': '-fno-tree-vectorize',
    'icc': '-no-vec',
    'clang': '-fno-vectorize',
}

def build_commands(compiler, mode, test):
    command = base_command[compiler]
    if mode == 'novec':
        command.append(novec_flag[compiler])

    def assembly(output):
        return command + ['-S', '-o', output, test]
    def exe(output):
        return command + ['-o', output, test]
    return assembly, exe
