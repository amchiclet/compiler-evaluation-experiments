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

def update_dddl(d, k1, k2, k3, v):
    if k1 not in d:
        d[k1] = {}
    if k2 not in d[k1]:
        d[k1][k2] = {}
    if k3 not in d[k1][k2]:
        d[k1][k2][k3] = []
    d[k1][k2][k3].append(v)

def update_ddl(d, k1, k2, v):
    if k1 not in d:
        d[k1] = {}
    if k2 not in d[k1]:
        d[k1][k2] = []
    d[k1][k2].append(v)

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

def format_spread_pair(spread, is_fully_qualified=False):
    ((less, less_id), (greater, greater_id)) = spread
    assert(less_id[:2] == greater_id[:2])
    pattern, program = less_id[:2]
    if not is_fully_qualified:
        pattern = pattern[1]
    mutation_1 = less_id[2]
    mutation_2 = greater_id[2]
    return (f'{less:.2f} vs {greater:.2f}\n'
            f'({pattern}.{program}.[{mutation_1}|{mutation_2}])')

def format_pair_raw_single_mutation(single, is_fully_qualified=False):
    (raw_1, raw_2), (pattern, program, mutation) = single
    if not is_fully_qualified:
        pattern = pattern[1]
    return (f'{raw_1:.2f} vs {raw_2:.2f}\n'
            f'({pattern}.{program}.{mutation})')

def format_raw_single_mutation(single, is_fully_qualified=False):
    raw, (pattern, program, mutation) = single
    if not is_fully_qualified:
        pattern = pattern[1]
    return (f'{raw:.2f}\n'
            f'({pattern}.{program}.{mutation})')

class Outlier:
    def __init__(self, data=None, key=None):
        self.data = data
        self.key = key
    def merge(self, is_better, new_data, new_key):
        if self.data is None:
            self.data = new_data
            self.key = new_key
        else:
            if is_better(new_data, self.data):
                self.data = new_data
                self.key = new_key
