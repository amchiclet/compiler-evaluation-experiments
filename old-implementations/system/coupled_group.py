from abstract_ast import all_pairs, is_same_memory
from z3_helper import find_minimum_valid_index
from dep_range import DepRange, DepRangeMap
from loguru import logger
# A coupled group should include
# array name
# set(loop_vars) that need to be analyzed together
# set(dimensions) that need to be analyzed together
# dimension -> index mappin
class CoupledGroup:
    def __init__(self, array, loop_vars, indices):
        if len(loop_vars) > 1:
            assert(len(loop_vars) == 2 and 'dummy' in loop_vars)
        assert(len(indices) > 0)
        expected_dimension = next(iter(indices)).dimension
        for index in indices:
            assert(expected_dimension == index.dimension)

        self.array = array
        print(f'type of loop_vars ({type(loop_vars)})')
        self.loop_vars = loop_vars
        self.indices = indices

        self.min_array_indices = None
        self.calculate_min_array_indices()
        self.dep_ranges = None
        self.calculate_dep_ranges()
        self.cuts = None
        self.calculate_cuts()

    def has_common_loop_vars(self, loop_vars):
        # dummy variable should not be used to check
        # otherwise for A[i][j] = A[1][2], then i and j will
        # be in the same coupled group, but it shouldn't
        me = self.loop_vars.copy()
        me.discard('dummy')
        them = loop_vars.copy()
        them.discard('dummy')
        return len(me.intersection(them)) > 0

    def calculate_cuts(self):
        cuts = set()
        loop_var = next(iter(self.loop_vars))
        min_val = self.min_array_indices[loop_var]
        max_val = 500
        cuts.add(min_val)
        cuts.add(max_val)
        for dep_range in self.dep_ranges.all_dep_ranges():
            if dep_range.loop_carried:
                cuts.update(dep_range.loop_carried)
            if dep_range.loop_independent:
                cuts.update(dep_range.loop_independent)
        sorted_cuts = sorted(list(cuts))
        self.cuts = sorted_cuts
        

    def calculate_min_array_indices(self):
        min_array_indices = {}
        loop_var = next(iter(self.loop_vars))
        min_array_indices[loop_var] = 0
        for index in self.indices:
            # TODO: generalize to find minimum_indices per group
            min_array_indices[loop_var] = find_minimum_valid_index(min_array_indices[loop_var],
                                                                   index)
        self.min_array_indices = min_array_indices

    def calculate_dep_ranges(self):
        dep_ranges = DepRangeMap()
        loop_var = next(iter(self.loop_vars))
        min_val = self.min_array_indices[loop_var]
        max_val = 500
        for index1 in self.indices:
            for index2 in self.indices:
                if index1 == index2:
                    continue
                dep_range = DepRange(min_val, max_val, index1, index2)
                dep_ranges.set_dep_range(index1, index2, dep_range)
        self.dep_ranges = dep_ranges

    def pprint(self):
        lines = []
        lines.append(f'Array: {self.array}')
        lines.append(f'Loop vars: {self.loop_vars}')
        lines.append(f'Indices: {[i.pprint() for i in self.indices]}')
        lines.append(self.dep_ranges.pprint())
        return '\n'.join(lines)

def merge_coupled_groups(group1, group2):
    logger.info(group1.array + ' ' + group2.array)
    assert(group1.array == group2.array)

    loop_vars = set()
    loop_vars.update(group1.loop_vars)
    loop_vars.update(group2.loop_vars)
    indices = set()
    indices.update(group1.indices)
    indices.update(group2.indices)
    return CoupledGroup(group1.array, loop_vars, indices)

def partition(accesses):
    groups = []
    # partition the accesses naively first
    for access1, access2 in all_pairs(accesses):
        if not is_same_memory(access1, access2):
            continue
        array = access1.var
        assert(len(access1.indices) == len(access2.indices))
        for index1, index2 in zip(access1.indices, access2.indices):
            loop_vars = set()
            if index1.var:
                loop_vars.add(index1.var)
            if index2.var:
                loop_vars.add(index2.var)
            group = CoupledGroup(array, loop_vars, set([index1, index2]))
            groups.append(group)
    if len(groups) < 2:
        return groups
    changed = True
    while changed:
        changed = False
        new_group = []
        for group1, group2 in all_pairs(groups):
            if group1.array == group2.array and \
               group1.has_common_loop_vars(group2.loop_vars):
                new_group.append(merge_coupled_groups(group1, group2))
                changed = True
        if changed:
            group = new_group
    return groups
