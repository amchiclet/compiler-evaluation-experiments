from parser import parse_file
from z3 import Solver, Ints, unsat, Optimize, sat, Int
from loguru import logger
from abstract_ast import get_accesses

def is_statement_sorted(loop, ref1, ref2):
    return loop.body.index(ref1.parent_stmt) < loop.body.index(ref2.parent_stmt)

def test_dependence(loop):
    for (ref1, ref2) in iterate_reference_pairs(loop):
        direction_vector = calculate_direction_vector(loop, ref1, ref2)
        print(f'Testing {ref1.pprint()} -> {ref2.pprint()}: {direction_vector}')
        if is_independent(direction_vector):
            print('\tINDEPENDENT')
            continue

        if is_positive(direction_vector):
            print(f'\tLOOP-CARRIED: {direction_vector}')
            continue

        if is_zero(direction_vector):
            if is_statement_sorted(loop, ref1, ref2):
                print(f'\tLOOP_INDEPENDENT')
                continue

        print(f'\tNOT IN THIS DIRECTION')


def iterate_reference_pairs(loop):
    accesses = get_accesses(loop)
    for access1 in accesses:
        for access2 in accesses:
            if access1.var != access2.var:
                continue
            if not access1.is_write and not access2.is_write:
                continue
            yield (access1, access2)

def calculate_direction_vector(loop, source_ref, sink_ref):
    source_cvars, sink_cvars = generate_constraint_vars(loop.loop_vars)
  
    constraints = []
    constraints += generate_loop_bound_constraints(loop, source_cvars)
    constraints += generate_loop_bound_constraints(loop, sink_cvars)
    constraints += generate_subscript_equality_constraints(source_ref, source_cvars,
                                                           sink_ref, sink_cvars)

    direction_vector = []
    for v in loop.loop_vars:
        direction = calculate_direction(source_cvars[v],
                                        sink_cvars[v],
                                        constraints)
        direction_vector += [direction]
    return direction_vector

def generate_constraint_vars(loop_vars):
    source_cvars = {}
    sink_cvars = {}
    for v in loop_vars:
        source_cvars[v] = Int(f'{v}_source')
        sink_cvars[v] = Int(f'{v}_sink')
    return (source_cvars, sink_cvars)

def generate_loop_bound_constraints(loop, constraint_vars):
    constraints = []
    for v in loop.loop_vars:
        cvar = constraint_vars[v]
        constraints += [0 <= cvar, cvar < 500]
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

def calculate_direction(source_cvar, sink_cvar, constraints):
    direction = []
    if solve(source_cvar < sink_cvar, constraints):
        direction += ['<']
    if solve(source_cvar == sink_cvar, constraints):
        direction += ['=']
    if solve(source_cvar > sink_cvar, constraints):
        direction += ['>']
    return direction

def solve(what, constraints):
    solver = Solver()
    solver.add(constraints)
    status = solver.check(what)
    return status == sat

def is_independent(direction_vector):
    return [] in direction_vector

def is_positive(direction_vector):
    for d in direction_vector:
        if '<' in d:
            return True
        if '=' in d:
            continue
        if '>' in d:
            return False
    return False

def is_zero(direction_vector):
    for d in direction_vector:
        if not '=' in d:
            return False
    return True

program, _ = parse_file('simple_dep.loop')

loop = program.loops[0]
print(loop.pprint())
test_dependence(loop)
