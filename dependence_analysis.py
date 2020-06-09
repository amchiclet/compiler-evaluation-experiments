from parser import parse_file
from z3 import Solver, Ints, unsat, Optimize, sat, Int
from loguru import logger
from abstract_ast import get_accesses, Program, AbstractLoop
from dependence_graph import Dependence, DependenceGraph

def is_ordered(l, v1, v2):
    return l.index(v1) < l.index(v2)

def analyze_dependence(program, var_map):
    graph = DependenceGraph()
    for (ref1, ref2) in iterate_unique_reference_pairs(program):

        ref1_then_ref2_dv = calculate_execution_order_direction_vector(ref1, ref2)
        ref2_then_ref1_dv = calculate_execution_order_direction_vector(ref2, ref1)
        for dependence_dv in iterate_dependence_direction_vectors(ref1, ref2, var_map):
            print(f'{ref1.pprint()} -> {ref2.pprint()}:, '
                  f'{dependence_dv} {ref1_then_ref2_dv}')
            dv1 = calculate_valid_direction_vector(dependence_dv,
                                                   ref1_then_ref2_dv)
            if dv1 is not None:
                graph.add(ref1, ref2, dv1)


            dependence_dv_inv = negate_direction_vector(dependence_dv)
            print(f'{ref2.pprint()} -> {ref2.pprint()}:, '
                  f'{dependence_dv_inv} {ref2_then_ref1_dv}')
            dv2 = calculate_valid_direction_vector(dependence_dv_inv,
                                                   ref2_then_ref1_dv)
            if dv2 is not None:
                graph.add(ref2, ref1, dv2)
    return graph

def iterate_unique_reference_pairs(program):
    refs = list(get_accesses(program))
    n_refs = len(refs)
    for i in range(0, n_refs):
        for j in range(i, n_refs):
            ref1 = refs[i]
            ref2 = refs[j]
            if ref1.var != ref2.var:
                continue
            if not ref1.is_write and not ref2.is_write:
                continue
            yield (ref1, ref2)


def calculate_execution_order_direction_vector(source_ref, sink_ref):
    source_stmt = source_ref.parent_stmt
    source_loops = gather_surrounding_loops(source_stmt)
    source_trace = source_loops + [source_stmt]
    sink_stmt = sink_ref.parent_stmt
    sink_loops = gather_surrounding_loops(sink_stmt)
    sink_trace = sink_loops + [sink_stmt]

    common_parents = get_common_prefix(source_loops, sink_loops)
    n_common_parents = len(common_parents)

    assert(n_common_parents > 0)
    n_common_loops = n_common_parents - 1

    common_ancestor = common_parents[-1]
    source_first_diff = source_trace[n_common_parents]
    sink_first_diff = sink_trace[n_common_parents]

    if isinstance(common_ancestor, Program):
        if not is_ordered(common_ancestor.loops,
                          source_first_diff,
                          sink_first_diff):
            return None
        else:
            return []

    assert(isinstance(common_ancestor, AbstractLoop))
    if is_ordered(common_ancestor.body,
                  source_first_diff,
                  sink_first_diff):
        return ['<='] + ['<=>'] * (n_common_loops - 1)
    else:
        return ['<'] + ['<=>'] * (n_common_loops - 1)

def gather_surrounding_loops(stmt):
    def recurse(s, acc):
        outer = s.surrounding_loop
        if not outer:
            return acc
        return recurse(outer, [outer] + acc)
    return recurse(stmt, [])

def gather_surrounding_loop_vars(ref):
    loop_vars = []
    for loop in gather_surrounding_loops(ref.parent_stmt):
        loop_vars += loop.loop_vars
    return loop_vars

def get_common_prefix(l1, l2):
    common = []
    for v1, v2 in zip(l1, l2):
        if v1 != v2:
            break
        common.append(v1)
    return common

