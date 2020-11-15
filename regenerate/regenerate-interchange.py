from patterns import patterns
from parser import parse_str
from abstract_ast import get_ordered_loops, Literal
from pattern_generator import write_patterns_to_dir

print(patterns)
patterns = [( 'p000',
    [ ('i00', ['m00', 'm01', 'm02', 'm03']),
      ('i01', ['m00', 'm01', 'm02', 'm03'])]),
]

root_dir = '.'
code_dir = f'{root_dir}/code'
patterns_dir = f'{root_dir}/patterns'
logs_dir = f'{root_dir}/logs'

def read_pattern(path):
    with open(path) as f:
        return parse_str(f.read())

def read_mutation(log_path, p, i, m):
    lines = []
    with open(log_path) as f:
        began = False
        for line in f:
            if not began:
                if f'{p}.{i}.{m}' in line:
                    began = True
                    lines = []
            else:
                if '|' not in line:
                    lines.append(line)
                else:
                    began = False
    return parse_str(''.join(lines))

def to_size(size_str):
    if size_str.startswith('restrict '):
        return int(size_str[len('restrict '):])
    else:
        return int(size_str)

def parse_sizes(part):
    part = part.strip()
    name = part[:part.index('[')]
    size_strs = part[part.index('[')+1: part.rindex(']')].split('][')
    return name, [to_size(size_str) for size_str in size_strs]

def get_loop_bounds(pattern):
    bounds = {}
    for loop in get_ordered_loops(pattern):
        for shape in loop.loop_shapes:
            name = shape.loop_var.var
            low = shape.greater_eq.val
            high = shape.less_eq.val
            if name not in bounds:
                bounds[name] = [None, None]
            if bounds[name][0] is None or low < bounds[name][0]:
                bounds[name][0] = low
            if bounds[name][1] is None or bounds[name][1] < high:
                bounds[name][1] = high
    return bounds

def set_loop_bounds(pattern, bounds):
    for loop in get_ordered_loops(pattern):
        for shape in loop.loop_shapes:
            low, high = bounds[shape.loop_var.var]
            shape.greater_eq = Literal(int, low)
            shape.less_eq = Literal(int, high)

def parse_sizess(wrapper_path):
    with open(wrapper_path) as f:
        print(wrapper_path)
        for line in f:
            sizess = {}
            if 'core' in line:
                parts = line.split('float')
                for part in parts[1:]:
                    name, sizes = parse_sizes(part)
                    sizess[name] = sizes
                return sizess

def get_representative_loop_body(mutation):
    last_loop = mutation.body[-1]
    return [stmt.clone() for stmt in last_loop.body]

instances_to_save = []
mutations_to_save = []

for p, instances in patterns:
    print(p)
    pattern_path = f'{patterns_dir}/{p}.pattern'
    log_path = f'{logs_dir}/{p}.log'
    pattern, _ = read_pattern(pattern_path)
    print(pattern.pprint())
    for i, mutations in instances:
        print(p, i)
        instance = pattern.clone()
        print(instance.pprint())
        for decl in instance.decls:
            print(decl.name)

        wrapper_path = f'{code_dir}/{p}.{i}.wrapper.c'
        sizess = parse_sizess(wrapper_path)
        for decl in instance.decls:
            decl.sizes = sizess[decl.name]

        m = mutations[0]
        mutation, _ = read_mutation(log_path, p, i, m)
        bounds = get_loop_bounds(mutation)
        set_loop_bounds(instance, bounds)
        assert(len(instance.body) == 1)
        instance.body[0].body = get_representative_loop_body(mutation)

        print(instance.pprint())
        instances_to_save.append((instance, f'{p}.{i}'))

        for m in mutations:
            print(p, i, m)
            mutation, _ = read_mutation(log_path, p, i, m)

            for decl in mutation.decls:
                decl.sizes = sizess[decl.name]
            print(mutation.pprint())
            mutations_to_save.append((mutation, f'{p}.{i}.{m}'))

write_patterns_to_dir(instances_to_save, 'instances')
write_patterns_to_dir(mutations_to_save, 'mutations')
