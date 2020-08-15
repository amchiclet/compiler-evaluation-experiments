from abstract_ast import get_accesses, get_loops, Access, Op, ConstReplacer
from random import randint, choice, shuffle
from loguru import logger
from dependence_analysis import expr_to_cexpr

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

from z3 import Solver, Int, unsat, Optimize, sat, Or

def affine_to_cexpr(affine, cvars):
    if not affine.var:
        return affine.offset
    return affine.coeff * cvars[affine.var] + affine.offset

def find_max(constraints, expr):
    if type(expr) == int:
        return expr
    max_optimize = Optimize()
    max_optimize.assert_exprs(*constraints)
    max_optimize.maximize(expr)
    max_val = None
    if sat == max_optimize.check():
        max_val = max_optimize.model().eval(expr).as_long()
    constraint_strs = [f'{c}' for c in constraints]
    logger.debug(f'Find max:\n' + '\n'.join(constraint_strs))
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

def determine_array_sizes(decls, accesses, cvars, constraints, var_map):
    array_sizes = {}
    cloned = var_map.clone()
    for decl in decls:
        sizes = []
        for dimension in range(decl.n_dimensions):
            var = dimension_var(decl.name, dimension)
            if cloned.has_min(var):
                sizes.append(max(1, cloned.get_min(var)))
            else:
                sizes.append(1)
        array_sizes[decl.name] = sizes

    for access in accesses:
        for dimension, index in enumerate(access.indices):
            cexpr = expr_to_cexpr(index, cvars)
            if cexpr is None:
                logger.warning(f'Unable to analyze the max value of {index.pprint()} in {access.pprint()}')
                max_val = cloned.default_max
            else:
                max_val = find_max(constraints, cexpr)
                assert(max_val is not None)
                max_val = min(max_val + 1, cloned.default_max)

            # var = dimension_var(access.var, dimension)

            # # Update the min value for the array size.
            # # Min array size must be large enough to
            # # hold the max index.
            if max_val > array_sizes[access.var][dimension]:
                array_sizes[access.var][dimension] = max_val

    return array_sizes

def validate_var_map(program, var_map):
    cloned = var_map.clone()

    accesses = get_accesses(program)

    cvars = get_scalar_cvars(program)
    index_constraints = generate_index_constraints(accesses, cvars, cloned)
    bound_constraints = generate_bound_constraints(cvars, cloned)
    constraints = index_constraints + bound_constraints

    solver = Solver()
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

def get_scalar_cvars(pattern):
    cvars = {}
    for access in get_accesses(pattern):
        if access.is_scalar():
            if access.var not in cvars:
                cvars[access.var] = Int(access.var)
    return cvars

def create_instance(program, var_map, max_tries=10000):
    def randomly_replace_consts():
        cloned = program.clone()
        replace_map = {}
        for const in cloned.consts:
            var = const.name
            min_val = var_map.get_min(var)
            max_val = var_map.get_max(var)
            # TODO: support other types than int
            val = randint(min_val, max_val)
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
        constraints = index_constraints + loop_shape_constraints

        solver = Solver()
        solver.add(constraints)
        status = solver.check()
        if status == unsat:
            logger.debug('unsat retrying')
            logger.debug('\n'.join(map(str, constraints)))
            return None
        array_sizes = determine_array_sizes(random_pattern.decls,
                                            accesses, cvars,
                                            constraints,
                                            cloned_var_map)

        return Instance(random_pattern, array_sizes)

    result = None
    for _ in range(max_tries):
        result = try_once()
        if result is not None:
            return result

    return result
