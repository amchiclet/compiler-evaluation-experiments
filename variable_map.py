from abstract_ast import get_accesses, get_loops, Access, Op
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

def validate_var_map(program, var_map):
    accesses = get_accesses(program)

    cvars = {}
    def add_cvar(expr):
        if type(expr) == Access:
            if expr.is_scalar() and expr.var not in cvars:
                cvars[expr.var] = Int(expr.var)
        elif type(expr) == Op:
            for arg in expr.args:
                add_cvar(arg)

    for access in accesses:
        for index in access.indices:
            add_cvar(index)

    constraints = []
    for access in accesses:
        for index in access.indices:
            cexpr = expr_to_cexpr(index, cvars)
            if cexpr is not None:
                constraints.append(0 <= cexpr)

    restricted_var_map = var_map.clone()
    # figure out maximum array sizes if any of their limits are not set
    for var, cvar in cvars.items():
        current_min = var_map.get_min(var)
        current_max = var_map.get_max(var)
        constraints.append(cvar >= current_min)
        constraints.append(cvar <= current_max)

    for var, cvar in cvars.items():
        min_val, max_val = find_min_max(constraints, cvars[var])
        assert(min_val is not None)
        assert(max_val is not None)
        restricted_var_map.set_min(var, min_val)
        restricted_var_map.set_max(var, max_val)

    for access in accesses:
        for dimension, index in enumerate(access.indices):
            cexpr = expr_to_cexpr(index, cvars)
            if cexpr is None:
                logger.warning(f'Unable to analyze the max value of {index.pprint()} in {access.pprint()}')
            else:
                max_val = find_max(constraints, cexpr)
                assert(max_val is not None)
                var = dimension_var(access.var, dimension)

            # Update the min value for the array size.
            # Min array size must be large enough to
            # hold the max index.
            if restricted_var_map.has_min(var):
                if max_val > restricted_var_map.get_min(var):
                    restricted_var_map.set_min(var, max_val)
            else:
                restricted_var_map.set_min(var, max_val)

    return restricted_var_map

def randomize_iteration_vars(program, var_map):
    cloned = var_map.clone()
    loops = get_loops(program)
    loop_vars = set()
    for loop in loops.values():
        loop_vars.update(loop.loop_vars)
    for var in loop_vars:
        current_min = var_map.get_min(var)
        current_max = var_map.get_max(var)

        # tighten it
        x = randint(current_min, current_max)
        y = randint(current_min, current_max)
        new_min = min(x, y)
        new_max = max(x, y)

        cloned.set_min(var, new_min)
        cloned.set_max(var, new_max)
    return cloned
