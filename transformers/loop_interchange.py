from dependence_analysis import analyze_dependence
from variable_map import VariableMap
import random
from sampler import Sampler
from math import factorial
from loguru import logger
from abstract_ast import get_loops

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

def gather_loop_shapes(program):
    shapes = {}
    for loop in program.loops:
        shapes[loop.node_id] = len(loop.loop_vars)
    return shapes

# This is for calculating permutations
def calculate_strides(n_dimensions):
    strides = []
    prev = 1
    for d in range(n_dimensions):
        size = prev * (d+1)
        prev = size
        strides.append(size)
    strides.reverse()
    return strides

# def get_loop_ids(node):
#     if isinstance(node, AbstractLoop):
#         loop_ids = [node.node_id]
#         for stmt in node.body:
#             loop_ids += get_loop_ids(stmt)
#         return loop_ids
#     elif isinstance(node, Program):
#         loop_ids = []
#         for loop in node.loops:
#             loop_ids += get_loop_ids(loop)
#         return loop_ids
#     elif isinstance(node, Assignment):
#         return []
#     else:
#         raise RuntimeError('get_loop_ids: Unhandled type of node ' + str(type(node)))

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

# def to_id(p):
#     n_dimensions = len(p)
#     remaining = list(range(n_dimensions))
#     strides = calculate_strides(n_dimensions)
#     result = 0
#     for i in range(n_dimensions-1):
#         value = remaining.index(p[i])
#         del remaining[value]
#         result += strides[i+1] * value
#     return result

class LoopInterchangeV2:
    def __init__(self, program):
        self.program = program
        self.ordered_loop_ids = sorted(get_loops(program).keys())
        # self.ordered_loop_ids = get_loop_ids(program)
        self.loop_shapes = gather_loop_shapes(program)

        self.ordered_strides = [1]
        current_stride = 1
        for loop_id in self.ordered_loop_ids[:-1]:
            size = factorial(self.loop_shapes[loop_id])
            current_stride = current_stride * size
            self.ordered_strides.append(current_stride)
        self.ordered_strides.reverse()

        self.n_total_samples = prod([factorial(d) for d in self.loop_shapes.values()])
        logger.info(f'total samples = {self.n_total_samples}')
        self.sampler = Sampler(self.n_total_samples)

    # def to_total_id(self, permutations):
    #     result = 0
    #     for size, permutation in zip(self.total_strides, permutations):
    #         result += size * to_id(permutation)
    #     return result

    def to_permutations(self, sample_id):
        permutations = {}
        for loop_id, stride in zip(self.ordered_loop_ids, self.ordered_strides):
            permutation_id = sample_id // stride
            n_dimensions = self.loop_shapes[loop_id]
            permutation = to_permutation(permutation_id, n_dimensions)
            permutations[loop_id] = permutation
            sample_id = sample_id % stride
        return permutations

    def transform(self, program, var_map=None):
        if not var_map:
            var_map = VariableMap()

        dependence_graph = analyze_dependence(program, var_map)
        logger.info('heyyy')
        dependence_graph.debug()

        def is_permutable(loop, new_order):
            for dv in iterate_direction_vectors(dependence_graph, loop):
                cloned = list(dv)
                reorder(new_order, cloned)
                if is_positive(cloned):
                    return False
            return True

        loops = get_loops(program)
        for sample_id in self.sampler.iterate():
            # Sample id 0 is the original program, skip it
            if sample_id == 0:
                continue
            permutations = self.to_permutations(sample_id)

            is_valid = True
            for loop_node_id, loop in loops.items():
                permutation = permutations[loop_node_id]
                if not is_permutable(loop, permutation):
                    is_valid = False
                    break
            if is_valid:
                clone = program.clone()
                for loop_node_id, loop in get_loops(clone).items():
                    permutation = permutations[loop_node_id]
                    reorder(permutation, loop.loop_vars)
                logger.info('valid clone\n'
                            f'{clone.pprint()}')
                yield clone
