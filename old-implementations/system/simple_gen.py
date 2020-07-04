from abstract_ast import get_accesses
MAX_SIZE_PER_ARRAY = 501 * 501 * 501

# gather array dimensions and loop accesses
def get_program_info(program):
    # maps array name to [loop var name]
    arrays = {}
    # maps loop var name to (lower, upper)
    loop_vars = {}
    for access in get_accesses(program):
        array_name = access.var
        n_dimensions = len(access.indices)
        if n_dimensions == 0:
            continue
        if not array_name in arrays:
            arrays[array_name] = [None] * n_dimensions
        for i, abstract_index in enumerate(access.indices):
            loop_var = abstract_index.var

            # update arrays
            if not arrays[array_name][i]:
                arrays[array_name][i] = loop_var
            else:
                assert(arrays[array_name][i] == loop_var)

            # update loop_vars
            if not loop_var in loop_vars:
                loop_vars[loop_var] = [0, 0]
            loop_vars[loop_var][0] = min(loop_vars[loop_var][0],
                                         abstract_index.relationship)
            loop_vars[loop_var][1] = max(loop_vars[loop_var][1],
                                         abstract_index.relationship)
    return arrays, loop_vars
