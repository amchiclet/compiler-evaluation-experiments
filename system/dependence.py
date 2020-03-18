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
            self.dep_map[dep_pair] = []
        self.dep_map[dep_pair].append(Dependence(loop_carried))
    def has_dependence(self, s1, s2):
        return (s1, s2) in self.dep_map
    def get_dependence(self, s1, s2):
        return self.dep_map[(s1, s2)]
    def pprint(self, statement_map):
        for (s1, s2), deps in self.dep_map.items():
            if s1 == s2:
                print(f'Same statement dep:\n'
                      f'\t{statement_map[s1].pprint()}')
            else:
                print(f'Dep across statements:\n'
                      f'\tFrom: {statement_map[s1].pprint()}\n'
                      f'\tTo: {statement_map[s2].pprint()}')
            for dep in deps:
                if dep.loop_carried:
                    print(f'\tLoop carried: {dep.loop_carried}')

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
    print(ordering)
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

def is_negative(nums):
    for n in nums:
        if n < 0:
            return True
        elif n > 0:
            return False
    return False

def is_zero(nums):
    for n in nums:
        if n != 0:
            return False
    return True

def inverse(nums):
    return [-n for n in nums]

def subtract(loop_order, access1, access2):
    if not is_comparable(access1, access2):
        raise RuntimeError('Access are not comparable')
    result = []
    for v in loop_order:
        for i1, i2 in zip(access1.indices, access2.indices):
            if i1.var == v:
                assert(i2.var == v)
                result.append(i1.relationship - i2.relationship)
    return result

def is_same_memory(access1, access2):
    return access1.var == access2.var

def is_in_same_loop(stmt1, stmt2):
    return stmt1.surrounding_loop.node_id == stmt2.surrounding_loop.node_id

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
    debug = False
    if debug:
        print('Printing debug')
        print(relations.ordering)
        print(relations.child_to_parent)
        for i, s in relations.statement_map.items():
            print(i, s.pprint())

    dep_graph = DependenceGraph()

    # calculate access to same statement
    print('Calculating access to same statement')
    for stmt_id, stmt in relations.statement_map.items():
        assert(not stmt.surrounding_loop is None)
        loop_order = stmt.surrounding_loop.loop_vars
        assert(isinstance(stmt, Assignment))
        accesses = list(get_accesses(stmt))
        print(stmt.pprint())
        for index, access1 in enumerate(accesses[:-1]):
            for access2 in accesses[index + 1:]:
                if not is_same_memory(access1, access2):
                    continue
                if not is_comparable(access1, access2):
                    raise RuntimeError(f'Accesses are not comparable: '
                                       f'{access1.pprint()}, '
                                       f'{access2.pprint()}')
                diff = subtract(loop_order, access1, access2)
                print(diff)
                # if i's negative, then there's a dependence from access1 to access2
                loop_carried_dep = diff if is_negative(diff) else inverse(diff)
                dep_graph.add(stmt_id, stmt_id, loop_carried_dep)

    # calculate access across statements
    print('Calculating access across statements')
    for index, stmt_id1 in enumerate(relations.ordering[:-1]):
        stmt1 = relations.statement_map[stmt_id1]
        accesses1 = get_accesses(stmt1)
        for stmt_id2 in relations.ordering[index + 1:]:
            stmt2 = relations.statement_map[stmt_id2]
            accesses2 = get_accesses(stmt2)

            print(stmt1.pprint())
            print(stmt2.pprint())
            if is_in_same_loop(stmt1, stmt2):
                # If they are in the same loop, need further dependence analysis
                for access1 in accesses1:
                    for access2 in accesses2:
                        if not is_same_memory(access1, access2):
                            continue
                        diff = subtract(loop_order, access1, access2)
                        # for i ...
                        #   s1: ... a[i] ...
                        #   s2: ... a[i-1] ...
                        # causes a dependency from s1 to s2
                        # s1 subtract s2 is 1
                        if is_zero(diff):
                            print('Adding dep ', access1.pprint(), access2.pprint())
                            dep_graph.add(stmt_id1, stmt_id2)
                        elif is_negative(diff):
                            print('Adding dep ', access2.pprint(), access1.pprint())
                            dep_graph.add(stmt_id2, stmt_id1, diff)
                        else:
                            print('Adding dep ', access1.pprint(), access2.pprint())
                            dep_graph.add(stmt_id1, stmt_id2, inverse(diff))
            else:
                # If they are in different loops,
                # assume dependence from statement that happens before
                # if they access the same arrays
                for access1 in accesses1:
                    for access2 in accesses2:
                        if not is_same_memory(access1, access2):
                            continue
                        print('Adding dep ', access1.pprint(), access2.pprint())
                        dep_graph.add(stmt_id1, stmt_id2)
    dep_graph.pprint(relations.statement_map)

def is_valid(dep_graph_before, dep_graph_after):
    # TODO: implement
    pass
