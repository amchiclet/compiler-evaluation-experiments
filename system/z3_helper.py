from z3 import Solver, Ints, unsat, Optimize, sat, Or
from random import choice

# assuming i1 < i2
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
            assert(index1.var == index2.var)

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
        status = solver.check(i1 == i2)
        if status == sat:
            # range where i1 == i2
            new_constraints = constraints + [i1 == i2]
            min_max_i1 = find_min_max(new_constraints, i1)
            self.loop_independent = min_max_i1
        else:
            assert(status == unsat)
            self.loop_independent = None

        # check for loop carried from index1 to index2
        # it's only loop carried when it's not loop independent
        if self.loop_independent:
            solver.add(Or(i1 < self.loop_independent[0],
                          i1 >= self.loop_independent[1]))
            solver.add(Or(i2 < self.loop_independent[0],
                          i2 >= self.loop_independent[1]))

        status = solver.check(i1 < i2)

        if status == sat:
            # print('finding loop-carried')
            # range where i1 < i2
            new_constraints = constraints + [i1 < i2]
            min_max_i1 = find_min_max(new_constraints, i1)
            min_max_i2 = find_min_max(new_constraints, i2)
            # print(min_max_i1)
            # print(min_max_i2)
            # print(solver.check(i1 == min_max_i1[0]))
            # print(solver.model().eval(i1),
            #       solver.model().eval(i2),
            #       solver.model().eval(s1),
            #       solver.model().eval(s2))
            self.loop_carried = [min(min_max_i1[0], min_max_i1[0]),
                                 max(min_max_i2[1], min_max_i2[1])]
            # print(self.loop_carried)
        else:
            assert(status == unsat)
            self.loop_carried = None

    def is_independent(self):
        return not self.loop_carried and not self.loop_independent

    def pprint(self):
        return (f'\t{self.index1.pprint()} -> {self.index2.pprint()}\n'
                f'\tLoop-carried({self.loop_carried})\n'
                f'\tLoop-independent({self.loop_independent})')

def find_minimum_valid_index(min_val, use):
    i, = Ints('i')
    solver = Solver()

    i_abs_min_constraint = min_val <= i
    i_min_constraint = i * use.coeff + use.offset >= 0
    
    # find min
    find_min = Optimize()
    find_min.assert_exprs(i_abs_min_constraint,
                          i_min_constraint)
    find_min.minimize(i)
    assert(sat == find_min.check())
    return find_min.model().eval(i).as_long()

def find_min_max_range(min_val, max_val, index):
    # give a current range of i
    # give an index that uses i
    # find the min and max int that covers all the index

    i, s = Ints('i s')
    solver = Solver()

    i_min_constraint = min_val <= i
    i_max_constraint = i < max_val
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
