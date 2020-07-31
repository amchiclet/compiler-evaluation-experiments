from pattern_generator import PatternInfo
from abstract_ast import Declaration

def create_pattern_info(n_stmts, n_ops):
    mul_consts = ['a1', 'a2', 'a3']
    add_consts = ['b1', 'b2', 'b3']
    data_consts = ['f1', 'f2', 'f3']
    loop_vars = ['i1', 'i2', 'i3', 'i4', 'i5', 'i6']
    decls = [
        Declaration('A', 1),
        Declaration('B', 1),
        Declaration('C', 1),
        Declaration('D', 1),
        Declaration('E', 1),
    ]
    ops = ['+', '*', '-']
    n_loops = 5
    n_depth = 3
    # n_stmts = 2
    # n_ops = 1
    pattern_info = PatternInfo(decls, mul_consts, add_consts,
                               data_consts, ops,
                               loop_vars, n_loops,
                               n_depth, n_stmts, n_ops)
    return pattern_info

def create_pattern_info_1():
    return create_pattern_info(1, 25)

def create_pattern_info_2():
    return create_pattern_info(2, 5)

def create_pattern_info_3():
    return create_pattern_info(2, 5)
