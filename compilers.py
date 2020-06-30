compilers = [
    'gcc',
    'icc',
    # 'pgi',
    # 'clang',
]

base_command = {
    'pgi': ['pgcc', '-Minfo', '-fast'],
    'gcc': ['gcc', '-march=native', '-Ofast'],
    'icc': ['icc', '-xCORE-AVX512', '-qopt-zmm-usage=high', '-Ofast'],
    'clang': ['clang', '-march=native', '-Ofast']
}

novec_flags = {
    'pgi': ['-Mnovect'],
    'gcc': ['-fno-tree-vectorize'],
    'icc': ['-no-vec'],
    'clang': ['-fno-vectorize'],
}

nopredict_flags = {
    # 'pgi': '-Mnovect',
    'gcc': ['-fno-vect-cost-model'],
    'icc': ['-vec-threshold0'],
    'clang': ['-mllvm -force-vector-width=16'],
}
