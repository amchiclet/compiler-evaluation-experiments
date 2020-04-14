from abstract_ast import get_accesses
from random import shuffle, choice
from z3_helper import find_min_max_range
from coupled_group import partition
from loguru import logger

def analyze_arrays(accesses, loop_var_analysis):
    array_analysis = ArrayAnalysis()
    for access in accesses:
        array = access.var
        for index in access.indices:
            loop_var = index.var
            min_loop_var_val = loop_var_analysis.min_val(loop_var)
            max_loop_var_val = loop_var_analysis.max_val(loop_var)
            range_min, range_max = find_min_max_range(
                min_loop_var_val,
                max_loop_var_val,
                index)
            array_analysis.update_range(index.array, index.dimension, range_min, range_max)
    return array_analysis

class LoopAnalysis:
    def __init__(self, loop_var_analysis, array_analysis, groups):
        self.loop_var_analysis = loop_var_analysis
        self.array_analysis = array_analysis
        self.groups = groups
    def debug(self):
        lines = [
            self.loop_var_analysis.pprint(),
            self.array_analysis.pprint()
        ]
        lines.append(f'Loop range analysis')
        for i, group in enumerate(self.groups):
            lines.append(f'Group {i+1}:')
            lines.append(group.pprint())
        return '\n'.join(lines)

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
    def pprint(self):
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
    def pprint(self):
        lines = []
        lines.append('Array index ranges:')
        for (array, dimension), (min_val, max_val) in self.arrays.items():
            lines.append(f'  |{array}[{dimension}]| => [{min_val}..{max_val}]')
        return '\n'.join(lines)

def analyze_loop_vars(groups, loop):
    loop_var_analysis = LoopVarAnalysis()
    for loop_var in loop.loop_vars:
        cuts = set([0, 500])
        for group in groups:
            if group.has_common_loop_vars([loop_var]):
                cuts.update(group.cuts)
        cuts = sorted(list(cuts))
        # # if there are no groups that handle this variable,
        # # it means that its not used
        # # set the range to default
        # if not cuts:
        #     logger.info(f'Could not find a group that handles {group.array}{group.loop_vars}')
        #     loop_var_analysis.set_range(loop_var, 0, 500)
        # else:
        logger.info(f'loop var {loop_var} has cuts {cuts}')
        non_trivial_ranges = []
        for i in range(len(cuts) - 1):
            if cuts[i+1] - cuts[i] > 1:
                non_trivial_ranges.append(tuple(cuts[i:i+2]))
        logger.info(f'Non trivial ranges = {non_trivial_ranges}')
        loop_var_range = choice(non_trivial_ranges)
        loop_var_analysis.set_range(loop_var, *loop_var_range)
    return loop_var_analysis

from math import factorial
def analyze_loop(loop):
    accesses = get_accesses(loop)
    groups = partition(accesses)
    loop_var_analysis = analyze_loop_vars(groups, loop)
    array_analysis = analyze_arrays(accesses, loop_var_analysis)
    loop_analysis = LoopAnalysis(loop_var_analysis, array_analysis, groups)
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
