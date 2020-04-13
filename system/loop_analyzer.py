from abstract_ast import get_accesses, all_pairs, is_same_memory
from random import shuffle, choice
from z3_helper import DepRange, find_minimum_valid_index, find_min_max_range

# A coupled group should include
# array name
# set(loop_vars) that need to be analyzed together
# set(dimensions) that need to be analyzed together
# dimension -> index mappin
class CoupledGroup:
    def __init__(self, array, loop_vars, indices):
        assert(len(loop_vars) <= 1)
        assert(len(indices) > 0)
        expected_dimension = next(iter(indices)).dimension
        for index in indices:
            assert(expected_dimension == index.dimension)

        self.array = array
        self.loop_vars = loop_vars
        self.indices = indices

        self.min_array_indices = None
        self.calculate_min_array_indices()
        self.dep_ranges = None
        self.calculate_dep_ranges()
        self.cuts = None
        self.calculate_cuts()

    def has_common_loop_vars(self, loop_vars):
        return self.loop_vars.intersection(loop_vars)

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
        self.cuts = sorted(list(cuts))

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
                print(index1.pprint(), index2.pprint())
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
    loop_vars = set()
    loop_vars.update(group1.loop_vars)
    loop_vars.update(group2.loop_vars)
    indices = set()
    indices.update(group1.indices)
    indices.update(group2.indices)
    return CoupledGroup(loop_vars, indices)

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
            if group1.has_common_loop_vars(group2.loop_vars):
                new_group.append(merged_coupled_groups(group1, group2))
                changed = True
        if changed:
            group = new_group
    return groups

def analyze_arrays(groups, loop_var_analysis):
    array_analysis = ArrayAnalysis()
    for group in groups:
        loop_var = next(iter(group.loop_vars))
        min_loop_var_val = loop_var_analysis.min_val(loop_var)
        max_loop_var_val = loop_var_analysis.max_val(loop_var)
        for index in group.indices:
            range_min, range_max = find_min_max_range(
                min_loop_var_val,
                max_loop_var_val,
                index)
            array_analysis.update_range(index.array, index.dimension, range_min, range_max)
    return array_analysis

# given A[i][j],
# return loop_var -> (array, dimension) -> [index expression]
def group_indices(accesses):
    outer_map = {}
    for access in accesses:
        array = access.var
        for dimension, index in enumerate(access.indices):
            loop_var = index.var
            if not loop_var in outer_map:
                outer_map[loop_var] = {}
            inner_map = outer_map[loop_var]
            inner_key = (array, dimension)
            if not inner_key in inner_map:
                inner_map[inner_key] = []
            inner_map[inner_key].append(index)
    return outer_map

class LoopAnalysis:
    def __init__(self, loop_var_analysis, array_analysis, dep_map, groups):
        self.loop_var_analysis = loop_var_analysis
        self.array_analysis = array_analysis
        self.dep_map = dep_map
        self.groups = groups
    def debug(self):
        lines = [
            self.loop_var_analysis.debug(),
            self.array_analysis.debug()
        ]
        lines.append(f'Loop range analysis')
        for (loop_var, array, dimension), dep_range_map in self.dep_map.items():
            lines.append(f'{array}[{dimension}] (loop var {loop_var})')
            lines.append(dep_range_map.pprint())
        for i, group in enumerate(self.groups):
            lines.append(f'Group {i+1}:')
            lines.append(group.pprint())
        return '\n'.join(lines)

def hashed(index1, index2):
    return (index1.var, index1.coeff, index1.offset,
            index2.var, index2.coeff, index2.offset)

def has_overlap(range1, range2):
    return range1[1] > range2[0] and range1[0] < range2[1]

class DepRangeMap:
    def __init__(self):
        # maps hashed(index1, index2) to a DepRange
        self.the_map = {}
    def set_dep_range(self, index1, index2, dep_range):
        hashed_index = hashed(index1, index2)
        self.the_map[hashed_index] = dep_range
    def all_dep_ranges(self):
        return self.the_map.values()
    def pprint(self):
        lines = []
        for dep_range in self.the_map.values():
            lines.append(dep_range.pprint())
        return '\n'.join(lines)

    def check_overlap(self, loop_var_range, i1, i2, attr):
        i1_i2 = hashed(i1, i2)
        if not i1_i2 in self.the_map:
            return False
        dep_range = attr(self.the_map[i1_i2])
        if not dep_range:
            return False
        return has_overlap(loop_var_range, dep_range)

    def is_loop_carried(self, loop_var_range, i1, i2):
        return self.check_overlap(loop_var_range, i1, i2,
                                  lambda x: x.loop_carried)
    def is_loop_independent(self, loop_var_range, i1, i2):
        return self.check_overlap(loop_var_range, i1, i2,
                                  lambda x: x.loop_independent)

