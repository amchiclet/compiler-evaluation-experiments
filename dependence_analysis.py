from parser import parse_file
from z3 import Solver, Ints, unsat, Optimize, sat, Int
from loguru import logger
from abstract_ast import get_accesses, Program, AbstractLoop, Access, Op, Literal, gather_surrounding_loops, gather_loop_shapes, gather_loop_vars
from dependence_graph import Dependence, DependenceGraph

def is_ordered(l, v1, v2):
    return l.index(v1) < l.index(v2)

def analyze_dependence(program):
    graph = DependenceGraph()
    for (ref1, ref2) in iterate_unique_reference_pairs(program):
        for dependence_dv in iterate_dependence_direction_vectors(ref1, ref2):
            for ref1_then_ref2_dv in iterate_execution_order_direction_vector(ref1, ref2):
                logger.debug(f'Testing:\n'
                             f'{ref1.pprint()} -> {ref2.pprint()}:, '
                             f'dep({dependence_dv}) exe_order({ref1_then_ref2_dv})')
                dv1 = calculate_valid_direction_vector(dependence_dv,
                                                       ref1_then_ref2_dv)
                if dv1 is not None:
                    logger.debug(f'Valid direction vector: {dv1}')
                    graph.add(ref1, ref2, dv1)

            dependence_dv_inv = negate_direction_vector(dependence_dv)
            for ref2_then_ref1_dv in iterate_execution_order_direction_vector(ref2, ref1):
                logger.debug(f'Testing:\n'
                             f'{ref2.pprint()} -> {ref2.pprint()}:, '
                             f'dep({dependence_dv_inv}) exe_order({ref2_then_ref1_dv})')
                dv2 = calculate_valid_direction_vector(dependence_dv_inv,
                                                       ref2_then_ref1_dv)
                if dv2 is not None:
                    logger.debug(f'Valid direction vector: {dv2}')
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

def iterate_execution_order_direction_vector(source_ref, sink_ref):
    source_stmt = source_ref.parent_stmt
    source_loops = gather_surrounding_loops(source_stmt)
    source_trace = source_loops + [source_stmt]
    sink_stmt = sink_ref.parent_stmt
    sink_loops = gather_surrounding_loops(sink_stmt)
    sink_trace = sink_loops + [sink_stmt]
    logger.debug(f'debugging execution order dv\n'
                 f'source: {source_trace}\n'
                 f'sink: {sink_trace}')

    common_parents = get_common_prefix(source_loops, sink_loops)
    n_common_parents = len(common_parents)

    assert(n_common_parents > 0)
    n_common_loops = 0
    for parent in common_parents:
        if isinstance(parent, AbstractLoop):
            n_common_loops += len(parent.loop_shapes)

    common_ancestor = common_parents[-1]
    source_first_diff = source_trace[n_common_parents]
    sink_first_diff = sink_trace[n_common_parents]

    if isinstance(common_ancestor, Program):
        if not is_ordered(common_ancestor.body,
                          source_first_diff,
                          sink_first_diff):
            yield None
        else:
            yield []
    else:
        assert(isinstance(common_ancestor, AbstractLoop))
        if is_ordered(common_ancestor.body,
                      source_first_diff,
                      sink_first_diff):
            yield ['<='] + ['<=>'] * (n_common_loops - 1)
        else:
            for lt_position in range(n_common_loops):
                leading_eqs = ['='] * lt_position
                trailing_stars = ['<=>'] * (n_common_loops - 1 - lt_position)
                yield leading_eqs + ['<'] + trailing_stars

def gather_loop_steps(loop_shapes):
    steps = []
    for shape in loop_shapes:
        assert(type(shape.step) == Literal)
        assert(shape.step.ty == int)
        steps.append(shape.step.val)
    return steps

def get_common_prefix(l1, l2):
    common = []
    for v1, v2 in zip(l1, l2):
        if v1 != v2:
            break
        common.append(v1)
    return common

