def calculate_strides(n_dimensions):
    strides = []
    prev = 1
    for d in range(n_dimensions):
        size = prev * (d+1)
        prev = size
        strides.append(size)
    strides.reverse()
    return strides

def to_permutation(n, n_dimensions):
    strides = calculate_strides(n_dimensions)
    remaining_order = list(range(n_dimensions))
    order = []
    for i in range(n_dimensions-1):
        dimension_size = strides[i+1]
        which_index = n // dimension_size
        n = n % dimension_size
        value = remaining_order[which_index]
        del remaining_order[which_index]
        order.append(value)
    order.append(remaining_order.pop())
    return order

def to_id(p):
    n_dimensions = len(p)
    remaining = list(range(n_dimensions))
    strides = calculate_strides(n_dimensions)
    result = 0
    for i in range(n_dimensions-1):
        value = remaining.index(p[i])
        del remaining[value]
        result += strides[i+1] * value
    return result

print(calculate_strides(4))
for i in range(720):
    p = to_permutation(i, 6)
    n = to_id(p)
    assert(i == n)
    print(f'id({i}) permutation({p})  back to id({to_id(p)})')
