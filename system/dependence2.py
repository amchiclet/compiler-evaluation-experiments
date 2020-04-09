# Anything related to dependence goes here

from abstract_ast import Assignment, Access, AbstractIndex, AffineIndex, AbstractLoop, BinOp, Program, get_accesses, is_same_memory, is_comparable, get_all_access_pairs, is_in_same_loop

debug = True

# Each element of loop_carried holds one of the following values:
# (1) <
# (2) >
# (3) =
# (4) ?
class Dependence:
    def __init__(self, from_access, to_access, loop_carried=None):
        self.dep_id = (from_access.node_id, to_access.node_id)
        self.from_access = from_access
        self.to_access = to_access
        self.loop_carried = loop_carried
    def is_loop_carried(self):
        return \
            self.from_access.parent_stmt.surrounding_loop == \
            self.to_access.parent_stmt.surrounding_loop
    def pprint(self):
        from_type = 'W' if self.from_access.is_write else 'R'
        from_str = f'{self.from_access.pprint()}({from_type})'
        to_type = 'W' if self.to_access.is_write else 'R'
        to_str = f'{self.to_access.pprint()}({to_type})'
        loop_carried_str = f'[{self.loop_carried}]' if self.is_loop_carried() else ''
        return f'dep {from_str} -> {to_str} {loop_carried_str}'

# maps a pair of statements to a list of dependences
class DependenceGraph:
    def __init__(self):
        self.dep_map = {}
        self.dep_access_pairs = set()
    def add(self, from_access, to_access, loop_carried=None):
        s1 = from_access.parent_stmt.node_id
        s2 = to_access.parent_stmt.node_id
        stmt_pair = (s1, s2)
        if not stmt_pair in self.dep_map:
            self.dep_map[stmt_pair] = []
        self.dep_map[stmt_pair].append(Dependence(from_access, to_access, loop_carried))
        self.dep_access_pairs.add((from_access.node_id, to_access.node_id))
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
                print(f'\t{dep.pprint()}')

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

def subtract(loop_order, access1, access2, loop_analysis):
    if not is_comparable(access1, access2):
        raise RuntimeError('Access are not comparable')
    result = []
    for v in loop_order:
        min_i = loop_analysis.loop_var_analysis.min_val(v)
        max_i = loop_analysis.loop_var_analysis.max_val(v)
        loop_var_range = [min_i, max_i]
        for dimension, (index1, index2) in enumerate(zip(access1.indices, access2.indices)):
            assert(type(index1) == type(index2))
            if index1.var != v:
                continue
            if isinstance(index1, AbstractIndex):
                assert(index2.var == v)
                result.append(index1.relationship - index2.relationship)
            elif isinstance(index1, AffineIndex):
                dep_range_map = loop_analysis.dep_map[(v, access1.var, dimension)]
                if dep_range_map.is_loop_independent(loop_var_range, index1, index2):
                    compare_result = 0
                elif dep_range_map.is_loop_carried(loop_var_range, index1, index2):
                    compare_result = 1
                elif dep_range_map.is_loop_carried(loop_var_range, index2, index1):
                    compare_result = -1
                else:
                    # it's independent. no need to subtract further
                    return None
                result.append(compare_result)
            else:
                raise RuntimeError('Unsupported case')
    return result

class AccessPair:
    def __init__(self, stmt_ordering, access1, access2):
        assert(isinstance(access1, Access))
        assert(isinstance(access2, Access))
        stmt1_index = stmt_ordering.index(access1.parent_stmt.node_id)
        stmt2_index = stmt_ordering.index(access2.parent_stmt.node_id)
        # if in the same statement, read comes before write
        if stmt1_index == stmt2_index:
            if access1.is_write:
                self.before = access2
                self.after = access1
            else:
                self.before = access1
                self.after = access2
        elif stmt1_index < stmt2_index:
            self.before = access1
            self.after = access2
        else:
            self.before = access2
            self.after = access1

def to_direction(num):
    if num > 0:
        return '>'
    elif num < 0:
        return '<'
    else:
        return '='

def to_direction_vector(nums):
    return [to_direction(num) for num in nums]

def analyze_dependence(program, loop_analysis):
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
    if debug:
        print(f'Statement relations')
        print(f'\t{relations.ordering}')
        print(f'\t{relations.child_to_parent}')
        for i, s in relations.statement_map.items():
            print('\t', i, s.pprint())

    dep_graph = DependenceGraph()

    for access1, access2 in get_all_access_pairs(program):
        if access1 == access2:
            continue

        if not is_same_memory(access1, access2):
            continue

        if not is_comparable(access1, access2):
            raise RuntimeError(f'Accesses are not comparable: '
                               f'{access1.pprint()}, '
                               f'{access2.pprint()}')

        if not (access1.is_write or access2.is_write):
            continue

        # access_pair = AccessPair(relations.ordering, access1, access2)

        # before = access_pair.before
        # before_type = 'W' if before.is_write else 'R'
        # before_str = f'{before.pprint()}({before_type})'
        # stmt1 = before.parent_stmt

        # after = access_pair.after
        # after_type = 'W' if after.is_write else 'R'
        # after_str = f'{after.pprint()}({after_type})'
        # stmt2 = after.parent_stmt

        before = access1
        before_type = 'W' if before.is_write else 'R'
        before_str = f'{before.pprint()}({before_type})'
        stmt1 = before.parent_stmt

        after = access2
        after_type = 'W' if after.is_write else 'R'
        after_str = f'{after.pprint()}({after_type})'
        stmt2 = after.parent_stmt
        
        # if in the same loop, calculate loop carried dependency
        if is_in_same_loop(stmt1, stmt2):
            # print(f'Analyzing {before_str} -> {after_str}')
            loop = stmt1.surrounding_loop
            diff = subtract(loop.loop_vars, before, after, loop_analysis[loop.node_id])
            if not diff:
                # print('No dependency')
                # there's no dependence between these statements
                continue
            if is_zero(diff):
                if debug:
                    print(f'dep {before_str} -> {after_str}')
                dep_graph.add(before, after)
            elif is_negative(diff):
                if debug:
                    print(f'dep {after_str} -> {before_str}')
                dep_graph.add(after, before, to_direction_vector(diff))
            else:
                if debug:
                    print(f'dep {before_str} -> {after_str}')
                dep_graph.add(before, after, to_direction_vector(inverse(diff)))
        else:
            # if in different loop,
            # there's a dependency from stmt1 to stmt2
            if debug:
                print(f'dep {before_str} -> {after_str}')
            dep_graph(before, after)
    if debug:
        dep_graph.pprint(relations.statement_map)
    return dep_graph

def is_valid(dep_graph_before, dep_graph_after):
    # TODO: implement
    # Rule: existing dependencies cannot be reversed
    # (Dependencies can be added or removed though)
    # 1) check for accesses in the same statement
    # 2) check for accesses across statements
    for (s1, s2) in dep_graph_before.dep_access_pairs:
        if (s2, s1) in dep_graph_after.dep_access_pairs:
            return False
    return True

