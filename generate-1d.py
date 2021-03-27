from skeleton import \
    parse_str as parse_skeleton, \
    parse_stmt_str as parse_statement, \
    parse_seq_str as parse_seq, \
    parse_expr_str as parse_expression

from pattern import generate_patterns_from_skeleton
from skeleton_ast import Var, Op
from random import choice, seed
from instance import create_instance_with_fixed_size
from codelet_generator import generate_codelet_full, name
from populator import PopulateParameters, populate_name, populate_stmt, populate_expr, populate_op

seed(12345)

skeleton_code = """
declare S[];
declare A[];
declare B[];
declare C[];
declare a;
declare b;
declare c;

for [i] {
  #_:lhs# = #_:rhs# @_@ #_:rhs# @_@ #_:rhs#;
}
"""

def generate(skeleton):
    exprs = PopulateParameters()
    lhs = ['S[0]', 'A[i]', 'B[i]', 'C[i]']
    exprs.add('lhs', [parse_expression(code) for code in lhs])
    rhs = ['S[0]', 'A[i]', 'B[i]', 'C[i]', 'a', 'b', 'c', '2.0']
    exprs.add('rhs', [parse_expression(code) for code in rhs])

    ops = PopulateParameters()
    op_names = ['+', '*']
    ops.add('_', [Op(name) for name in  op_names])

    code = skeleton.clone()
    code = populate_expr(code, exprs.populate)
    code = populate_op(code, ops.populate)
    return code

skeleton = parse_skeleton(skeleton_code)

patterns = []
hashes = set()

patterns = generate_patterns_from_skeleton(
    generate,
    skeleton,
    n_wanted = 10)

application = 'LoopGen'
sizes = [850, 2550]
n_iterations = 2
for size in sizes:
    for pattern in patterns:
        instance = create_instance_with_fixed_size(pattern, size)
        print(instance.pattern.pprint())
        batch = f'vector-{size}'
        code_prefix = f'{name(instance.pattern)}'
        code = f'{code_prefix}.c'
        codelet = f'{code_prefix}_{size}.c_de'

        generate_codelet_full(application, batch, code, codelet,
                              n_iterations, instance)
