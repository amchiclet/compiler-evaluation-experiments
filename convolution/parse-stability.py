# ['|', 'Benchmark', '|', 'pgi_s', '|', 'pgi_v', '|', 'clang_s', '|', 'clang_v', '|', 'gcc_s', '|', 'gcc_v', '|', 'icc_s', '|', 'icc_v', '|']
# ['|', 'conv_i232_h_w_c_kh_kw_kc_c', '|', '292262', '|', '292439', '|', '56993', '|', '56994', '|', '114744', '|', '114748', '|', '96191', '|', '59553', '|']

def gather_parts(line, ty):
    parts = line.split()
    return [
        ty(parts[3]),
        ty(parts[5]),
        ty(parts[7]),
        ty(parts[9]),
        ty(parts[11]),
        ty(parts[13]),
        ty(parts[15]),
        ty(parts[17]),
    ]

with open('conv.log') as f:
    for line in f:
        compilers = gather_parts(line, str)
        break

    all_runtimes = {}
    for c in compilers:
        all_runtimes[c] = []

    for line in f:
        runtimes = gather_parts(line, float)
        for c, runtime in zip(compilers, runtimes):
            all_runtimes[c].append(runtime)

import statistics
speedups = {}
stability = {}
threshold = 0.15
for c in compilers:
    runtimes = all_runtimes[c]
    best = min(runtimes)
    speedup = [r / best for r in runtimes]
    n_stable = sum(((r - best) / best) < threshold for r in runtimes)
    n_stable2 = len(list(filter(lambda r: r < 1.0 + threshold, speedup)))
    print(n_stable == n_stable2)
    stability[c] = float(n_stable) / len(runtimes)
    speedups[c] = statistics.mean(speedup)

# for c in compilers:
#     print(c, speedups[c], stability[c])

# speedups = {}
base_compilers = []
for c in compilers:
    base = c[:-2]
    if base not in base_compilers:
        base_compilers.append(base)

def find_min_and_index(runtimes):
    min_i = 0
    min_r = runtimes[0]
    for i, r in enumerate(runtimes):
        if r < min_r:
            min_r = r
            min_i = i
    return (min_r, min_i)

top_top_speed = None
top_speeds = {}
vos = {}
for c in base_compilers:
    scalar = c + '_s'
    vector = c + '_v'
    assert(scalar in compilers)
    assert(vector in compilers)

    min_scalar_r, min_scalar_i = find_min_and_index(all_runtimes[scalar])
    min_vector_r, min_vector_i = find_min_and_index(all_runtimes[vector])
    vo = min_scalar_r / min_vector_r
    vos[c] = vo
    top_speed = min(min_scalar_r, min_vector_r)
    top_speeds[c] = top_speed
    if not top_top_speed or top_top_speed > top_speed:
        top_top_speed = top_speed

for c in base_compilers:
    print(f'\\hline')
    print(f'\\multicolumn{{6}}{{| c |}}{{{c}}} \\\\')
    print(f'\\hline')
    print(f'convolution & {speedups[scalar]:.2f} & {stability[scalar]:.2f} & {speedups[vector]:.2f} & {stability[vector]:.2f} & {vos[c]:.2f} & {(top_top_speed / top_speeds[c]):.2f} \\\\')
    print(f'\\hline')
    
    

