import os
import random
from parser import parse_file

def get_patterns(root_dir):
    patterns = []
    for pattern in os.listdir(root_dir):
        full_path = os.path.join(root_dir, pattern)
        if os.path.isfile(full_path) and full_path.endswith('.loop'):
            patterns.append(pattern)
    patterns += [None] * len(patterns)
    return patterns

rel_dir = 'loops/lore'
abs_dir = os.path.abspath(rel_dir)
patterns = get_patterns(abs_dir)

max_patterns = 5
chosen = random.choices(patterns, k=max_patterns)
while chosen.count(None) == max_patterns:
    chosen = random.choices(patterns, k=max_patterns)
chosen = list(filter(lambda x: x is not None, chosen))

merged = None
node_id = 0
for rel_path in chosen:
    abs_path = os.path.join(abs_dir, rel_path)
    print('parsing', abs_path, node_id)
    program, node_id = parse_file(abs_path, node_id)
    if merged:
        merged.merge(program)
    else:
        merged = program

print(merged.pprint())
