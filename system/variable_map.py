from abstract_ast import get_accesses
class Limit:
    def __init__(self, min_val=None, max_val=None):
        self.min_val = min_val
        self.max_val = max_val

class VariableMap:
    def __init__(self, default_min=0, default_max=999):
        self.default_min = default_min
        self.default_max = default_max
        self.limits = {}
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

from z3 import Solver, Int, unsat, Optimize, sat, Or

def affine_to_cexpr(affine, cvars):
    if not affine.var:
        return affine.offset
    return affine.coeff * cvars[affine.var] + affine.offset

def find_min_max(constraints, i):
    min_optimize = Optimize()
    min_optimize.assert_exprs(*constraints)
    min_optimize.minimize(i)
    assert(sat == min_optimize.check())

    max_optimize = Optimize()
    max_optimize.assert_exprs(*constraints)
    max_optimize.maximize(i)
    assert(sat == max_optimize.check())
    return [
        min_optimize.model().eval(i).as_long(),
        max_optimize.model().eval(i).as_long() + 1,
    ]

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
            decls[(decl.name, dimension)] = size
    for access in accesses:
        for dimension in range(len(access.indices)):
            uses[(access.var, dimension)] = []
        for dimension, index in enumerate(access.indices):
            uses[(access.var, dimension)].append(index)
    for (array, dimension), indices in uses.items():
        if (array, dimension) not in decls:
            raise RuntimeError(
                f'Could not find declaration for array[dimension] {array}[{dimension}]')
        size = decls[(array, dimension)]
        csize = affine_to_cexpr(size, cvars)
        for index in indices:
            print(f'{array}[{dimension}] {index.pprint()}')
            cexpr = affine_to_cexpr(index, cvars)
            # constraints induced by array size
            constraints.append(0 <= cexpr)
            constraints.append(cexpr < csize)

    # constraints induced by configuration
    for var in all_vars:
        n = var_map.get_min(var)
        print(n, type(n))
        constraints.append(cvars[var] >= var_map.get_min(var))
        constraints.append(cvars[var] < var_map.get_max(var))
    # constraints.append(cvars['x'] < 200)
    for var in all_vars:
        min_val, max_val = find_min_max(constraints, cvars[var])
        print(f'Variable {var} [{min_val}, {max_val})')
