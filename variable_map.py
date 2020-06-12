from abstract_ast import get_accesses
from random import randint, choice

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

def find_min_max(constraints, i):
    min_optimize = Optimize()
    min_optimize.assert_exprs(*constraints)
    min_optimize.minimize(i)
    min_val = None
    if sat == min_optimize.check():
        min_val = min_optimize.model().eval(i).as_long()

    max_optimize = Optimize()
    max_optimize.assert_exprs(*constraints)
    max_optimize.maximize(i)
    max_val = None
    if sat == max_optimize.check():
        max_val = max_optimize.model().eval(i).as_long()

    return (min_val, max_val)

def calculate_array_sizes(decls, var_map):
    # maps name to [size]
    array_sizes = {}
    decl_vars = set()
    for decl in decls:
        array_sizes[decl.name] = []
        for affine in decl.sizes:
            if affine.var:
                decl_vars.add(affine.var)
    constraints = []
    cvars = {}
    for var in decl_vars:
        cvar = Int(var)
        cvars[var] = cvar
        constraints += [
            var_map.get_min(var) <= cvar,
            0 < cvar,
            cvar <= var_map.get_max(var)
        ]

    for decl in decls:
        for dimension, size in enumerate(decl.sizes):
            index = Int(f'{decl.name}[{dimension}]')
            new_constraints = constraints + [index == affine_to_cexpr(size, cvars)]
            min_val, max_val = find_min_max(new_constraints, index)
            array_sizes[decl.name].append(max_val)
    for array, size in array_sizes.items():
        print(array, size)
    return array_sizes

def restrict_var_map(program, var_map):
    # constraints relating array indices
    # for A[M]
    # (1) M >= 0 >= M_min
    # (2) for all i in A[i], i < M < M_max
    # 
    # If the maximum i leads to an maximum M less than the original maximum M,
    # then use the tigher maximum M
    # As for each of the indices, figure out the maximum possible

    # Algorithm:
    # (1) collect all variables (loop_vars, sizes)
    # (2) for each access to array X, for each index ai+c in dimension d
    # (3) ai+c >= 0 & ai+c < M
    # (4) find min and max for all loop_vars and sizes

    all_vars = set()
    decl_vars = set()
    ref_vars = set()
    for decl in program.decls:
        for affine in decl.sizes:
            if affine.var:
                decl_vars.add(affine.var)

    accesses = get_accesses(program)
    for access in accesses:
        for index in access.indices:
            if index.var:
                ref_vars.add(index.var)
    all_vars = decl_vars.union(ref_vars)

    cvars = {}
    for var in all_vars:
        cvars[var] = Int(var)
    
    # both of these dicts map (array name, dimension) to expressions
    decls = {}
    uses = {}

    # TODO: type check to prevent simple errors
    constraints = []
    for decl in program.decls:
        for dimension, size in enumerate(decl.sizes):
            key = (decl.name, dimension)
            decls[key] = size
            uses[key] = []

    for access in accesses:
        for dimension, index in enumerate(access.indices):
            uses[(access.var, dimension)].append(index)
    for (array, dimension), indices in uses.items():
        if (array, dimension) not in decls:
            raise RuntimeError(
                f'Could not find declaration for array[dimension] {array}[{dimension}]')
        size = decls[(array, dimension)]

        csize = affine_to_cexpr(size, cvars)

        for index in indices:
            cexpr = affine_to_cexpr(index, cvars)
            # constraints induced by array size
            constraints.append(0 <= cexpr)
            constraints.append(cexpr < csize)

    restricted_var_map = var_map.clone()

    for var in all_vars:
        current_min = var_map.get_min(var)
        current_max = var_map.get_max(var)
        print('restrict', var, current_min, current_max)
        constraints.append(cvars[var] >= current_min)
        constraints.append(cvars[var] <= current_max)
        if var in decl_vars:
            constraints.append(cvars[var] > 0)
    for var in all_vars:
        min_val, max_val = find_min_max(constraints, cvars[var])
        assert(min_val is not None)
        assert(max_val is not None)
        restricted_var_map.set_min(var, min_val)
        restricted_var_map.set_max(var, max_val)

    # either randomize the max values for ref vars or decl vars
    randomized_var_map = restricted_var_map.clone()
    for var in choice([decl_vars, ref_vars]):
        current_min = restricted_var_map.get_min(var)
        current_max = restricted_var_map.get_max(var)
        x = randint(current_min, current_max)
        y = randint(current_min, current_max)
        new_min = min(x, y)
        new_max = max(x, y)
        print('random', var, new_min, new_max)
        constraints.append(cvars[var] >= new_min)
        constraints.append(cvars[var] <= new_max)

    for var in all_vars:
        min_val, max_val = find_min_max(constraints, cvars[var])
        assert(min_val is not None)
        assert(max_val is not None)
        randomized_var_map.set_min(var, min_val)
        randomized_var_map.set_max(var, max_val)

    return randomized_var_map
