from abstract_ast import get_accesses, get_loops, Access, Op, ConstReplacer
from random import randint, choice, shuffle, uniform
from loguru import logger
from dependence_analysis import expr_to_cexpr
from copy import deepcopy
from enum import Enum

class Error(Enum):
    Z3_BUG = 0

class Limit:
    def __init__(self, min_val=None, max_val=None):
        self.min_val = min_val
        self.max_val = max_val
    def clone(self):
        return Limit(self.min_val, self.max_val)

class VariableMap:
    def __init__(self, default_min=0, default_max=999):
        self.default_min = default_min
        self.default_max = default_max
        self.limits = {}
    def remove_var(self, var):
        if var in self.limits:
            self.limits.pop(var)
    def has_min(self, var):
        return var in self.limits and not self.limits[var].min_val is None
    def has_max(self, var):
        return var in self.limits and not self.limits[var].max_val is None
    def set_min(self, var, min_val):
        if var not in self.limits:
            self.limits[var] = Limit()
        self.limits[var].min_val = min_val
    def set_max(self, var, max_val):
        if var not in self.limits:
            self.limits[var] = Limit()
        self.limits[var].max_val = max_val
    def get_min(self, var):
        if var not in self.limits:
            return self.default_min
        min_val = self.limits[var].min_val
        return min_val if min_val else self.default_min
    def get_max(self, var):
        if var not in self.limits:
            return self.default_max
        max_val = self.limits[var].max_val
        return max_val if max_val else self.default_max
    def clone(self):
        cloned = VariableMap(self.default_min, self.default_max)
        for var, limit in self.limits.items():
            cloned.limits[var] = limit.clone()
        return cloned
    def pprint(self):
        lines = []
        for var in sorted(self.limits.keys()):
            limit = self.limits[var]
            lines.append(f'Variable {var} range [{limit.min_val}, {limit.max_val}]')
        return '\n'.join(lines)

from z3 import Solver, Int, unsat, Optimize, sat, Or, And, Not

def affine_to_cexpr(affine, cvars):
    if not affine.var:
        return affine.offset
    return affine.coeff * cvars[affine.var] + affine.offset

def find_max(constraints, expr, l = None):
    if l is None:
        l = logger

    if type(expr) == int:
        return expr

    constraint_strs = [f'{c}' for c in constraints]

    max_optimize = Optimize()
    max_optimize.set('timeout', 10000)
    max_optimize.assert_exprs(*constraints)
    max_optimize.maximize(expr)
    status = max_optimize.check()
    if status != sat:
        l.warning(f'Unable to find max ({status}) for:\n' + '\n'.join(constraint_strs))
        return None

    max_val = max_optimize.model().eval(expr).as_long()

    # Make sure it's actually the max, since z3 has a bug
    #   https://github.com/Z3Prover/z3/issues/4670
    solver = Solver()
    solver.set('timeout', 10000)
    solver.add(constraints + [expr > max_val])
    status = solver.check()

    if status != unsat:
        l.warning(f'Z3 bug\nFind max ({expr}) => {max_val} with status ({status}):\n' + '\n'.join(constraint_strs))
        return Error.Z3_BUG
    return max_val

def find_min(constraints, expr):
    min_optimize = Optimize()
    min_optimize.assert_exprs(*constraints)
    min_optimize.minimize(expr)
    min_val = None
    if sat == min_optimize.check():
        min_val = min_optimize.model().eval(expr).as_long()
    return min_val

def find_min_max(constraints, i):
    return [f(constraints, i) for f in [find_min, find_max]]

def dimension_var(var, dimension):
    return f'{var}{"[]"*(dimension+1)}'

def generate_index_constraints(accesses, cvars, var_map):
    constraints = []
    for access in accesses:
        for dimension, index in enumerate(access.indices):
            cexpr = expr_to_cexpr(index, cvars)
            if cexpr is not None:
                constraints.append(0 <= cexpr)
                dim_var = dimension_var(access.var, dimension)
                dim_size = var_map.get_max(dim_var)
                constraints.append(cexpr < dim_size)
    return constraints

