from dependence_analysis import analyze_dependence
from variable_map import VariableMap
import random
from sampler import Sampler
from math import factorial
from loguru import logger

def swap(i, j, l):
    t = l[i]
    l[i] = l[j]
    l[j] = t

def reorder(new_order, l):
    l[:] = [l[i] for i in new_order]

def is_positive(dv):
    for d in dv:
        if d == '>':
            return True
        if d == '<':
            return False
    return False

def iterate_direction_vectors(dependency_graph, loop):
    for deps in dependency_graph.iterate_dependences_among(loop.body):
        for dep in deps:
            yield dep.direction_vector

class LoopInterchange:
    def __init__(self):
        self.batch_size = 1
        self.attempts_per_mutation = 10
    def transform(self, program, var_map=None):
        if not var_map:
            var_map = VariableMap()
        assert(len(program.loops) == 1)
        dependence_graph = analyze_dependence(program.loops[0], var_map)
        dependence_graph.debug()

        space = [list(loop.loop_vars) for loop in program.loops]
        for _ in range(self.batch_size):
            for _ in range(self.attempts_per_mutation):
                loop_i = random.sample(range(len(program.loops)), 1)[0]
                loop = program.loops[loop_i]

                def is_interchangable(i, j):
                    for dv in iterate_direction_vectors(dependence_graph, loop):
                        cloned = list(dv)
                        swap(i, j, cloned)
                        if is_positive(cloned):
                            return False
                    return True

                def is_permutable(new_order):
                    for dv in iterate_direction_vectors(dependence_graph, loop):
                        cloned = list(dv)
                        reorder(new_order, cloned)
                        if is_positive(cloned):
                            return False
                    return True

                new_order = list(range(len(loop.loop_vars)))
                random.shuffle(new_order)
                if is_permutable(new_order):
                    clone = program.clone()
                    reorder(new_order, clone.loops[loop_i].loop_vars)
                    yield clone
                    break

                # i1, i2 = random.sample(range(len(loop.loop_vars)), 2)
                # if is_interchangable(i1, i2):
                #     clone = program.clone()
                #     swap(i1, i2, clone.loops[loop_i].loop_vars)
                #     yield clone
                #     break

def prod(l):
    r = 1
    for i in l:
        r *= i
    return r

def calculate_space(program):
    space = []
    for loop in program.loops:
        space.append(len(loop.loop_vars))
    return space

def calculate_strides(n_dimensions):
    strides = []
    prev = 1
    for d in range(n_dimensions):
        size = prev * (d+1)
        prev = size
        strides.append(size)
    strides.reverse()
    return strides

def to_permutation(n, n_dimensions):
    strides = calculate_strides(n_dimensions)
    remaining_order = list(range(n_dimensions))
    order = []
    for i in range(n_dimensions-1):
        dimension_size = strides[i+1]
        which_index = n // dimension_size
        n = n % dimension_size
        value = remaining_order[which_index]
        del remaining_order[which_index]
        order.append(value)
    order.append(remaining_order.pop())
    return order

def to_id(p):
    n_dimensions = len(p)
    remaining = list(range(n_dimensions))
    strides = calculate_strides(n_dimensions)
    result = 0
    for i in range(n_dimensions-1):
        value = remaining.index(p[i])
        del remaining[value]
        result += strides[i+1] * value
    return result

class LoopInterchangeV2:
    def __init__(self, program):
        self.program = program
        self.n_loops = len(program.loops)
        self.space = calculate_space(program)

        self.strides = [1]
        new_size = 1
        for i in range(len(program.loops) - 2, -1, -1):
            size = factorial(self.space[i])
            new_size = new_size * size
            self.strides.append(new_size)
        self.strides.reverse()

        self.n_total_samples = prod([factorial(d) for d in self.space])
        logger.info(f'total samples = {self.n_total_samples}')
        self.sampler = Sampler(self.n_total_samples)

    def to_id(self, permutations):
        result = 0
        for size, permutation in zip(self.strides, permutations):
            result += size * to_id(permutation)
        return result

    def to_permutations(self, sample_id):
        permutations = []
        for stride, n_dimensions in zip(self.strides, self.space):
            permutation_id = sample_id // stride
            permutation = to_permutation(permutation_id, n_dimensions)
            permutations.append(permutation)
            sample_id = sample_id % stride
        return permutations

    def transform(self, program, var_map=None):
        if not var_map:
            var_map = VariableMap()

        dependence_graph = analyze_dependence(program, var_map)
        dependence_graph.debug()

        ppps = []
        for sample_id in self.sampler.iterate():
            # Sample id 0 is the original program, skip it
            if sample_id == 0:
                continue
            permutations = self.to_permutations(sample_id)
            ppps.append(permutations)
            # logger.info(f'{permutations}')

        ppps.sort()
        for ppp in ppps:
            logger.info(ppp)
        logger.info(f'length = {len(ppps)}')
        yield sample_id
        # space = [list(loop.loop_vars) for loop in program.loops]
        # for _ in range(self.batch_size):
        #     for _ in range(self.attempts_per_mutation):
        #         loop_i = random.sample(range(len(program.loops)), 1)[0]
        #         loop = program.loops[loop_i]

        #         def is_permutable(new_order):
        #             for dv in iterate_direction_vectors(dependence_graph, loop):
        #                 cloned = list(dv)
        #                 reorder(new_order, cloned)
        #                 if is_positive(cloned):
        #                     return False
        #             return True

        #         new_order = list(range(len(loop.loop_vars)))
        #         random.shuffle(new_order)
        #         if is_permutable(new_order):
        #             clone = program.clone()
        #             reorder(new_order, clone.loops[loop_i].loop_vars)
        #             yield clone
        #             break
