from build import PathBuilder

def debug(d):
    for k, v in d.items():
        print(f'{k} => {v}')

def merge_value(database, key, value, merge_function):
    if key not in database:
        database[key] = value
    else:
        database[key] = merge_function(database[key], value)

def update_dict_dict(d, k1, k2, v):
    if k1 not in d:
        d[k1] = {}
    d[k1][k2] = v

def update_dict_array(d, k, v):
    if k not in d:
        d[k] = []
    d[k].append(v)

def get_paths_for_pair(stats):
    interesting_case_paths = set()
    for compiler, interesting_spreads in stats.interesting_cases.iterate():
        for spread in interesting_spreads:
            for (runtime, mutation_id) in spread.raw:
                pattern, program, mutation = mutation_id
                interesting_case_paths.add(mutation_id)
    return interesting_case_paths

def get_paths_for_single(stats):
    interesting_case_paths = set()
    for compiler, interesting_spreads in stats.interesting_cases.iterate():
        for spread in interesting_spreads:
            (runtime, mutation_id) = spread.raw
            pattern, program, mutation = mutation_id
            interesting_case_paths.add(mutation_id)
    return interesting_case_paths

def format_spread_pair(spread):
    ((less, less_id), (greater, greater_id)) = spread
    assert(less_id[:2] == greater_id[:2])
    pattern, program = less_id[:2]
    mutation_1 = less_id[2]
    mutation_2 = greater_id[2]
    return (f'{less:.2f} vs {greater:.2f}\n'
            f'({pattern}.{program}.[{mutation_1}|{mutation_2}])')

def format_pair_raw_single_mutation(single):
    (raw_1, raw_2), (pattern, program, mutation) = single
    return (f'{raw_1:.2f} vs {raw_2:.2f}\n'
            f'({pattern}.{program}.{mutation})')
