from loguru import logger

class Dependence:
    def __init__(self, source_ref, sink_ref, direction_vector):
        self.source_ref = source_ref
        self.sink_ref = sink_ref
        self.direction_vector = direction_vector
    def pprint(self):
        stmt1 = self.source_ref.parent_stmt
        stmt2 = self.sink_ref.parent_stmt
        return (f'From: {stmt1.dep_print([self.source_ref])}({self.source_ref.node_id})\n'
                f'To:   {stmt2.dep_print([self.sink_ref])}({self.sink_ref.node_id})\n'
                f'DV:   {self.direction_vector}')

class DependenceGraph:
    def __init__(self):
        self.graph = {}
        self.nodes = {}
    def iterate_dependences_from(self, source):
        for (source_id, _), deps in self.graph.items():
            if source.node_id == source_id:
                yield deps
    def iterate_dependences_to(self, sink):
        for (_, sink_id), deps in self.graph.items():
            if sink.node_id == sink_id:
                yield deps
    def iterate_dependences_among(self, stmts):
        wanted = set([stmt.node_id for stmt in stmts])
        for (source_id, sink_id), deps in self.graph.items():
            if source_id in wanted and sink_id in wanted:
                yield deps
    def iterate_dependences(self):
        return iter(self.graph.values())
    def add(self, source_ref, sink_ref, direction_vector):
        source_id = source_ref.parent_stmt.node_id
        sink_id = sink_ref.parent_stmt.node_id
        key = (source_id, sink_id)
        if not key in self.graph:
            self.graph[key] = []

        existing_deps = self.graph[key]
        for existing_dep in existing_deps:
            if existing_dep.direction_vector == direction_vector:
                return
        dep = Dependence(source_ref, sink_ref, direction_vector)
        self.graph[key].append(dep)

    def debug(self):
        for dep_list in self.graph.values():
            for dep in dep_list:
                logger.debug(dep.pprint())
