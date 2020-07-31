compilers = [
    'gcc',
    'icc',
    'pgi',
    'clang',
]

base_command = {
    'pgi': ['pgcc', '-Minfo=vect', '-fast'],
    'gcc': ['gcc', '-march=native', '-Ofast', '-fopt-info-vec'],
    'icc': ['icc', '-xCORE-AVX512', '-qopt-zmm-usage=high', '-Ofast', '-qopt-report-file=stderr', '-qopt-report-phase=vec'],
    'clang': ['clang', '-march=native', '-Ofast', '-Rpass=loop-vectorize']
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