def iterate_dependence_direction_vectors(source_ref, sink_ref):
    source_loops = gather_surrounding_loops(source_ref.parent_stmt)
    source_loop_shapes = gather_loop_shapes(source_loops)
    source_loop_vars = gather_loop_vars(source_loop_shapes)
    sink_loops = gather_surrounding_loops(sink_ref.parent_stmt)
    sink_loop_shapes = gather_loop_shapes(sink_loops)
    sink_loop_vars = gather_loop_vars(sink_loop_shapes)

    source_cvars, sink_cvars, source_step_cvars, sink_step_cvars \
        = generate_constraint_vars(source_loop_vars,
                                   sink_loop_vars)

    constraints = []

    constraints += generate_loop_bound_constraints(source_loop_shapes,
                                                   source_cvars)

    # source_steps = gather_loop_steps(source_loop_shapes)
    constraints += generate_step_constraints(source_loop_shapes,
                                             source_cvars,
                                             source_step_cvars)

    constraints += generate_loop_bound_constraints(sink_loop_shapes,
                                                   sink_cvars)

    # sink_steps = gather_loop_steps(sink_loop_shapes)
    constraints += generate_step_constraints(sink_loop_shapes,
                                             sink_cvars,
                                             sink_step_cvars)

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
    common_loops = get_common_prefix(source_loops, sink_loops)
    common_loop_shapes = gather_loop_shapes(common_loops)
    common_loop_vars = gather_loop_vars(common_loop_shapes)
    yield from iterate_recursive(constraints, common_loop_vars, [])

def generate_constraint_vars(source_loop_vars, sink_loop_vars):
    source_cvars = {}
    sink_cvars = {}
    source_step_cvars = {}
    sink_step_cvars = {}
    for v in source_loop_vars:
        source_cvars[v] = Int(f'{v}_source')
        source_step_cvars[v] = Int(f'{v}_step_source')
    for v in sink_loop_vars:
        sink_cvars[v] = Int(f'{v}_sink')
        sink_step_cvars[v] = Int(f'{v}_step_sink')
    return (source_cvars, sink_cvars, source_step_cvars, sink_step_cvars)

def generate_loop_bound_constraints(loop_shapes, cvars):
    constraints = []
    for shape in loop_shapes:
        assert(type(shape.loop_var) == Access)
        v = shape.loop_var.var
        begin = expr_to_cexpr(shape.greater_eq, cvars)
        end = expr_to_cexpr(shape.less_eq, cvars)
        cvar = cvars[v]
        constraints += [begin <= cvar, cvar <= end]
    return constraints

def generate_step_constraints(loop_shapes, cvars, step_cvars):
    constraints = []
    for shape in loop_shapes:
        assert(type(shape.loop_var) == Access)
        v = shape.loop_var.var
        assert(type(shape.step) == Literal)
        assert(shape.step.ty == int)
        cvar = cvars[v]
        step_cvar = step_cvars[v]
        step = shape.step.val
        begin = expr_to_cexpr(shape.greater_eq, cvars)
        constraints += [cvar == step*step_cvar + begin]
    return constraints

def affine_to_cexpr(affine, cvars):
    if not affine.var:
        return affine.offset
    return affine.coeff * cvars[affine.var] + affine.offset

def expr_to_cexpr(expr, cvars):
    if type(expr) == Op:
        args = expr.args
        op = expr.op
        if len(args) == 1:
            cexpr = expr_to_cexpr(args[0])
            if expr.op == '+':
                return cexpr
            elif expr.op == '-':
                return -cexpr
        elif len(args) == 2:
            left = expr_to_cexpr(args[0], cvars)
            right = expr_to_cexpr(args[1], cvars)
            if left is not None and right is not None:
                if op == '+':
                    return left + right
                elif op == '*':
                    return left * right
                elif op == '-':
                    return left - right
                elif op == '/':
                    return left / right
    elif type(expr) == Literal:
        if expr.ty == int:
            return expr.val
    elif type(expr) == Access:
        if expr.is_scalar() and expr.var in cvars:
            return cvars[expr.var]
    return None

