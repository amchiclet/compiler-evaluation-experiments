from z3 import Solver, Ints, unsat, Optimize, sat, Or

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
