from pattern import parse_str as parse_pattern, generate_patterns_from_skeleton
from instance import create_instance
from constant_assignment import VariableMap
from type_assignment import TypeAssignment
from codegen.c_generator import generate_code
from codelet_generator import generate_codelet_full, name
from skeleton import parse_str as parse_skeleton, \
    parse_stmt_str as parse_stmt, \
    generate_from_skeleton

from populator import PopulateParameters, populate_stmt
from random import randint, seed

seed(0)

grid_point_size = 64 / 2 * 2 + 1 + 1
main = """
declare grid_points[3];
declare add;
declare rhs[64 / 2 * 2 + 1][64 / 2 * 2 + 1][64 / 2 * 2 + 1][m_end];
declare rms[m_end];

$_$
"""

loop_i = [
    "for [(i, >=1, <=grid_points[0]-2)] { $_$ }",
    "for [(i, >=1, <=1)] { $_$ }",
]

loop_j = [
    "for [(j, >=1, <=grid_points[1]-2)] { $_$ }",
    "for [(j, >=1, <=1)] { $_$ }",
]

loop_k = [
    "for [(k, >=1, <=grid_points[2]-2)] { $_$ }",
    "for [(k, >=1, <=1)] { $_$ }",
]

loop_m = """
for [(m, >=0, <=m_end-1)] {
  add = rhs[i][j][k][m];
  rms[m] = rms[m] + add * add;
}
"""

class AtMostNMax:
    def __init__(self, max_index, n_choices, n_max):
        self.choices = None
        while self.choices is None or self.choices.count(max_index) > n_max:
            self.choices = [randint(0, max_index) for _ in range(n_choices)]
        self.current = 0
    def choice(self, choices):
        print('choice!')
        c = choices[self.choices[self.current]]
        self.current += 1
        return c

def generate(skeleton):
    depth_control = AtMostNMax(
        1, # index 1 means to skip the loop
        3, # we're deciding from the outer 3 loops which ones to skip
        1  # we can skip at most 1
    )

    parameters = PopulateParameters()
    parameters.add('_', [parse_stmt(code) for code in loop_i], choice_function=depth_control.choice)
    skeleton = populate_stmt(skeleton, parameters.populate)

    parameters = PopulateParameters()
    parameters.add('_', [parse_stmt(code) for code in loop_j], choice_function=depth_control.choice)
    skeleton = populate_stmt(skeleton, parameters.populate)

    parameters = PopulateParameters()
    parameters.add('_', [parse_stmt(code) for code in loop_k], choice_function=depth_control.choice)
    skeleton = populate_stmt(skeleton, parameters.populate)

    parameters = PopulateParameters()
    parameters.add('_', [parse_stmt(loop_m)])
    skeleton = populate_stmt(skeleton, parameters.populate)

    pattern = parse_pattern(skeleton.pprint())

    n_inner_iterations = randint(2, 16)
    var_map = VariableMap()
    var_map.set_value('grid_points[0]', grid_point_size)
    var_map.set_value('grid_points[1]', grid_point_size)
    var_map.set_value('grid_points[2]', grid_point_size)
    var_map.set_value('m_end', n_inner_iterations)

    # Specify variable types
    types = TypeAssignment(default_types=['int'])
    types.set('add', 'double')
    types.set('rhs', 'double')
    types.set('rms', 'double')

    instance = create_instance(pattern, var_map, types=types, max_tries=100)
    if instance is None:
        return None

    chosen_loops = [var
                    for choice, var
                    in zip(depth_control.choices, ['i', 'j', 'k'])
                    if choice == 0]
    name = f'nrm261_{"_".join(chosen_loops)}_m_{n_inner_iterations}'

    return instance, name

skeleton = parse_skeleton(main)
instances = {}

generate_from_skeleton(
    generate,
    skeleton,
    n_wanted = 15,
    outputs=instances)

init_value_map = {
    'grid_points': str(grid_point_size),
    'add': 'drand(0.0, 1.0)',
    'rhs': 'drand(0.0, 1.0)',
    'rms': 'drand(0.0, 1.0)',
}

for name, instance in instances.items():
    application = 'LoopGen'
    batch = f'lore'
    code_prefix = name
    code = f'{code_prefix}.c'
    codelet = f'{code_prefix}.c_de'
    n_iterations = 10
    n_elements = 0

    generate_codelet_full('LoopGen', batch, code, codelet,
                          n_iterations, n_elements, instance, init_value_map)