class LoopVarAnalysis:
    def __init__(self):
        self.analysis = {}
    def set_range(self, loop_var, min_val, max_val):
        self.analysis[loop_var] = (min_val, max_val)
    def min_val(self, loop_var, default=0):
        if loop_var in self.analysis:
            return self.analysis[loop_var][0]
        else:
            return default
    def max_val(self, loop_var, default=500):
        if loop_var in self.analysis:
            return self.analysis[loop_var][1]
        else:
            return default
    def debug(self):
        lines = []
        lines.append('Loop var ranges:')
        for loop_var, (min_val, max_val) in self.analysis.items():
            lines.append(f'  {loop_var} = [{min_val}..{max_val}]')
        return '\n'.join(lines)

class ArrayAnalysis:
    def __init__(self):
        self.arrays = {}
    def set_range(self, array, dimension, min_index, max_index):
        self.arrays[(array, dimension)] = (min_index, max_index)
    def update_range(self, array, dimension, candidate_min, candidate_max):
        key = (array, dimension)
        if not key in self.arrays:
            self.arrays[key] = [None, None]
        if not self.arrays[key][0] or self.arrays[key][0] > candidate_min:
            self.arrays[key][0] = candidate_min
        if not self.arrays[key][1] or self.arrays[key][1] < candidate_max:
            self.arrays[key][1] = candidate_max
    def min_index(self, array, dimension):
        return self.arrays[(array, dimension)][0]
    def max_index(self, array, dimension):
        return self.arrays[(array, dimension)][1]
    def debug(self):
        lines = []
        lines.append('Array index ranges:')
        for (array, dimension), (min_val, max_val) in self.arrays.items():
            lines.append(f'  |{array}[{dimension}]| => [{min_val}..{max_val}]')
        return '\n'.join(lines)

def analyze_loop_vars(groups, loop):
    loop_var_analysis = LoopVarAnalysis()
    for loop_var in loop.loop_vars:
        cuts = None
        for group in groups:
            print(group.pprint())
            if group.has_common_loop_vars([loop_var]):
                cuts = group.cuts
                break
        # if there are no groups that handle this variable,
        # it means that its not used
        # set the range to default
        if not cuts:
            loop_var_analysis.set_range(loop_var, 0, 500)
        else:
            print(f'loop var {loop_var} has cuts {cuts}')
            non_trivial_ranges = []
            for i in range(len(group.cuts) - 1):
                if group.cuts[i+1] - group.cuts[i] > 1:
                    non_trivial_ranges.append(tuple(group.cuts[i:i+2]))
            loop_var_range = choice(non_trivial_ranges)
            print(loop_var_range)
            loop_var_analysis.set_range(loop_var, *loop_var_range)
    return loop_var_analysis

from math import factorial
def analyze_loop(loop):
    accesses = get_accesses(loop)
    groups = partition(accesses)

    # grouped_indices = group_indices(accesses)

    # # maps (array, dimension) to another map which
    # # maps (index1, index2) to a DepRange
    # dep_map = {}

    # # find the range of possible loop var
    # for loop_var in loop.loop_vars:
    #     failed_outer = True

    #     min_array_index = 0
    #     for indices in grouped_indices[loop_var].values():
    #         for index in indices:
    #             min_array_index = find_minimum_valid_index(min_array_index, index)

    #     min_val = min_array_index
    #     max_val = 500
    #     failed_inner = False
    #     for (array, dimension), indices in grouped_indices[loop_var].items():
    #         print(f'Analyzing array {array}[{dimension}]')
    #         dep_ranges = DepRangeMap()
    #         for index1 in indices:
    #             for index2 in indices:
    #                 print(index1.pprint(), index2.pprint())
    #                 if index1 == index2:
    #                     continue
    #                 dep_range = DepRange(min_val, max_val, index1, index2)
    #                 print(dep_range.pprint())
    #                 dep_ranges.set_dep_range(index1, index2, dep_range)
    #         dep_map[(loop_var, array, dimension)] = dep_ranges

    loop_var_analysis = analyze_loop_vars(groups, loop)
    array_analysis = analyze_arrays(groups, loop_var_analysis)
    dep_map = {}
    loop_analysis = LoopAnalysis(loop_var_analysis, array_analysis, dep_map, groups)
    return loop_analysis

max_tries = 1
def analyze_loops(program):
    all_analysis = {}
    for loop in program.loops:
        for _ in range(max_tries):
            analysis = analyze_loop(loop)
            if analysis:
                all_analysis[loop.node_id] = analysis
                break
    return all_analysis
