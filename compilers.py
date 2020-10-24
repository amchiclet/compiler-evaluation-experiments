compilers = [
    # 'gcc-5',
    # 'gcc-7',
    'icc',
    # 'pgi',
    # 'clang-6',
    # 'clang-10',
]

base_command = {
    'pgi': ['pgcc', '-fast'],
    'gcc-5': ['gcc', '-march=native', '-Ofast'],
    'gcc-7': ['gcc', '-march=native', '-Ofast'],
    'icc': ['icc', '-xCORE-AVX512', '-qopt-zmm-usage=high', '-Ofast'],
    'clang-6': ['clang-6.0', '-march=native', '-Ofast'],
    'clang-10': ['clang-10', '-march=native', '-Ofast', '-mprefer-vector-width=512']
}

noopt_flags = {
    'pgi': ['-Mnovect'],
    'gcc-5': ['-fno-tree-vectorize'],
    'gcc-7': ['-fno-tree-vectorize'],
    'icc': ['-no-vec'],
    'clang-6': ['-fno-vectorize'],
    'clang-10': ['-fno-vectorize'],
}

novec_flags = {
    'pgi': ['-Mnovect'],
    'gcc-5': ['-fno-tree-vectorize'],
    'gcc-7': ['-fno-tree-vectorize'],
    'icc': ['-no-vec'],
    'clang-6': ['-fno-vectorize'],
    'clang-10': ['-fno-vectorize'],
}

nopredict_flags = {
    'pgi': ['-Mvect=nosizelimit'],
    'gcc-5': ['-fvect-cost-model=unlimited'],
    'gcc-7': ['-fvect-cost-model=unlimited'],
    'icc': ['-vec-threshold0'],
    'clang-6': ['-mllvm', '-force-vector-width=16'],
    'clang-10': ['-mllvm', '-force-vector-width=16'],
}

report_flags = {
    'pgi': ['-Minfo=vect'],
    'gcc': ['-fopt-info-vec'],
    'icc': ['-qopt-report-file=stderr', '-qopt-report-phase=vec'],
    'clang': ['-Rpass=loop-vectorize'],
}

math_lib = {
    'pgi': ['-lm'],
    'gcc-5': ['-lm'],
    'gcc-7': ['-lm'],
    'icc': ['-lm'],
    'clang-6': ['-lm'],
    'clang-10': ['-lm'],
}
