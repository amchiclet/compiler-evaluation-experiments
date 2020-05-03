from z3 import Solver, Ints, unsat, Optimize, sat, Or
from z3_helper import find_min_max
from loguru import logger

def hashed(index1, index2):
    return (index1.var, index1.coeff, index1.offset,
            index2.var, index2.coeff, index2.offset)

def has_overlap(range1, range2):
    logger.debug(f'Checking overlap: {range1} vs {range2}')
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
            logger.debug(f'Not found {i1_i2}')
            return False
        dep_range = attr(self.the_map[i1_i2])
        if not dep_range:
            logger.debug(f'Not found dep range for {i1_i2}')
            return False
        return has_overlap(loop_var_range, dep_range)

    def is_loop_carried(self, loop_var_range, i1, i2):
        return self.check_overlap(loop_var_range, i1, i2,
                                  lambda x: x.loop_carried)
    def is_loop_independent(self, loop_var_range, i1, i2):
        return self.check_overlap(loop_var_range, i1, i2,
                                  lambda x: x.loop_independent)

# TODO: move the z3 stuff into functions and move this class to somewhere else
class DepRange:
    def __init__(self, min_i, max_i, index1, index2):
        # finds the range of i such that there is a dependence from index1 to index2
        # returns a dep range instance
        self.index1 = index1
        self.index2 = index2
        self.min_i = min_i
        self.max_i = max_i

        if index1.var and index2.var:
            assert(index1.var == index2.var or index1.coeff == 0 or index2.coeff == 0)

        # i is the index variable and s* are the subscripts
        # expect s1 < s2
        i1, i2, s1, s2 = Ints('i1 i2 s1 s2')

        i1_min_constraint = min_i <= i1
        i1_max_constraint = i1 < max_i
        i2_min_constraint = min_i <= i2
        i2_max_constraint = i2 < max_i

        s1 = i1 * index1.coeff + index1.offset
        s2 = i2 * index2.coeff + index2.offset
        s1_min_constraint = s1 >= 0
        s2_min_constraint = s2 >= 0

        # dependence constraint
        same_mem = s1 == s2

        constraints = [
            i1_min_constraint,
            i1_max_constraint,
            i2_min_constraint,
            i2_max_constraint,
            s1_min_constraint,
            s2_min_constraint,
            same_mem
        ]
        solver = Solver()
        solver.add(constraints)

        # check for loop independent dependence
        self.loop_independent = None
        if index1.parent_stmt != index2.parent_stmt:
            status = solver.check(i1 == i2)
            if status == sat:
                # range where i1 == i2
                new_constraints = constraints + [i1 == i2]
                min_max_i1 = find_min_max(new_constraints, i1)
                self.loop_independent = min_max_i1
            else:
                assert(status == unsat)

        # check for loop carried from index1 to index2
        # it's only loop carried when it's not loop independent
        # if self.loop_independent:
        #     solver.add(Or(i1 < self.loop_independent[0],
        #                   i1 >= self.loop_independent[1]))
        #     solver.add(Or(i2 < self.loop_independent[0],
        #                   i2 >= self.loop_independent[1]))

        status = solver.check(i1 < i2)

        if status == sat:
            # print('finding loop-carried')
            # range where i1 < i2
            new_constraints = constraints + [i1 < i2]
            min_max_i1 = find_min_max(new_constraints, i1)
            min_max_i2 = find_min_max(new_constraints, i2)
            self.loop_carried = [min(min_max_i1[0], min_max_i1[0]),
                                 max(min_max_i2[1], min_max_i2[1])]
        else:
            assert(status == unsat)
            self.loop_carried = None

    def is_independent(self):
        return not self.loop_carried and not self.loop_independent

    def pprint(self):
        return (f'\t{self.index1.pprint()} -> {self.index2.pprint()}\n'
                f'\tLoop-carried({self.loop_carried})\n'
                f'\tLoop-independent({self.loop_independent})')
