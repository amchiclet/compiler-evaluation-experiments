from abstract_ast import get_accesses
from z3 import Solver, Ints, unsat, Optimize, sat
from random import shuffle

def find_possible_index(min_val, max_val, index):
    # give a current range of i
    # give an index that uses i
    # find the min and max int that covers all the index

    i, s = Ints('i s')
    solver = Solver()

    i_min_constraint = min_val <= i
    i_max_constraint = i <= max_val
    s_constraint = s == i * index.coeff + index.offset

    # find min
    find_min = Optimize()
    find_min.assert_exprs(i_min_constraint,
                          i_max_constraint,
                          s_constraint)
    find_min.minimize(s)
    assert(sat == find_min.check())
    min_val = find_min.model().eval(s)

    # find max
    find_max = Optimize()
    find_max.assert_exprs(i_min_constraint,
                          i_max_constraint,
                          s_constraint)
    find_max.maximize(s)
    assert(sat == find_max.check())
    max_val = find_max.model().eval(s)
    return [min_val.as_long(), max_val.as_long()]
    
def find_possible_range(min_val, max_val, lesser, greater):
    # find if it's solvable, then find min and max of the new range
    assert(lesser.var == greater.var)
    # i is the index variable and s* are the subscripts
    # expect s1 < s2
    i, s1, s2 = Ints('i s1 s2')
    solver = Solver()

    i_min_constraint = min_val <= i
    i_max_constraint = i <= max_val
    s1_constraint = s1 == i * lesser.coeff + lesser.offset
    s2_constraint = s2 == i * greater.coeff + greater.offset
    s1_min_constraint = s1 >= 0
    s2_min_constraint = s2 >= 0

    solver.add(i_min_constraint,
               i_max_constraint,
               s1_constraint,
               s2_constraint,
               s1_min_constraint,
               s2_min_constraint)

    status = solver.check(s1 < s2)
    if status == unsat:
        return None

    # find min and max for new range

    # find min
    find_min = Optimize()
    find_min.assert_exprs(i_min_constraint,
                          i_max_constraint,
                          s1_constraint,
                          s2_constraint,
                          s1_min_constraint,
                          s2_min_constraint,
                          s1 < s2)
    find_min.minimize(i)
    assert(sat == find_min.check())
    new_min = find_min.model().eval(i)

    # find max
    find_max = Optimize()
    find_max.assert_exprs(i_min_constraint,
                          i_max_constraint,
                          s1_constraint,
                          s2_constraint,
                          s1_min_constraint,
                          s2_min_constraint,
                          s1 < s2)
    find_max.maximize(i)
    assert(sat == find_max.check())
    new_max = find_max.model().eval(i)
    return [new_min, new_max]

def find_range(min_val, max_val, uses):
    for lesser, greater in zip(uses[:-1], uses[1:]):
        # if they're equal then the ranges don't change
        if lesser.coeff == greater.coeff and lesser.offset == greater.offset:
            continue
        new_range = find_possible_range(min_val, max_val, lesser, greater)
        if not new_range:
            return None
        min_val = new_range[0]
        max_val = new_range[1]
    return (min_val, max_val)

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
    def __init__(self, loop_var_analysis, index_analysis, array_analysis):
        self.loop_var_analysis = loop_var_analysis
        self.index_analysis = index_analysis
        self.array_analysis = array_analysis
    def debug(self):
        lines = [
            self.loop_var_analysis.debug(),
            self.index_analysis.debug(),
            self.array_analysis.debug()
        ]
        return '\n'.join(lines)

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

class SortedIndices:
    def __init__(self, sorted_indices):
        self.sorted_indices = sorted_indices
    def index(self, target):
        for i, index in enumerate(self.sorted_indices):
            if index.is_syntactically_equal(target):
                return i
        raise RuntimeError('Index not found')
    def is_sorted(self, lesser, greater):
        return self.index(lesser) < self.index(greater)
    def debug(self):
        return f'{[i.pprint() for i in self.sorted_indices]}'

class IndexAnalysis:
    def __init__(self):
        self.indices = {}
    def set_sorted_indices(self, array, dimension, sorted_indices):
        self.indices[(array, dimension)] = sorted_indices
    def get_sorted_indices(self, array, dimension):
        return self.indices[(array, dimension)]
    def debug(self):
        lines = []
        lines.append('Sorted indices:')
        for (array, dimension), sorted_indices in self.indices.items():
            lines.append(f'  {array}[{dimension}] => {sorted_indices.debug()}')
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
    index_analysis = IndexAnalysis()
    grouped_indices = group_indices(get_accesses(loop))

    for loop_var in loop.loop_vars:
        failed_outer = True
        # calculate max ways to shuffle the indices and order them
        space_size = 1
        for indices in grouped_indices[loop_var].values():
            space_size *= factorial(len(indices))

        for _ in range(space_size):
            min_val = 0
            max_val = 500
            failed_inner = False
            for (array, dimension), indices in grouped_indices[loop_var].items():
                shuffle(indices)
                new_range = find_range(min_val, max_val, indices)
                if not new_range:
                    failed_inner = True
                    break
                min_val = new_range[0]
                max_val = new_range[1]
            if failed_inner:
                continue
            loop_var_analysis.set_range(loop_var, min_val, max_val)
            failed_outer = False
            break
        if failed_outer:
            return None
    for loop_var, indices_map in grouped_indices.items():
        for (array, dimension), sorted_indices in indices_map.items():
            index_analysis.set_sorted_indices(array, dimension, SortedIndices(sorted_indices))

    array_analysis = ArrayAnalysis()
    for loop_var, indices_map in grouped_indices.items():
        for (array, dimension), indices in indices_map.items():
            min_loop_var_val = loop_var_analysis.min_val(loop_var)
            max_loop_var_val = loop_var_analysis.max_val(loop_var)
            min_index = 500
            max_index = 0
            for index in indices:
                new_min_index, new_max_index = find_possible_index(
                    min_loop_var_val,
                    max_loop_var_val,
                    index)
                if new_min_index < min_index:
                    min_index = new_min_index
                if new_max_index > max_index:
                    max_index = new_max_index
            array_analysis.set_range(array, dimension, min_index, max_index)
    loop_analysis = LoopAnalysis(loop_var_analysis, index_analysis, array_analysis)
    return loop_analysis

max_tries = 5
def analyze_loops(program):
    all_analysis = {}
    for loop in program.loops:
        for _ in range(max_tries):
            analysis = analyze_loop(loop)
            if analysis:
                all_analysis[loop.node_id] = analysis
                break
    return all_analysis
