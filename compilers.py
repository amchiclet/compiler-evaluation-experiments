compilers = [
    'gcc',
    'icc',
    'pgi',
    'clang',
]

base_command = {
    'pgi': ['pgcc', '-fast'],
    'gcc': ['gcc', '-march=native', '-Ofast'],
    'icc': ['icc', '-xCORE-AVX512', '-qopt-zmm-usage=high', '-Ofast'],
    'clang': ['clang', '-march=native', '-Ofast']
}

noopt_flags = {
    'pgi': ['-Mnovect'],
    'gcc': ['-fno-tree-vectorize'],
    'icc': ['-no-vec'],
    'clang': ['-fno-vectorize'],
}

novec_flags = {
    'pgi': ['-Mnovect'],
    'gcc': ['-fno-tree-vectorize'],
    'icc': ['-no-vec'],
    'clang': ['-fno-vectorize'],
}

nopredict_flags = {
    'pgi': ['-Mvect=nosizelimit'],
    'gcc': ['-fvect-cost-model=unlimited'],
    'icc': ['-vec-threshold0'],
    'clang': ['-mllvm', '-force-vector-width=16'],
}

report_flags = {
    'pgi': ['-Minfo=vect'],
    'gcc': ['-fopt-info-vec'],
    'icc': ['-qopt-report-file=stderr', '-qopt-report-phase=vec'],
    'clang': ['-Rpass=loop-vectorize'],
}

math_lib = {
    'pgi': ['-lm'],
    'gcc': ['-lm'],
    'icc': ['-lm'],
    'clang': ['-lm'],
}