def generate_subscript_equality_constraints(source_ref, source_cvars, sink_ref, sink_cvars):
    constraints = []
    assert(len(source_ref.indices) == len(sink_ref.indices))
    if len(source_ref.indices) == 0:
        # Not adding anything means that the constraints will vacuously be satisfied
        # This is true because scalar variables always share the same memory in
        # all iterations.
        pass
    else:
        for (source_affine, sink_affine) in zip(source_ref.indices, sink_ref.indices):
            source_cexpr = expr_to_cexpr(source_affine, source_cvars)
            sink_cexpr = expr_to_cexpr(sink_affine, sink_cvars)
            # If either is None, it means that we won't be able to determine whether
            # the indices overlap or not. For example, A[A[i]] or A[1.5] vs anything.
            # Since we don't know their intersection, we conservatively assume they
            # overlap by not adding any constraints. (It will be treated as true.)
            if source_cexpr is not None and sink_cexpr is not None:
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

def find_min(constraints, expr, default_min=0):
    if type(expr) == int:
        return expr

    constraint_strs = [f'{c}' for c in constraints]

    min_optimize = Optimize()
    min_optimize.set('timeout', 10000)
    min_optimize.assert_exprs(*constraints)
    min_optimize.minimize(expr)
    status = min_optimize.check()
    if status != sat:
        l.warning(f'Unable to find min ({status}) for:\n' + '\n'.join(constraint_strs))
        return None

    min_val = min_optimize.model().eval(expr).as_long()

    # Make sure it's actually the min, since z3 has a bug
    #   https://github.com/Z3Prover/z3/issues/4670
    solver = Solver()
    solver.set('timeout', 10000)
    solver.add(constraints + [expr < min_val])
    status = solver.check()

    if status != unsat:
        l.warning(f'Z3 bug\nFind min ({expr}) => {min_val} with status ({status}):\n' + '\n'.join(constraint_strs))
        return None
    return min_val

def get_min_distance(source_ref, sink_ref):
    source_loops = gather_surrounding_loops(source_ref.parent_stmt)
    source_loop_shapes = gather_loop_shapes(source_loops)
    source_loop_vars = gather_loop_vars(source_loop_shapes)
    sink_loops = gather_surrounding_loops(sink_ref.parent_stmt)
    sink_loop_shapes = gather_loop_shapes(sink_loops)
    sink_loop_vars = gather_loop_vars(sink_loop_shapes)

    source_cvars, sink_cvars, source_step_cvars, sink_step_cvars \
        = generate_constraint_vars(source_loop_vars,
                                   sink_loop_vars)

    constraints = []

    constraints += generate_loop_bound_constraints(source_loop_shapes,
                                                   source_cvars)

    # source_steps = gather_loop_steps(source_loop_shapes)
    constraints += generate_step_constraints(source_loop_shapes,
                                             source_cvars,
                                             source_step_cvars)

    constraints += generate_loop_bound_constraints(sink_loop_shapes,
                                                   sink_cvars)

    # sink_steps = gather_loop_steps(sink_loop_shapes)
    constraints += generate_step_constraints(sink_loop_shapes,
                                             sink_cvars,
                                             sink_step_cvars)

    constraints += generate_subscript_equality_constraints(source_ref, source_cvars,
                                                           sink_ref, sink_cvars)

    common_loops = get_common_prefix(source_loops, sink_loops)
    common_loop_shapes = gather_loop_shapes(common_loops)
    common_loop_vars = gather_loop_vars(common_loop_shapes)

    distances = {}
    for loop_var in common_loop_vars:
        sink_cvar = sink_cvars[loop_var]
        source_cvar = source_cvars[loop_var]
        min_val = find_min(constraints, sink_cvar - source_cvar)
        if min_val is not None:
            assert(loop_var not in distances)
            distances[loop_var] = min_val

    return distances
