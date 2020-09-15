from report.generate import get_ok_patterns, read_runtimes_database_multi_experiment, limit_patterns, read_runtimes_database, get_popular_pattern_structure
from report.runtime import add_plot_normalized_runtimes, get_normalized_runtimes
from report.peer_rank import get_rankings
from report.peer_metrics import get_compiler_pairs, x_approximates_y_key, x_faster_than_y_key
from report.util import update_dict_array
from compilers import compilers
from plot import display_plot, save_plot, clear_plot, add_plot
from random import shuffle, choices
from stats import geometric_mean, arithmetic_mean
import os
from pathlib import Path
from tqdm import tqdm
from multiprocessing import Pool

base_dir = os.path.abspath(os.getcwd())

fig_dir = '/home/phaosaw2/big-unroll-results'
Path(fig_dir).mkdir(parents=True, exist_ok=True)

def get_data(base_dir):
    patterns = get_ok_patterns(base_dir)
    runtimes = read_runtimes_database(base_dir, patterns)
    normalized, _ = get_normalized_runtimes(runtimes)
    rankings_map = get_rankings(runtimes)
    return patterns, normalized, rankings_map

# base_dir1 = '/home/phaosaw2/compiler-test-generator/unroll.200.2.4/code'
# base_dir2 = '/home/phaosaw2/compiler-test-generator/repeat-unroll.200.2.4/code'

def merge_data(patternss, normalizeds, rankings_maps):
    merged_patterns = []
    merged_normalized = {}
    merged_rankings_map = {}
    count = 0
    for patterns, normalized, rankings_map in zip(patternss, normalizeds, rankings_maps):
        rename = {}
        for p, instances in patterns:
            rename[p] = f'p{count:03d}'
            count += 1
            merged_patterns.append((rename[p], instances))
        for (c, p, i, m), r in normalized.items():
            merged_normalized[(c, rename[p], i, m)] = r
        for (pair, (p, i, m)), r in rankings_map.items():
            merged_rankings_map[(pair, (rename[p], i, m))] = r
    return merged_patterns, merged_normalized, merged_rankings_map

patternss = []
normalizeds = []
rankings_maps = []

base_dirs = [f'big-unroll.200.2.4/r{r:02d}/code' for r in range(10)]
for base_dir in base_dirs:
    patterns, normalized, rankings_map = get_data(base_dir)
    patternss.append(patterns)
    normalizeds.append(normalized)
    rankings_maps.append(rankings_map)
all_patterns, normalized, rankings_map = merge_data(patternss, normalizeds, rankings_maps)
n_instances, n_mutations = get_popular_pattern_structure(all_patterns)
all_patterns = limit_patterns(all_patterns, n_instances, n_mutations)
print(f'total patterns = {len(all_patterns)}')

print(n_instances, n_mutations, len(all_patterns))

def plot_one(all_patterns, compilers, repeat, n_patterns, n_parts):
    shuffle(all_patterns)
    n_all_patterns = n_patterns * n_parts
    sub_patterns = all_patterns[:n_all_patterns]

    assert(n_all_patterns <= len(sub_patterns))
    for c in compilers:
        for part in range(0, n_all_patterns, n_patterns):
            patterns = sub_patterns[part:part+n_patterns]

            print(f'runtime repeat({repeat}) compiler({c}) n_patterns({n_patterns})({part}-{part+n_patterns})')
            # runtime stability
            stat = []
            for _ in range(10000):
                sampled = choices(patterns, k=len(patterns))
                data = []
                for p, instances in sampled:
                    for i, mutations in instances:
                        for m in mutations:
                            data.append(normalized[(c, p, i, m)])
                stat.append(geometric_mean(data))
            add_plot(stat, label=f'{part}-{part+n_patterns}', min_val=0, max_val=1)
        save_plot(f'/{fig_dir}/unroll.runtime.{c}.{n_patterns}.{repeat}.png', f'{c} runtime stability')
        clear_plot()

    for (c1, c2) in get_compiler_pairs(compilers):
        keys = [x_approximates_y_key(c1, c2),
                x_faster_than_y_key(c1, c2),
                x_faster_than_y_key(c2, c1)]
        for pair in keys:
            for part in range(0, n_all_patterns, n_patterns):
                patterns = sub_patterns[part:part+n_patterns]

                print(f'peer repeat({repeat}) compiler({pair}) n_patterns({n_patterns})({part}-{part+n_patterns})')

                stat = []
                for _ in range(10000):
                    sampled = choices(patterns, k=len(patterns))
                    data = []
                    for p, instances in sampled:
                        for i, mutations in instances:
                            for m in mutations:
                                data.append(rankings_map[(pair, (p, i, m))])
                    avg = arithmetic_mean(data)
                    stat.append(avg)
                add_plot(stat, label=f'{part}-{part+n_patterns}', min_val=0, max_val=1)
            pair_name = pair.replace('>', '_gt_').replace('~', '_eq_')
            save_plot(f'/{fig_dir}/unroll.peer_rank.{pair_name}.{n_patterns:03d}.{repeat:02d}.png',
                      f'{pair} peer rank')
            clear_plot()


