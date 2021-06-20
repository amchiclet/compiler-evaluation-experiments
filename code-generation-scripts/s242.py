from pattern import parse_str as parse_pattern, generate_patterns_from_skeleton
from instance import create_instance
from constant_assignment import VariableMap
from type_assignment import TypeAssignment
from codegen.c_generator import generate_code
from codelet_generator import generate_codelet_full
from skeleton import \
    parse_str as parse_skeleton, \
    parse_stmt_str as parse_stmt, \
    parse_expr_str as parse_expr, \
    generate_from_skeleton
from skeleton_ast import Op, Var
from populator import PopulateParameters, populate_stmt, populate_expr, populate_op, populate_name, ChoiceRecorder
from random import randint, seed

seed(0)

size = 32000
main = """
declare a[32000];
declare s1;
declare s2;
declare b[32000];
declare c[32000];
declare d[32000];
declare e[32000];
declare f[32000];
declare g[32000];

$_$
$_$
"""

loop = """
for [(i, >=1, <=31999)] {
  a[i] = a[i-1] + #_:s1# + #_:s2# + #_:b# + #_:c# + #_:d# + #_:e# + #_:f# + #_:g#;
}
"""

stmt = [';', loop, loop]

def name(node):
    from pattern_ast import Hex, Assignment, AbstractLoop, Literal, Access, Program, Op, NoOp
    ty = type(node)
    if ty == Assignment:
        return name(node.lhs) + name(node.rhs)
    if ty == Access:
        return f'{node.var}'
    if ty == NoOp:
        return 'noop'
    if ty == AbstractLoop:
        assert(len(node.body) == 1)
        return name(node.body[0])
    if ty == Op:
        return name(node.args[0]) + name(node.args[1])
    if ty == Program:
        return '_'.join(name(loop) for loop in node.body)
    if ty == Literal:
        return ''
    raise RuntimeError(f'Unsupport type {ty}')

def generate(skeleton):
    parameters = PopulateParameters()
    parameters.add('_', [parse_stmt(code) for code in stmt], is_finite=True)
    skeleton = populate_stmt(skeleton, parameters.populate)

    parameters = PopulateParameters()
    parameters.add('s1', [parse_expr(code) for code in ['0', 's1']])
    parameters.add('s2', [parse_expr(code) for code in ['0', 's2']])
    parameters.add('b', [parse_expr(code) for code in ['0', 'b[i]']])
    parameters.add('c', [parse_expr(code) for code in ['0', 'c[i]']])
    parameters.add('d', [parse_expr(code) for code in ['0', 'd[i]']])
    parameters.add('e', [parse_expr(code) for code in ['0', 'e[i]']])
    parameters.add('f', [parse_expr(code) for code in ['0', 'f[i]']])
    parameters.add('g', [parse_expr(code) for code in ['0', 'g[i]']])

    skeleton = populate_expr(skeleton, parameters.populate)
    print(skeleton.pprint())

    pattern = parse_pattern(skeleton.pprint())

    var_map = VariableMap(default_max=size)

    # Specify variable types
    types = TypeAssignment(default_types=['int'])
    types.set('s1', 'double')
    types.set('s2', 'double')
    types.set('a', 'double')
    types.set('b', 'double')
    types.set('c', 'double')
    types.set('d', 'double')
    types.set('e', 'double')
    types.set('f', 'double')
    types.set('g', 'double')

    instance = create_instance(pattern, var_map, types=types, max_tries=1)
    if instance is None:
        return None

    instance_name = 's242_' + name(instance.pattern)
    print(instance_name)
    return instance, instance_name

skeleton = parse_skeleton(main)

instances = {}

generate_from_skeleton(
    generate,
    skeleton,
    n_wanted = 15,
    outputs=instances)

init_value_map = {
    's1': 'drand(0.0, 1.0)',
    's2': 'drand(0.0, 1.0)',
    'a': 'drand(0.0, 1.0)',
    'b': 'drand(0.0, 1.0)',
    'c': 'drand(0.0, 1.0)',
    'd': 'drand(0.0, 1.0)',
    'e': 'drand(0.0, 1.0)',
    'f': 'drand(0.0, 1.0)',
    'g': 'drand(0.0, 1.0)',
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
