from abstract_ast import get_accesses
from random import shuffle, choice
from z3_helper import DepRange, find_minimum_valid_index, find_min_max_range

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
    def __init__(self, loop_var_analysis, array_analysis, dep_map):
        self.loop_var_analysis = loop_var_analysis
        self.array_analysis = array_analysis
        self.dep_map = dep_map
    def debug(self):
        lines = [
            self.loop_var_analysis.debug(),
            self.array_analysis.debug()
        ]
        lines.append(f'Loop range analysis')
        for (loop_var, array, dimension), dep_range_map in self.dep_map.items():
            lines.append(f'{array}[{dimension}] (loop var {loop_var})')
            lines.append(dep_range_map.pprint())
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
    def min_val(self, loop_var):
        return self.analysis[loop_var][0]
    def max_val(self, loop_var):
        return self.analysis[loop_var][1]
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

from math import factorial
def analyze_loop(loop):
    loop_var_analysis = LoopVarAnalysis()
    grouped_indices = group_indices(get_accesses(loop))

    # maps (array, dimension) to another map which
    # maps (index1, index2) to a DepRange
    dep_map = {}

    # find the range of possible loop var
    for loop_var in loop.loop_vars:
        loop_var_cut = set()
        failed_outer = True

        min_array_index = 0
        for indices in grouped_indices[loop_var].values():
            for index in indices:
                min_array_index = find_minimum_valid_index(min_array_index, index)

        min_val = min_array_index
        max_val = 500
        loop_var_cut.add(min_array_index)
        loop_var_cut.add(max_val)
        failed_inner = False
        for (array, dimension), indices in grouped_indices[loop_var].items():
            print(f'Analyzing array {array}[{dimension}]')
            dep_ranges = DepRangeMap()
            for index1 in indices:
                for index2 in indices:
                    print(index1.pprint(), index2.pprint())
                    if index1.is_syntactically_equal(index2):
                        continue
                    dep_range = DepRange(min_val, max_val, index1, index2)
                    print(dep_range.pprint())
                    dep_ranges.set_dep_range(index1, index2, dep_range)
                    if dep_range.loop_carried:
                        loop_var_cut.update(dep_range.loop_carried)
                    if dep_range.loop_independent:
                        loop_var_cut.update(dep_range.loop_independent)
            dep_map[(loop_var, array, dimension)] = dep_ranges

        print(f'loop var {loop_var} has cuts {sorted(list(loop_var_cut))}')
        # find all non-trivial cuts (cuts with length greater than 1)
        sorted_cuts = sorted(list(loop_var_cut))
        non_trivial_ranges = []
        for i in range(len(sorted_cuts) - 1):
            if sorted_cuts[i+1] - sorted_cuts[i] > 1:
                non_trivial_ranges.append(tuple(sorted_cuts[i:i+2]))
        loop_var_range = choice(non_trivial_ranges)
        # print(f'loop var {loop_var} has range {loop_var_range}')
        loop_var_analysis.set_range(loop_var, *loop_var_range)

    # figure out array sizes
    array_analysis = ArrayAnalysis()
    for loop_var, indices_map in grouped_indices.items():
        for (array, dimension), indices in indices_map.items():
            min_loop_var_val = loop_var_analysis.min_val(loop_var)
            max_loop_var_val = loop_var_analysis.max_val(loop_var)
            min_range = 500
            max_range = 0
            for index in indices:
                new_min_range, new_max_range = find_min_max_range(
                    min_loop_var_val,
                    max_loop_var_val,
                    index)
                if new_min_range < min_range:
                    min_range = new_min_range
                if new_max_range > max_range:
                    max_range = new_max_range
            array_analysis.set_range(array, dimension, min_range, max_range)
    loop_analysis = LoopAnalysis(loop_var_analysis, array_analysis, dep_map)
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
