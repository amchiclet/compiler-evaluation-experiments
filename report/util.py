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
