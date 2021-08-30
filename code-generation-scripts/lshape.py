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
from populator import PopulateParameters, populate_stmt, populate_expr, populate_op, populate_name, ChoiceRecorder, IncrementalChoice
from random import randint, seed, choice

seed(0)
code = """
declare v00[];
declare v01[];
declare v02[];
declare v03[];
declare v04[];
declare v05[];
declare v06[];
declare v07[];
declare v08[];
declare v09[];
declare v10[];
declare v11[];
declare v12[];
declare v13[];
declare v14[];
declare v15[];
declare v16[];
declare v17[];
declare v18[];
declare v19[];

for [(i, >=0, <=31998)] {
  $_:N1$
  $_:N1$
  $_:N1$
  $_:N1$
  $_:N1$

  $_:N2$
  $_:N2$
  $_:N2$
  $_:N2$
  $_:N2$
  $_:N2$
  $_:N2$
  $_:N2$
  $_:N2$
  $_:N2$
}
"""

def generate_block(skeleton, n1, l1, n2, l2):
    max_n1 = 5
    max_n2 = 10
    stmt_parameters = PopulateParameters()

    def add_param(name, n, l, max_n):
        l_rhs = ' + '.join(['#_:rhs#'] * l)
        n_skeleton_code = f'#_:lhs# = {l_rhs};'
        stmts = [parse_stmt(stmt)
                 for stmt in [n_skeleton_code] * n + [';'] * (max_n-n)]
        inc = IncrementalChoice()
        stmt_parameters.add(name, stmts, choice_function=inc.choice)

    add_param('N1', n1, l1, max_n1)
    add_param('N2', n2, l2, max_n2)

    skeleton = populate_stmt(skeleton, stmt_parameters.populate)
    return skeleton

def fill_expressions(skeleton, n_lhs, n_rhs, n_rhs_vars):
    lhs_exprs = [parse_expr(f'v{i:02d}[i]')
                 for i in range(n_lhs)]
    rhs_pool = [parse_expr(f'v{i:02d}[i]')
                for i in range(n_rhs_vars)]
    rhs_exprs = [expr.clone() for expr in rhs_pool]
    for _ in range(n_rhs - len(rhs_exprs)):
        rhs_exprs.append(choice(rhs_pool).clone())

    expr_parameters = PopulateParameters()
    expr_parameters.add('lhs', lhs_exprs, choice_function=IncrementalChoice().choice)
    expr_parameters.add('rhs', rhs_exprs)
    skeleton = populate_expr(skeleton, expr_parameters.populate)
    return skeleton

def generate(skeleton, n1, l1, n2, l2, n_rhs_vars):
    skeleton = generate_block(skeleton, n1, l1, n2, l2)
    n_lhs = n1 + n2
    n_rhs = n1 * l1 + n2 * l2
    skeleton = fill_expressions(skeleton, n_lhs, n_rhs, n_rhs_vars)
    return skeleton

var_map = VariableMap(default_min=0, default_max=32000)
types = TypeAssignment(default_types=['int'])
init_value_map = {}
n_max_vars = 20
for i in range(n_max_vars):
    v = f'v{i:02d}'
    types.set(v, 'double')
    init_value_map[v] = 'drand(0.0, 1.0)'

application = 'LoopGen'
batch = 'lshape'
n_iterations = 10
n_elements = 0

generated = set()
n_to_generate = 15
skeleton = parse_skeleton(code)
while len(generated) < n_to_generate:
    n1 = randint(1, 5)
    n2 = randint(n1, 10)
    l2 = randint(1, 5)
    l1 = randint(l2, 10)
    n_rhs_vars = randint(1, n_max_vars)
    code_id = (n1, l1, n2, l2, n_rhs_vars)
    if code_id in generated:
        continue
    generated.add(code_id)
    generated_skeleton = generate(skeleton.clone(), *code_id)
    pattern = parse_pattern(generated_skeleton.pprint())
    instance = create_instance(pattern, var_map, types=types, max_tries=1)
    name = f'lshape_{n_rhs_vars:02d}_{n1:02d}x{l1:02d}_{n2:02d}x{l2:02d}'
    code = f'{name}.c'
    codelet = f'{code}_de'
    generate_codelet_full(application, batch, code, codelet,
                          n_iterations, n_elements, instance, init_value_map)


print('name, n_rhs_vars, n1, l1, n2, l2')
rows = []
for n1, l1, n2, l2, n_rhs_vars in generated:
    name = f'lshape_{n_rhs_vars:02d}_{n1:02d}x{l1:02d}_{n2:02d}x{l2:02d}'
    rows.append(', '.join([name, str(n_rhs_vars), str(n1), str(l1), str(n2), str(l2)]))
for row in sorted(rows):
    print(row)