def generate_loop_shape_constraints(loop_shapes, cvars, var_map):
    constraints = []
    for shape in loop_shapes:
        i = expr_to_cexpr(shape.loop_var, cvars)

        i_greater_eq = expr_to_cexpr(shape.greater_eq, cvars)
        if i_greater_eq is not None:
            constraints.append(i_greater_eq <= i)

        i_less_eq = expr_to_cexpr(shape.less_eq, cvars)
        if i_less_eq is not None:
            constraints.append(i <= i_less_eq)

    return constraints

def generate_bound_constraints(cvars, var_map):
    constraints = []
    for var, cvar in cvars.items():
        current_min = var_map.get_min(var)
        current_max = var_map.get_max(var)
        constraints.append(cvar >= current_min)
        constraints.append(cvar <= current_max)
    return constraints

def determine_array_sizes(decls, accesses, cvars, constraints, var_map, l=None):
    if l is None:
        l = logger
    constraint_strs = '\n'.join(map(str, constraints))
    l.debug(f'Determining array sizes for constraints\n{constraint_strs}')
    bypass_set = set()
    array_sizes = {}
    cloned = var_map.clone()
    for decl in decls:
        sizes = []
        for dimension in range(decl.n_dimensions):
            dim_var = dimension_var(decl.name, dimension)
            if cloned.has_min(dim_var):
                sizes.append(cloned.get_min(dim_var))
                bypass_set.add(dim_var)
            else:
                sizes.append(1)
        array_sizes[decl.name] = (decl.is_local, sizes)

    for access in accesses:
        for dimension, index in enumerate(access.indices):

            dim_var = dimension_var(access.var, dimension)
            if dim_var in bypass_set:
                continue

            cexpr = expr_to_cexpr(index, cvars)
            if cexpr is None:
                l.warning(f'Unable to analyze the max value of {index.pprint()} in {access.pprint()}')
                max_val = cloned.default_max
            else:
                max_val = find_max(constraints, cexpr, l)
                if max_val is None or max_val == Error.Z3_BUG:
                    return max_val
                max_val = min(max_val + 1, cloned.default_max)

            # var = dimension_var(access.var, dimension)

            # # Update the min value for the array size.
            # # Min array size must be large enough to
            # # hold the max index.
            if max_val > array_sizes[access.var][1][dimension]:
                array_sizes[access.var][1][dimension] = max_val

    return array_sizes

def validate_var_map(program, var_map):
    cloned = var_map.clone()

    accesses = get_accesses(program)

    cvars = get_scalar_cvars(program)
    index_constraints = generate_index_constraints(accesses, cvars, cloned)
    bound_constraints = generate_bound_constraints(cvars, cloned)
    constraints = index_constraints + bound_constraints

    solver = Solver()
    solver.set('timeout', 10000)
    solver.add(constraints)
    status = solver.check()

    if status == unsat:
        return False
    return True

class Instance:
    def __init__(self, pattern, array_sizes):
        self.pattern = pattern
        self.array_sizes = array_sizes
    def pprint(self):
        lines = []
        lines.append(self.pattern.pprint())
        for name in sorted(self.array_sizes.keys()):
            lines.append(f'Array {name}: {self.array_sizes[name]}')
        return '\n'.join(lines)
    def clone(self):
        return Instance(self.pattern.clone(),
                        deepcopy(self.array_sizes))

def get_scalar_cvars(pattern):
    cvars = {}
    for access in get_accesses(pattern):
        if access.is_scalar():
            if access.var not in cvars:
                cvars[access.var] = Int(access.var)
    return cvars

