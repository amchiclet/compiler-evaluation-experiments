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

size = 92700
main = """
declare tmort[92700];
declare mormult[92700];
declare nmor;
declare A[];
declare B[];
declare C[];

for [(i, >=0, <=nmor-1)] {
  $_$
  $_$
}
"""

stmt = [
    'tmort[i] = (#_:tmort#) / (#_:mormult#);',
    'tmort[i] = (#_:tmort#) / (#_:mormult#);',
    #';'
]

tmort = [
    'tmort[i]',
    'tmort[i] * `_`[i]',
    'tmort[i] * `_`[i] * `_`[i]',
    'tmort[i] * `_`[i] * `_`[i] * `_`[i]',
]

mormult = [
    'mormult[i]',
    'mormult[i] * `_`[i]',
    'mormult[i] * `_`[i] * `_`[i]',
    'mormult[i] * `_`[i] * `_`[i] * `_`[i]',
]

def name_cnv(node):
    from pattern_ast import Hex, Assignment, AbstractLoop, Literal, Access, Program, Op
    ty = type(node)
    if ty == Assignment:
        return name_cnv(node.rhs)
    if ty == Access:
        return f'{node.var}'
    if ty == AbstractLoop:
        return '_'.join([name_cnv(stmt) for stmt in node.body])
    if ty == Op:
        if node.op == '/':
            return name_cnv(node.args[0]) + '_' + name_cnv(node.args[1])
        else:
            assert(node.op == '*')
            return name_cnv(node.args[0]) + name_cnv(node.args[1])
    if ty == Program:
        assert(len(node.body) == 1)
        return name_cnv(node.body[0])
    raise RuntimeError(f'Unsupport type {ty}')

def generate(skeleton):
    parameters = PopulateParameters()
    parameters.add('_', [parse_stmt(code) for code in stmt], is_finite=True)
    skeleton = populate_stmt(skeleton, parameters.populate)

    parameters = PopulateParameters()
    parameters.add('tmort', [parse_expr(code) for code in tmort])
    parameters.add('mormult', [parse_expr(code) for code in mormult])
    skeleton = populate_expr(skeleton, parameters.populate)

    parameters = PopulateParameters()
    parameters.add('_', [Op('+'), Op('*')])
    skeleton = populate_op(skeleton, parameters.populate)

    parameters = PopulateParameters()
    arrays = ['A', 'B', 'C']
    parameters.add('_', [Var(v) for v in arrays])
    skeleton = populate_name(skeleton, parameters.populate)

    pattern = parse_pattern(skeleton.pprint())

    var_map = VariableMap(default_max=size)
    var_map.set_value('nmor', size)

    # Specify variable types
    types = TypeAssignment(default_types=['int'])
    types.set('tmort', 'double')
    types.set('mormult', 'double')
    types.set('A', 'double')
    types.set('B', 'double')
    types.set('C', 'double')

    instance = create_instance(pattern, var_map, types=types, max_tries=1)
    if instance is None:
        return None

    name = 'cnv243_' + name_cnv(instance.pattern)

    return instance, name

skeleton = parse_skeleton(main)

instances = {}

generate_from_skeleton(
    generate,
    skeleton,
    n_wanted = 1,
    outputs=instances)

init_value_map = {
    'nmor': str(size),
    'tmort': 'drand(0.0, 1.0)',
    'mormult': 'drand(0.0, 1.0)',
    'A': 'drand(0.0, 1.0)',
    'B': 'drand(0.0, 1.0)',
    'C': 'drand(0.0, 1.0)',
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
