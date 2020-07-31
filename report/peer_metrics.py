from util import \
    merge_value, \
    update_dict_dict, \
    update_dict_array, \
    get_paths_for_pair, \
    format_spread_pair

def x_faster_than_y_key(x, y):
    return f'{x}>{y}'

def x_faster_than_y_pair(key):
    return key.split('>')

def get_compiler_pairs_and_pims(runtimes):
    compiler_set = set()
    grouped = {}
    for (compiler, mode, pattern, program, mutation), runtime in runtimes.items():
        if mode == 'fast':
            compiler_set.add(compiler)
            key = (pattern, program, mutation)
            update_dict_dict(grouped, key, compiler, runtime)
    compilers = list(compiler_set)

    keys_to_consider = []
    for key, compiler_runtimes in grouped.items():
        if all([compiler in compiler_runtimes for compiler in compilers]):
            keys_to_consider.append(key)

    compiler_pairs = []
    for i, c1 in enumerate(compilers[:-1]):
        for c2 in compilers[i+1:]:
            compiler_pairs.append((c1, c2))

    return compiler_pairs, keys_to_consider

def iterate_compiler_runtime_pairs(runtimes):
    compiler_pairs, pims = get_compiler_pairs_and_pims(runtimes)
    for c1, c2 in compiler_pairs:
        for pim in pims:
            k1 = (c1, 'fast', *pim)
            k2 = (c2, 'fast', *pim)
            r1 = runtimes[k1]
            r2 = runtimes[k2]
            yield (c1, r1), (c2, r2), pim