def try_create_instance(pattern, var_map, l=None):
    if l is None:
        l = logger

    cvars = get_scalar_cvars(pattern)
    accesses = get_accesses(pattern)
    cloned_var_map = var_map.clone()
    index_constraints = generate_index_constraints(accesses,
                                                   cvars,
                                                   cloned_var_map)

    loop_shape_constraints = []
    for loop in get_loops(pattern).values():
        loop_shape_constraints += generate_loop_shape_constraints(loop.loop_shapes,
                                                                  cvars,
                                                                  cloned_var_map)

    l.debug('Index constraints:\n' + '\n'.join(map(str, index_constraints)))
    l.debug('Loop shape constraints:\n' + '\n'.join(map(str, loop_shape_constraints)))

    assert(len(index_constraints) > 0)
    invert_index_constraints = Not(And(index_constraints))

    constraints = [invert_index_constraints] + loop_shape_constraints

    solver = Solver()
    solver.set('timeout', 10000)
    solver.add(constraints)
    status = solver.check()
    if status != unsat:
        l.debug(f'Constraints are not unsatisfiable ({status}). '
                'May result in index out of bound')
        l.debug('Loop shape constraints:\n' + '\n'.join(map(str, constraints)))
        if status == sat:
            l.debug(f'Model:\n{solver.model()}')
        return None

    constraints = index_constraints + loop_shape_constraints
    solver = Solver()
    solver.set('timeout', 10000)
    solver.add(constraints)
    status = solver.check()
    if status != sat:
        l.debug('Constraints are not satisfiable ({status}). '
                'May result in no iterations')
        l.debug('\n'.join(map(str, constraints)))
        return None

    array_sizes = determine_array_sizes(pattern.decls,
                                        accesses, cvars,
                                        constraints,
                                        cloned_var_map, l)
    if array_sizes is None or array_sizes == Error.Z3_BUG:
        return array_sizes

    return Instance(pattern, array_sizes)

def create_instance(pattern, var_map, max_tries=10000, l=None):
    if l is None:
        l = logger

    def randomly_replace_consts():
        cloned = pattern.clone()
        replace_map = {}
        for const in cloned.consts:
            var = const.name
            min_val = var_map.get_min(var)
            max_val = var_map.get_max(var)
            # TODO: support other types than int
            if type(min_val) == int:
                val = randint(min_val, max_val)
            elif type(min_val) == float:
                val = uniform(min_val, max_val)
            replace_map[const.name] = val
        replacer = ConstReplacer(replace_map)
        cloned.replace(replacer)
        cloned.consts = []
        return cloned

    def try_once():
        random_pattern = randomly_replace_consts()
        cvars = get_scalar_cvars(random_pattern)
        accesses = get_accesses(random_pattern)
        cloned_var_map = var_map.clone()
        index_constraints = generate_index_constraints(accesses,
                                                       cvars,
                                                       cloned_var_map)

        loop_shape_constraints = []
        for loop in get_loops(random_pattern).values():
            loop_shape_constraints += generate_loop_shape_constraints(loop.loop_shapes,
                                                                      cvars,
                                                                      cloned_var_map)

        l.debug('Index constraints:\n' + '\n'.join(map(str, index_constraints)))
        l.debug('Loop shape constraints:\n' + '\n'.join(map(str, loop_shape_constraints)))

        assert(len(index_constraints) > 0)
        # conj_index_constraints = index_constraints[0]
        # for i in index_constraints[1:]:
        #     conj_index_constraints = And(conj_index_constraints, i)
        # invert_index_constraints = Not(conj_index_constraints)
        invert_index_constraints = Not(And(index_constraints))
        
        constraints = [invert_index_constraints] + loop_shape_constraints

        solver = Solver()
        solver.set('timeout', 10000)
        solver.add(constraints)
        status = solver.check()
        if status != unsat:
            l.debug(f'Constraints are not unsatisfiable ({status}). '
                    'May result in index out of bound')
            l.debug('Loop shape constraints:\n' + '\n'.join(map(str, constraints)))
            if status == sat:
                l.debug(f'Model:\n{solver.model()}')
            return None

        constraints = index_constraints + loop_shape_constraints
        solver = Solver()
        solver.set('timeout', 10000)
        solver.add(constraints)
        status = solver.check()
        if status != sat:
            l.debug('Constraints are not satisfiable ({status}). '
                    'May result in no iterations')
            l.debug('\n'.join(map(str, constraints)))
            return None

        array_sizes = determine_array_sizes(random_pattern.decls,
                                            accesses, cvars,
                                            constraints,
                                            cloned_var_map, l)
        if array_sizes is None or array_sizes == Error.Z3_BUG:
            return array_sizes

        return Instance(random_pattern, array_sizes)

    for _ in range(max_tries):
        result = try_once()
        if result == Error.Z3_BUG:
            return Error.Z3_BUG
        if result is not None:
            return result

    return None
