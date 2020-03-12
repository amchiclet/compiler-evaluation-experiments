# Anything related to dependence goes here

class Dependence:
    def __init__(self, loop_carried=None):
        self.loop_carried = loop_carried if loop_carried else []
    def is_loop_carried(self):
        return len(self.loop_carried) > 0

class DependenceGraph:
    def __init__(self):
        self.dep_map = {}
    def add(self, s1, s2, loop_carried=None):
        dep_pair = (s1, s2)
        if not dep_pair in self.dep_map:
            self.dep_map[key] = []
        self.dep_map[key].append(Dependence(loop_carried))
    def has_dependence(self, s1, s2):
        return (s1, s2) in self.dep_map
    def get_dependence(self, s1, s2):
        return self.dep_map[(s1, s2)]

from abstract_ast import Assignment, Access, AbstractIndex, AbstractLoop, BinOp, Program

def analyze_dependence(program):
    pass

def is_valid(dep_graph_before, dep_graph_after):
    # TODO: implement
    pass
