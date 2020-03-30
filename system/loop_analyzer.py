from abstract_ast import get_accesses
from z3 import Solver, Ints, unsat, Optimize, sat
from random import shuffle

def find_possible_range(current_range, lesser, greater):
    # find if it's solvable, then find min and max of the new range
    assert(lesser.var == greater.var)
    # i is the index variable and s* are the subscripts
    # expect s1 < s2
    i, s1, s2 = Ints('i s1 s2')
    solver = Solver()

    i_min_constraint = current_range[0] <= i
    i_max_constraint = i <= current_range[1]
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

def inner_shuffle(list_of_list):
    for l in list_of_list:
        shuffle(l)

def find_range(min_val, max_val, uses):
    for lesser, greater in zip(uses[:-1], uses[1:]):
        # if they're equal then the ranges don't change
        if lesser.coeff == greater.coeff and lesser.offset == greater.offset:
            continue
        new_range = find_possible_range([min_val, max_val], lesser, greater)
        if not new_range:
            return None
        min_val = new_range[0]
        max_val = new_range[1]
    return (min_val, max_val)

def find_range_backup(all_uses):
    min_val = 0
    max_val = 2 ** 16
    for uses in all_uses:
        # shuffle(uses)
        for lesser, greater in zip(uses[:-1], uses[1:]):
            # if they're equal then the ranges don't change
            if lesser.coeff == greater.coeff and lesser.offset == greater.offset:
                continue
            new_range = find_possible_range([min_val, max_val], lesser, greater)
            if not new_range:
                return None
            min_val = new_range[0]
            max_val = new_range[1]
    return [min_val, max_val]

# def group_indices(grouped_accesses):
#     grouped_indices = {}
#     for _, indices in grouped_accesses.items():
#         if not indices:
#             continue
#         loop_var = indices[0].var
#         if not loop_var in grouped_indices:
#             grouped_indices[loop_var] = []
#         grouped_indices[loop_var].append(indices)
#     return grouped_indices

# group by loop_var -> (array, dimension) -> [index]
def group_accesses(accesses):
    grouped_accesses = {}
    for access in accesses:
        array = access.var
        for dimension, index in enumerate(access.indices):
            key = (array, dimension)
            if not key in grouped_accesses:
                grouped_accesses[key] = []
            grouped_accesses[key].append(index)
    return grouped_accesses

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
    def __init__(self, loop_var_analysis, sorted_indices):
        self.loop_var_analysis = loop_var_analysis
        self.sorted_indices = sorted_indices
    def debug(self):
        lines = [
            self.loop_var_analysis.debug(),
            self.sorted_indices.debug()
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
        for (array, dimension), sorted_indices in self.indices.items():
            lines.append(f'{array}[{dimension}] => {sorted_indices.debug()}')
        return '\n'.join(lines)

def analyze_loop(loop):
    # array -> dimension -> indices
    # grouped_accesses = group_accesses(get_accesses(loop))
    # for (array, dimension), indices in grouped_accesses.items():
    #     print(f'{array}[{dimension}] = {[i.pprint() for i in indices]}')

    loop_var_analysis = LoopVarAnalysis()
    index_analysis = IndexAnalysis()
    grouped_indices = group_indices(get_accesses(loop))
    for loop_var in loop.loop_vars:
        for attempt in range(1, 10):
            min_val = 0
            max_val = 2 ** 16
            failed = False
            for (array, dimension), indices in grouped_indices[loop_var].items():
                shuffle(indices)
                new_range = find_range(min_val, max_val, indices)
                if not new_range:
                    failed = True
                    break
                min_val = new_range[0]
                max_val = new_range[1]
            if failed:
                continue
            loop_var_analysis.set_range(loop_var, min_val, max_val)
            break
    for loop_var, indices_map in grouped_indices.items():
        for (array, dimension), sorted_indices in indices_map.items():
            index_analysis.set_sorted_indices(array, dimension, SortedIndices(sorted_indices))
    loop_analysis = LoopAnalysis(loop_var_analysis, index_analysis)
    return loop_analysis
