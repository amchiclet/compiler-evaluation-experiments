# Anything related to dependence goes here

from abstract_ast import Assignment, Access, AbstractIndex, AffineIndex, AbstractLoop, BinOp, Program, get_accesses, is_same_memory, get_all_access_pairs, is_in_same_loop
from loguru import logger

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
        return self.loop_carried and \
            self.from_access.parent_stmt.surrounding_loop == \
            self.to_access.parent_stmt.surrounding_loop
    def pprint(self):
        from_type = 'W' if self.from_access.is_write else 'R'
        from_str = f'{self.from_access.pprint()}({from_type})'
        to_type = 'W' if self.to_access.is_write else 'R'
        to_str = f'{self.to_access.pprint()}({to_type})'
        loop_carried_str = f'{self.loop_carried}' if self.is_loop_carried() else '[Loop-independent]'
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
        lines = []
        for (s1, s2), deps in self.dep_map.items():
            if s1 == s2:
                lines.append(f'Same statement dep:\n'
                             f'\t{statement_map[s1].pprint()}')
            else:
                lines.append(f'Dep across statements:\n'
                             f'\tFrom: {statement_map[s1].pprint()}\n'
                             f'\tTo: {statement_map[s2].pprint()}')
            for dep in deps:
                lines.append(f'\t{dep.pprint()}')
        
        if len(lines) > 0:
            return '\n'.join(lines)
        else:
            return 'No dependence'

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
    assert(is_same_memory(access1, access2))
    array = access1.var
    # if not is_comparable(access1, access2):
    #     raise RuntimeError('Access are not comparable')
    logger.debug(loop_analysis.debug())
    result = []

    for v in loop_order:
        # if loop var is not used in any of the groups,
        # it means that either that loop var is not used at all
        # or it means that the group contains constant indices
        dep_ranges = None
        for group in loop_analysis.groups:
            if group.array == array and group.has_common_loop_vars([v]):
                dep_ranges = group.dep_ranges
                break
        if not dep_ranges:
            continue

        # special case when there is no loop var in expression
        # if they're different, then they is no dependence
        # find the group needed to calculate this dependency
        min_i = loop_analysis.loop_var_analysis.min_val(v)
        max_i = loop_analysis.loop_var_analysis.max_val(v)
        loop_var_range = [min_i, max_i]
        logger.debug(f'Checking dependence for loop var {v} {loop_var_range}')
        for dimension, (index1, index2) in enumerate(zip(access1.indices, access2.indices)):
            assert(type(index1) == type(index2))
            if index1.var != v and index1.var != 'dummy':
                continue
            if index2.var != v and index2.var != 'dummy':
                continue
            if isinstance(index1, AbstractIndex):
                raise RuntimeError('Abstract indices are not supported any more')
                assert(index2.var == v)
                result.append(index1.relationship - index2.relationship)
            elif isinstance(index1, AffineIndex):
                if dep_ranges.is_loop_independent(loop_var_range, index1, index2):
                    compare_result = 0
                elif dep_ranges.is_loop_carried(loop_var_range, index1, index2):
                    compare_result = 1
                elif dep_ranges.is_loop_carried(loop_var_range, index2, index1):
                    compare_result = -1
                else:
                    # it's independent. no need to subtract further
                    logger.debug(f'Found an independent range')
                    return []
                result.append(compare_result)
            else:
                raise RuntimeError('Unsupported case')
    return result

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
        logger.debug(f'Statement relations')
        logger.debug(f'\t{relations.ordering}')
        logger.debug(f'\t{relations.child_to_parent}')
        for i, s in relations.statement_map.items():
            logger.debug('\t', i, s.pprint())

    dep_graph = DependenceGraph()

    for access1, access2 in get_all_access_pairs(program):
        # logger.debug(f'Analyzing dependence for {access1.pprint()} vs {access2.pprint()}')
        if access1 == access2:
            continue

        if not is_same_memory(access1, access2):
            continue

        # if not is_comparable(access1, access2):
        #     raise RuntimeError(f'Accesses are not comparable: '
        #                        f'{access1.pprint()}, '
        #                        f'{access2.pprint()}')

        if not (access1.is_write or access2.is_write):
            continue

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
            logger.debug(f'Analyzing {before_str} -> {after_str}')
            loop = stmt1.surrounding_loop
            diff = subtract(loop.loop_vars, before, after, loop_analysis[loop.node_id])
            if not diff:
                logger.debug('No dependency')
                # there's no dependence between these statements
                continue
            if is_zero(diff):
                logger.debug(f'dep {before_str} -> {after_str}')
                dep_graph.add(before, after)
            elif is_negative(diff):
                logger.debug(f'dep {after_str} -> {before_str}')
                dep_graph.add(after, before, to_direction_vector(diff))
            else:
                logger.debug(f'dep {before_str} -> {after_str}')
                dep_graph.add(before, after, to_direction_vector(inverse(diff)))
        else:
            # if in different loop,
            # there's a dependency from stmt1 to stmt2
            logger.debug(f'dep {before_str} -> {after_str}')
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

