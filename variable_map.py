from abstract_ast import get_accesses, get_loops
from random import randint, choice, shuffle
from loguru import logger

class Limit:
    def __init__(self, min_val=None, max_val=None):
        self.min_val = min_val
        self.max_val = max_val
    def update_min_val(self, new_min_val):
        if new_min_val is None:
            return
        if self.min_val is None or new_min_val < self.min_val:
            self.min_val = new_min_val
    def update_max_val(self, new_max_val):
        if new_max_val is None:
            return
        if self.max_val is None or new_max_val > self.max_val:
            print('new max val', new_max_val)
            self.max_val = new_max_val
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
    def update_min_val(self, var, min_val):
        if var not in self.limits:
            self.limits[var] = Limit()
        self.limits[var].update_min_val(min_val)
    def update_max_val(self, var, max_val):
        if var not in self.limits:
            self.limits[var] = Limit()
        self.limits[var].update_max_val(max_val)
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
    for access in accesses:
        for index in access.indices:
            var = index.var
            if var is not None and var not in cvars:
                cvars[var] = Int(var)

    constraints = []
    for access in accesses:
        for index in access.indices:
            cexpr = affine_to_cexpr(index, cvars)
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
        restricted_var_map.update_min_val(var, min_val)
        restricted_var_map.update_max_val(var, max_val)

    for access in accesses:
        for dimension, index in enumerate(access.indices):
            cexpr = affine_to_cexpr(index, cvars)
            max_val = find_max(constraints, cexpr)
            print(access.pprint(), access.var)
            assert(max_val is not None)
            var = dimension_var(access.var, dimension)
            limits = restricted_var_map.limits
            if var not in limits:
                # min array size must be large enough to
                # hold the max index possible
                limits[var] = Limit(min_val=max_val)
            else:
                if max_val > limits[var].min_val:
                    limits[var].min_val = max_val

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
        cloned.update_min_val(var, new_min)
        cloned.update_max_val(var, new_max)
    return cloned
