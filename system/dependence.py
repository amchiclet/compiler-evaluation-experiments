# Anything related to dependence goes here

# Each element of loop_carried holds one of the following values:
# (1) <
# (2) >
# (3) =
# (4) ?
class Dependence:
    def __init__(self, loop_carried=None):
        self.loop_carried = loop_carried if loop_carried else []
    def is_loop_carried(self):
        return len(self.loop_carried) > 0

# maps a pair of statements to a list of dependences
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

class StatementRelations:
    def __init__(self, statement_map, ordering, child_to_parent):
        self.statement_map = statement_map
        self.ordering = ordering
        self.child_to_parent = child_to_parent

def get_statement_relations(program):
    statement_map = {}
    ordering = []
    child_to_parent = {}
    for loop in program.loops:
        for stmt in loop.body:
            statement_map[stmt.node_id] = stmt
            ordering.append(stmt.node_id)
            child_to_parent[stmt.node_id] = loop.node_id
    return StatementRelations(statement_map, ordering, child_to_parent)

def get_accesses(node):
    accesses = set()
    if isinstance(node, Assignment):
        accesses.update(get_accesses(node.lhs))
        accesses.update(get_accesses(node.rhs))
        return accesses
    elif isinstance(node, Access):
        accesses.add(node)
        return accesses
    elif isinstance(node, BinOp):
        accesses.update(get_accesses(node.left))
        accesses.update(get_accesses(node.right))
        return accesses
    else:
        raise RuntimeError('Unhandled type of node ' + str(type(node)))

# two accesses are compatible when they index the same
# loop variables in the same order
def is_comparable(access1, access2):
    n_dimensions = len(access1.indices)
    if  len(access2.indices) != n_dimensions:
        return False
    for index1, index2 in zip(access1.indices, access2.indices):
        if index1.var != index2.var:
            return False
    return True

def is_less_than(access1, access2):
    if not is_comparable(access1, access2):
        raise RuntimeError('Access are not comparable')
    for index1, index2 in zip(access1.indices, access2.indices):
        if index1.relationship < index2.relationship:
            return True
        elif index1.relationship > index2.relationship:
            return False
    return False

def same_memory(access1, access2):
    return access1.var == access2.var

def analyze_dependence(program):
    # L1:
    #   s1
    #   s2
    # L2
    #   s3
    # s1 -> s3: for all accesses to the same array no matter what index
    # s1 -> s1: if there are accesses to the same array
    #           A[i] = A[j]
    #           Loop carried <     if j < i
    #           Loop carried >     if j > i
    #           Non loop carried   if i = j
    # s1 ... A[i] ...
    # s2 ... A[j] ...
    # s1 -> s2: loop carried < if j < i
    #           because access is s1:1 s2:0 s1:2 s2:1
    # s2 -> s1: loop carried < if i < j
    #           because access is s1:0 s2:1 s1:1 s2:2
    # TODO: figure out 3 dimensionals
    #           s1 ... A[2] ...
    #           s2 ... A[1] ...
    #           if i < j: s2 -> s1
    #           
    # s2 -> s1:
    relations = get_statement_relations(program)
    print(relations.ordering)
    print(relations.child_to_parent)
    for i, s in relations.statement_map.items():
        print(i, s.pprint())

    # calculate access to same statement
    print('Calculating access to same statement')
    for stmt_id, stmt in relations.statement_map.items():
        assert(isinstance(stmt, Assignment))
        accesses = list(get_accesses(stmt))
        print(stmt.pprint())
        for index, access1 in enumerate(accesses[:-1]):
            for access2 in accesses[index + 1:]:
                print(access1.pprint() + ' vs ' + access2.pprint())


    # calculate access across statements
    print('Calculating access across statements')
    for index, stmt_id1 in enumerate(relations.ordering[:-1]):
        stmt1 = relations.statement_map[stmt_id1]
        accesses1 = get_accesses(stmt1)
        for stmt_id2 in relations.ordering[index + 1:]:
            # If they are in different loops, assume dependence if they access the same arrays
            stmt2 = relations.statement_map[stmt_id2]
            accesses2 = get_accesses(stmt2)
            # for access1 in accesses1:
            #     for access2 in accesses2:
            #         print(accesses1, accesses2)

def is_valid(dep_graph_before, dep_graph_after):
    # TODO: implement
    pass
