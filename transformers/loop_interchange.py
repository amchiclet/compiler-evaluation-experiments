from dependence_analysis import analyze_dependence
from variable_map import VariableMap
import random

def swap(i, j, l):
    t = l[i]
    l[i] = l[j]
    l[j] = t

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

                i1, i2 = random.sample(range(len(loop.loop_vars)), 2)
                if is_interchangable(i1, i2):
                    clone = program.clone()
                    swap(i1, i2, clone.loops[loop_i].loop_vars)
                    yield clone
                    break
                    