def iterate_dependence_direction_vectors(source_ref, sink_ref, var_map):
    source_loop_vars = gather_surrounding_loop_vars(source_ref)
    sink_loop_vars = gather_surrounding_loop_vars(sink_ref)
    source_cvars, sink_cvars = generate_constraint_vars(source_loop_vars,
                                                        sink_loop_vars)

    constraints = []
    constraints += generate_loop_bound_constraints(source_loop_vars,
                                                   source_cvars,
                                                   var_map)
    constraints += generate_loop_bound_constraints(sink_loop_vars,
                                                   sink_cvars,
                                                   var_map)
    constraints += generate_subscript_equality_constraints(source_ref, source_cvars,
                                                           sink_ref, sink_cvars)

    def iterate_recursive(constraints, remaining_loop_vars, accumulated_dv):
        n_dimensions_left = len(remaining_loop_vars)

        if n_dimensions_left == 0:
            if solve(constraints):
                yield accumulated_dv
        else:
            # If we don't add additional constraints on the direction
            # relation between source and sink vars, it means the rest of
            # the dimensions are *s.
            if solve(constraints):
                source_cvar = source_cvars[remaining_loop_vars[0]]
                sink_cvar = sink_cvars[remaining_loop_vars[0]]
                yield from iterate_recursive(constraints + [source_cvar < sink_cvar],
                                             remaining_loop_vars[1:],
                                             accumulated_dv + ['<'])
                yield from iterate_recursive(constraints + [source_cvar == sink_cvar],
                                             remaining_loop_vars[1:],
                                             accumulated_dv + ['='])
                yield from iterate_recursive(constraints + [source_cvar > sink_cvar],
                                             remaining_loop_vars[1:],
                                             accumulated_dv + ['>'])
    common_loop_vars = get_common_prefix(source_loop_vars,
                                         sink_loop_vars)
    yield from iterate_recursive(constraints, common_loop_vars, [])

def generate_constraint_vars(source_loop_vars, sink_loop_vars):
    source_cvars = {}
    sink_cvars = {}
    for v in source_loop_vars:
        source_cvars[v] = Int(f'{v}_source')
    for v in sink_loop_vars:
        sink_cvars[v] = Int(f'{v}_sink')
    return (source_cvars, sink_cvars)

def generate_loop_bound_constraints(loop_vars, constraint_vars, var_map):
    constraints = []
    for v in loop_vars:
        min_val = var_map.get_min(v)
        max_val = var_map.get_max(v)
        cvar = constraint_vars[v]
        constraints += [min_val <= cvar, cvar < max_val]
    return constraints

def affine_to_cexpr(affine, cvars):
    if not affine.var:
        return affine.offset
    return affine.coeff * cvars[affine.var] + affine.offset

def generate_subscript_equality_constraints(source_ref, source_cvars, sink_ref, sink_cvars):
    constraints = []
    for (source_affine, sink_affine) in zip(source_ref.indices, sink_ref.indices):
        source_cexpr = affine_to_cexpr(source_affine, source_cvars)
        sink_cexpr = affine_to_cexpr(sink_affine, sink_cvars)
        constraints += [source_cexpr == sink_cexpr]
    return constraints

def solve(constraints):
    solver = Solver()
    solver.add(constraints)
    status = solver.check()
    return status == sat

def calculate_valid_direction_vector(dependence_dv, execution_order_dv):
    if execution_order_dv is None:
        return None

    # Requirement 1: dependence goes from a statement executed before to one executed later
    dv = intersect_direction_vector(dependence_dv, execution_order_dv)
    for d in dv:
        if d == '':
            return None

    # Requirement 2: dependence goes from source to sink (i.e., leftmost non = is <)
    for d in dv:
        if d == '>':
            return None
        if d == '<':
            return dv

    return dv

def intersect_direction_vector(dv1, dv2):
    return [intersect_direction(d1, d2) for (d1, d2) in zip(dv1, dv2)]

def intersect_direction(d1, d2):
    lt = '<' in d1 and '<' in d2
    eq = '=' in d1 and '=' in d2
    gt = '>' in d1 and '>' in d2
    return ('<' if lt else ''
            '=' if eq else ''
            '>' if gt else '')

def negate_direction_vector(dv):
    return [negate_direction(d) for d in dv]

def negate_direction(d):
    lt = '<' in d
    eq = '=' in d
    gt = '>' in d
    return ('<' if gt else ''
            '=' if eq else ''
            '>' if lt else '')
