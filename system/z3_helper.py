from z3 import Solver, Ints, unsat, Optimize, sat
from random import choice

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

def find_minimum_index(min_val, use):
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

def find_possible_range(min_val, max_val, lesser, greater):
    # find if it's solvable, then find min and max of the new range
    assert(lesser.var == greater.var)
    # i is the index variable and s* are the subscripts
    # expect s1 < s2
    i1, i2, s1, s2 = Ints('i1 i2 s1 s2')

    i1_min_constraint = min_val <= i1
    i1_max_constraint = i1 <= max_val
    i2_min_constraint = min_val <= i2
    i2_max_constraint = i2 <= max_val

    s1 = i1 * lesser.coeff + lesser.offset
    s2 = i2 * greater.coeff + greater.offset
    s1_min_constraint = s1 >= 0
    s2_min_constraint = s2 >= 0

    # dependence constraint
    same_mem = s1 == s2

    def dep_exists(min_val, max_val):
        i1_min_constraint = min_val <= i1
        i1_max_constraint = i1 <= max_val
        i2_min_constraint = min_val <= i2
        i2_max_constraint = i2 <= max_val

        dep_existence_solver = Solver()
        dep_existence_solver.add(
            i1_min_constraint,
            i1_max_constraint,
            i2_min_constraint,
            i2_max_constraint,
            s1_min_constraint,
            s2_min_constraint,
            same_mem
        )

        # check that i2 can happen later
        status = dep_existence_solver.check(i2 > i1)
        if status == sat:
            return True
        elif status == unsat:
            return False
        else:
            raise RuntimeError(f'Unexpected status {status}')

    if not dep_exists(min_val, max_val):
        return None
    
    # find min and max for new range

    # at this point there is a dependency from iteration i1 -> i2
    # but we'd also like it that given the range [i_min, i_max]
    # that there is no dependency from i2 -> i1 as well

    # exclude all ranges where i1 > i2
    min_exclude = None

    # find min
    find_min = Optimize()
    find_min.assert_exprs(
        i1_min_constraint,
        i1_max_constraint,
        i2_min_constraint,
        i2_max_constraint,
        s1_min_constraint,
        s2_min_constraint,
        same_mem,
        i1 >= i2
    ) 
    find_min.minimize(i1)
    status = find_min.check()
    if status == unsat:
        # if i1 is never greater than i2, we're good
        return [min_val, max_val]
    elif status == sat:
        min_exclude = find_min.model().eval(i1).as_long()
    else:
        raise RuntimeError(f'Find min got status {status}')

    # find max
    max_exclude = None
    find_max = Optimize()
    find_max.assert_exprs(
        i1_min_constraint,
        i1_max_constraint,
        i2_min_constraint,
        i2_max_constraint,
        s1_min_constraint,
        s2_min_constraint,
        same_mem,
        i1 >= i2
    )
    find_max.maximize(i1)
    status = find_max.check()
    # if it reaches this point, there will have to be a crossing point
    # where i1 >= i2, and we must be able to find the max value for i1
    assert(status == sat)
    max_exclude = find_max.model().eval(i1).as_long()
    print(f'exclude = {[min_exclude, max_exclude]}')
    # calculate
    # [min_val, max_val] - [min_exclude, max_exclude]

    # if the exclude range covers the whole original range, return an empty range
    if min_exclude <= min_val and max_exclude >= max_val:
        return None

    # if there is no intersection at all, return the original range
    if max_exclude < min_val or min_exclude > max_val:
        new_range = [min_val, max_val]
        if dep_exists(*new_range):
            return new_range
        else:
            return None

    # if the over lap is on one side of the original range, do the intersect
    if min_exclude <= min_val and max_exclude < max_val:
        return [max_exclude + 1, max_val]
    if min_exclude > min_val and max_exclude >= max_val:
        return [min_val, min_exclude - 1]

    # If it reaches here, the the exclude range splits the original
    # into two parts. For this case, randomly pick one part
    part1 = [min_val, min_exclude - 1]
    part2 = [max_exclude + 1, max_val]
    if dep_exists(*part1):
        if dep_exists(*part2):
            return choice([part1, part2])
        else:
            return part1
    else:
        if dep_exists(*part2):
            return part2
        else:
            return None
    
def find_range(min_val, max_val, uses):
    for lesser, greater in zip(uses[:-1], uses[1:]):
        # if they're equal then the ranges don't change
        if lesser.coeff == greater.coeff and lesser.offset == greater.offset:
            continue
        print(f'before {[min_val, max_val]}')
        new_range = find_possible_range(min_val, max_val, lesser, greater)
        if not new_range:
            return None
        min_val = new_range[0]
        max_val = new_range[1]
        print(f'after {[min_val, max_val]}')
    return (min_val, max_val)
