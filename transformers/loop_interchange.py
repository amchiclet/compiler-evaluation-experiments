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
    def transform(self, program, var_map=None):
        if not var_map:
            var_map = VariableMap()

        print('begin analyze_dependence')
        dependence_graph = analyze_dependence(program, var_map)
        print('end analyze_dependence')
        logger.info('heyyy')
        dependence_graph.debug()

        def is_permutable(loop, new_order):
            for dv in iterate_direction_vectors(dependence_graph, loop):
                cloned = list(dv)
                reorder(new_order, cloned)
                if is_positive(cloned):
                    return False
            return True

        # Assuming that the whole space is less than 1000
        # a brute-force method should be fine
        # There is always at least one valid permutation
        # which is keeping the original loop.
        loops = get_loops(program)
        while True:
            print('next!')
            permutations = []
            is_valid = True
            for loop in loops.values():
                permutation = list(range(len(loop.loop_vars)))
                random.shuffle(permutation)
                permutations.append(permutation)
            for loop, permutation in zip(loops.values(), permutations):
                if not is_permutable(loop, permutation):
                    is_valid = False
                    break
            if is_valid:
                clone = program.clone()
                cloned_loops = get_loops(clone)
                for loop, permutation in zip(cloned_loops.values(), permutations):
                    reorder(permutation, loop.loop_vars)
                logger.info(f'valid clone\n'
                            f'{permutations}\n'
                            f'{clone.pprint()}')
                yield clone
