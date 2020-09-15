from dependence_analysis import analyze_dependence
from variable_map import VariableMap, try_create_instance, Error
from random import choice
from sampler import Sampler
from math import factorial
from loguru import logger
from abstract_ast import get_loops, get_accesses, gather_surrounding_loops, gather_loop_shapes, gather_loop_vars, get_ordered_assignments, Replacer, Access, Declaration

def gather_surrounding_loop_shapes(access):
    loops = gather_surrounding_loops(access.parent_stmt)
    shapes = gather_loop_shapes(loops)
    return shapes
#     return gather_loop_vars(shapes)

# def ensure_identical(loop_varss):
#     if len(loop_varss) == 0:
#         return []

#     expected = loop_varss[0]
#     for loop_vars in loop_varss[1:]:
#         if loop_vars != expected:
#             return []
#     return expected

# SimpleScalarExpansion only expands scalars for the "easy" cases,
# which are
#
# (1) when they are used exclusively inside one (nested) loop (which
# means they aren't defined before or used afterwards)
#
# (2) their first references are on the lhs (which means the scalar is
# not "forwarded" to the next iteration)
#
# Note that scalar input parameters to the kernel don't satisfy these requirements.
#
# In this case, all scalar references X will be converted to X[i][j][k] where the surrounding loop
# variables are i, j, and k in the order of the loop nesting.

def array_name(scalar_name):
    if scalar_name.endswith('_'):
        return f'{scalar_name}array'
    else:
        return f'{scalar_name}_array'

class ScalarReplacer(Replacer):
    def __init__(self, replace_map):
        self.replace_map = replace_map
    def should_replace(self, node):
        return type(node) == Access and node.var in self.replace_map
    def replace(self, node):
        indices = [Access(shape.loop_var.var) for shape in self.replace_map[node.var]]
        return Access(array_name(node.var), indices)

def get_candidates(instance):
    pattern = instance.pattern
    # for each local variable, map it to the loop vars surrounding it
    context_map = {}
    local_scalars = {decl.name for decl in pattern.decls
                     if decl.n_dimensions == 0 and decl.is_local}
    is_read_first = set()
    is_write_first = set()
    for assignment in get_ordered_assignments(instance.pattern):
        for access in get_accesses(assignment.rhs):
            var = access.var
            if var in local_scalars and var not in is_write_first:
                is_read_first.add(var)
        for access in get_accesses(assignment.lhs):
            var = access.var
            if var in local_scalars and var not in is_read_first:
                is_write_first.add(var)

    for access in get_accesses(pattern):
        if access.var not in local_scalars:
            continue
        loop_shapes = gather_surrounding_loop_shapes(access)
        var = access.var
        if var not in context_map:
            context_map[var] = loop_shapes
        if loop_shapes != context_map[var]:
            context_map[var] = None
    return {k:v for k, v in context_map.items()
            if v is not None and k in is_write_first}

class SimpleScalarExpansion:
    def transform(self, instance, var_map, max_tries=10):
        candidates = get_candidates(instance)

        n_tries = 0
        while n_tries < max_tries:
            cloned_pattern = instance.pattern.clone()

            for candidate in sorted(candidates.keys()):
                loop_shapes = candidates[candidate]
                is_expand = choice([True, False])
                if not is_expand:
                    continue
                replace_map = {candidate:loop_shapes}
                replacer = ScalarReplacer(replace_map)
                cloned_pattern.replace(replacer)

                new_var_name = array_name(candidate)
                new_array = Declaration(new_var_name,
                                        len(loop_shapes),
                                        is_local=True)
                cloned_pattern.decls.append(new_array)

            new_instance = try_create_instance(cloned_pattern, var_map)
            if new_instance is None:
                n_tries += 1
                print('for some reason it\'s failing')
                continue
            if new_instance == Error.Z3_BUG:
                yield None

            n_tries = 0
            yield new_instance
        while True:
            yield None