argss = []
max_patterns = 1600
for repeat in range(5):
    for n_patterns in [10, 20, 40, 80, 160]:
        argss.append((all_patterns, compilers, repeat, n_patterns, 10))
Pool().starmap(plot_one, argss)

# for repeat in range(5):
#     print(f'round {repeat}')
#     for n_patterns in [10, 20, 40, 80, 160, 320]:
#         shuffle(all_patterns)
#         sub_patterns = all_patterns[:300]
#         n_parts = len(sub_patterns) // n_patterns
#         n_all_patterns = n_patterns * n_parts
#         assert(n_all_patterns <= len(sub_patterns))
#         for c in compilers:
#             for part in range(0, n_all_patterns, n_patterns):
#                 patterns = sub_patterns[part:part+n_patterns]

#                 print(f'compiler({c}) n_patterns({part}-{part+n_patterns})')
#                 # runtime stability
#                 stat = []
#                 for _ in tqdm(range(10000)):
#                     sampled = choices(patterns, k=len(patterns))
#                     data = []
#                     for p, instances in sampled:
#                         for i, mutations in instances:
#                             for m in mutations:
#                                 data.append(normalized[(c, p, i, m)])
#                     stat.append(geometric_mean(data))
#                 add_plot(stat, label=f'{part}-{part+n_patterns}', min_val=0, max_val=1)
#             save_plot(f'/{fig_dir}/unroll.runtime.{c}.{n_patterns}.{repeat}.png', f'{c} runtime stability')
#             clear_plot()

#         for (c1, c2) in get_compiler_pairs(compilers):
#             keys = [x_approximates_y_key(c1, c2),
#                     x_faster_than_y_key(c1, c2),
#                     x_faster_than_y_key(c2, c1)]
#             for pair in keys:
#                 for part in range(0, n_all_patterns, n_patterns):
#                     patterns = sub_patterns[part:part+n_patterns]

#                     print(f'compiler({pair}) n_patterns({part}-{part+n_patterns})')

#                     stat = []
#                     for _ in tqdm(range(10000)):
#                         sampled = choices(patterns, k=len(patterns))
#                         data = []
#                         for p, instances in sampled:
#                             for i, mutations in instances:
#                                 for m in mutations:
#                                     data.append(rankings_map[(pair, (p, i, m))])
#                         avg = arithmetic_mean(data)
#                         if avg == 0:
#                             print(f'zero average {pair}')
#                         stat.append(avg)
#                     add_plot(stat, label=f'{part}-{part+n_patterns}', min_val=0, max_val=1)
#                 pair_name = pair.replace('>', '_gt_').replace('~', '_eq_')
#                 save_plot(f'/{fig_dir}/unroll.peer_rank.{pair_name}.{n_patterns}.{repeat}.png',
#                           f'{pair} peer rank')
#                 clear_plot()
 
                # filtered_runtimes = {}
                # for k, v in runtimes.items():
                #     if k[2] in pattern_names:
                #         filtered_runtimes[k] = v

                # print(f'compiler({c}) n_patterns({part}-{part+n_patterns})')
                # add_plot_normalized_runtimes(c, filtered_runtimes, f'patterns {part}-{part+n_patterns}')
            # save_plot(f'/{fig_dir}/unroll.{c}.{n_patterns}.{n_instances}.{repeat}.png', f'{c} runtime stability')
            # clear_plot()
