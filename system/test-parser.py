from parser import parse_file
program, node_id = parse_file('v2.loop')
print(program.pprint())

from abstract_ast import is_same_memory, is_comparable, get_all_access_pairs, get_accesses

grouped_accesses = {}
for access in get_accesses(program):
    array = access.var
    if array not in grouped_accesses:
        grouped_accesses[array] = [None] * len(access.indices)
    assert(len(access.indices) == len(grouped_accesses[array]))
    for dimension, index in enumerate(access.indices):
        if not grouped_accesses[array][dimension]:
            grouped_accesses[array][dimension] = []
        print(f'before {array}({dimension}): {[i.pprint() for i in grouped_accesses[array][dimension]]}')
        grouped_accesses[array][dimension].append(index)
        print(f'after {array}({dimension}): {[i.pprint() for i in grouped_accesses[array][dimension]]}')
print(grouped_accesses)
for array, all_indices in grouped_accesses.items():
    print(f'For array {array}:')
    for dimension, indices in enumerate(all_indices):
        print(f'Dimension {dimension}: {[i.pprint() for i in indices]}')
# for access1, access2 in get_all_access_pairs(program):
#     if not is_same_memory(access1, access2):
#         continue
#     if not is_comparable(access1, access2):
#         raise RuntimeError(f'Accesses are not comparable: {access1.pprint()} vs {access2.pprint()}')
#     print(access1.pprint(), access2.pprint())
#     for i1, i2 in zip(access1.indices, access2.indices):
        # print(i1.pprint(), i2.pprint())
    # get all the indices for each array
    # for each dimension, sort
    # sort each index
    # find a possible sorting
    # for each index, find out whether it's always greater than it's var or not
    # case 1: i < i1 < i2 then i1 becomes >i
    #                          i2 becomes >>i
    # case 2: 
    # case 1: i1 > i
    #   case 1.1: i2 > i
    #     case 1.1.1: i1 > i2
    # 
    
