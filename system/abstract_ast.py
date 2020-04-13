space_per_indent = 2

def is_list_syntactically_equal(list1, list2):
    if len(list1) != len(list2):
        return False
    for i1, i2 in zip(list1, list2):
        if not i1.is_syntactically_equal(i2):
            return False
    return True

class Node:
    def is_statement(self):
        raise NotImplementedError
    def is_loop(self):
        raise NotImplementedError
    def is_expression(self):
        raise NotImplementedError
    # clone the node including the node ids
    def clone(self):
        raise NotImplementedError
    def is_syntactically_equal(self, other):
        raise NotImplementedError

class Assignment(Node):
    def __init__(self, lhs, rhs, node_id=0):
        self.node_id = node_id
        self.lhs = lhs
        self.rhs = rhs
        self.surrounding_loop = None
    def pprint(self, indent=0):
        ws = space_per_indent * indent * ' '
        return f'{ws}{self.lhs.pprint()} = {self.rhs.pprint()};'
    def clone(self):
        cloned = Assignment(self.lhs.clone(), self.rhs.clone(), self.node_id)
        for access in get_accesses(cloned):
            access.parent_stmt = cloned
        return cloned
    def is_syntactically_equal(self, other):
        return self.lhs.is_syntactically_equal(other.lhs) and \
            self.rhs.is_syntactically_equal(other.rhs)

class AffineIndex(Node):
    def __init__(self, var, coeff, offset, node_id=0):
        self.node_id = node_id
        self.var = var
        self.coeff = coeff
        self.offset = offset
        self.array = None
        self.dimension = None
    def pprint(self, indent=0):
        if self.var:
            linear = f'{self.var}' if self.coeff == 1 else f'{self.coeff}*{self.var}'
            if self.offset > 0:
                return f'{linear}+{self.offset}'
            elif self.offset < 0:
                return f'{linear}{self.offset}'
            else:
                return f'{linear}'
        else:
            return f'{self.offset}'
    def clone(self):
        cloned = AffineIndex(self.var, self.coeff, self.offset, self.node_id)
        cloned.array = self.array
        cloned.dimension = self.dimension
        return cloned
    def is_syntactically_equal(self, other):
        return self.var == other.var and \
            self.coeff == other.coeff and \
            self.offset == other.offset

class AbstractIndex(Node):
    def __init__(self, var, relationship=0, node_id=0):
        self.node_id = node_id
        self.var = var
        self.relationship = relationship
    def pprint(self, indent=0):
        if self.relationship > 0:
            sign = '>' * self.relationship
        elif self.relationship < 0:
            sign = '<' * (-self.relationship)
        else:
            sign = ''
        s = f'{sign}{self.var}'
        return s
    def clone(self):
        return AbstractIndex(self.var, self.relationship, self.node_id)
    def is_syntactically_equal(self, other):
        return self.var == other.var and self.relationship == other.relationship

# TODO: create expr class

class Access(Node):
    def __init__(self, var, indices=None, node_id=0):
        self.node_id = node_id
        self.var = var
        self.indices = indices if indices else []
        for dimension, index in enumerate(indices):
            index.array = var
            index.dimension = dimension
        self.is_write = False
        self.parent_stmt = None
    def pprint(self, indent=0):
        list_of_pprint = [f'[{index.pprint()}]' for index in self.indices]
        return f'{self.var}{"".join(list_of_pprint)}'
    def clone(self):
        cloned_indices = [i.clone() for i in self.indices]
        cloned = Access(self.var, cloned_indices, self.node_id)
        for dimension, index in enumerate(cloned_indices):
            index.array = self.var
            index.dimension = dimension
        cloned.is_write = self.is_write
        return cloned
    def is_syntactically_equal(self, other):
        return self.var == other.var and \
            is_list_syntactically_equal(self.indices, other.indices)

class AbstractLoop(Node):
    def __init__(self, loop_vars, body, node_id=0):
        self.node_id = node_id
        self.loop_vars = loop_vars
        self.body = body
        # To be used for strip mining
        self.partial_loop_order = []
    def pprint(self, indent=0):
        ws = space_per_indent * indent * ' '
        header = f'{ws}for [{", ".join(self.loop_vars)}] {{'
        body = [f'{stmt.pprint(indent+1)}' for stmt in self.body]
        end = f'{ws}}}'
        return '\n'.join([header] + body + [end])
    def clone(self):
        cloned_loop_vars = list(self.loop_vars)
        cloned_body = [stmt.clone() for stmt in self.body]
        cloned_loop = AbstractLoop(cloned_loop_vars, cloned_body, self.node_id)
        for stmt in cloned_body:
            stmt.surrounding_loop = cloned_loop
        return cloned_loop
    def is_syntactically_equal(self, other):
        if self.loop_vars != other.loop_vars:
            return False
        return is_list_syntactically_equal(self.body, other.body)

class BinOp(Node):
    def __init__(self, left, right, node_id=0):
        self.node_id = node_id
        self.left = left
        self.right = right
    def pprint(self, indent=0):
        return f'{self.left.pprint()} * {self.right.pprint()}'
    def clone(self):
        return BinOp(self.left.clone(), self.right.clone(), self.node_id)
    def is_syntactically_equal(self, other):
        return self.left.is_syntactically_equal(other.left) and \
            self.right.is_syntactically_equal(other.right)

class Program:
    def __init__(self, loops, node_id=0):
        self.node_id = node_id
        self.loops = loops
    def pprint(self, indent=0):
        body = [f'{loop.pprint(indent)}' for loop in self.loops]
        return '\n'.join(body)
    def clone(self):
        cloned_loops = [loop.clone() for loop in self.loops]
        return Program(cloned_loops, self.node_id)
    def is_syntactically_equal(self, other):
        return is_list_syntactically_equal(self.loops, other.loops)

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
    elif isinstance(node, AbstractLoop):
        for stmt in node.body:
            accesses.update(get_accesses(stmt))
        return accesses
    elif isinstance(node, Program):
        for loop in node.loops:
            accesses.update(get_accesses(loop))
        return accesses
    else:
        raise RuntimeError('Unhandled type of node ' + str(type(node)))

# returns a map from array name to the number of dimensions for that array
def get_arrays(program):
    arrays = {}
    for access in get_accesses(program):
        array_name = access.var
        n_dimensions = len(access.indices)
        if not array_name in arrays:
            arrays[array_name] = n_dimensions
        else:
            assert(arrays[array_name] == n_dimensions)
    return arrays
    
# gather array dimensions and loop accesses
def get_program_info(program):
    # maps array name to [loop var name]
    arrays = {}
    # maps loop var name to (lower, upper)
    loop_vars = {}
    for access in get_accesses(program):
        array_name = access.var
        n_dimensions = len(access.indices)
        if n_dimensions == 0:
            continue
        if not array_name in arrays:
            arrays[array_name] = [None] * n_dimensions
        for i, abstract_index in enumerate(access.indices):
            loop_var = abstract_index.var

            # update arrays
            if not arrays[array_name][i]:
                arrays[array_name][i] = loop_var
            else:
                assert(arrays[array_name][i] == loop_var)

            # update loop_vars
            if not loop_var in loop_vars:
                loop_vars[loop_var] = [0, 0]
            loop_vars[loop_var][0] = min(loop_vars[loop_var][0],
                                         abstract_index.relationship)
            loop_vars[loop_var][1] = max(loop_vars[loop_var][1],
                                         abstract_index.relationship)
    return arrays, loop_vars

# two accesses are compatible when they index the same
# loop variables in the same order
def is_comparable(access1, access2):
    n_dimensions = len(access1.indices)
    if  len(access2.indices) != n_dimensions:
        return False
    for index1, index2 in zip(access1.indices, access2.indices):
        if type(index1) != type(index2):
            return False
        if index1.var != index2.var:
            return False
    return True

def is_same_memory(access1, access2):
    return access1.var == access2.var

def is_in_same_loop(stmt1, stmt2):
    return stmt1.surrounding_loop.node_id == stmt2.surrounding_loop.node_id

def all_pairs(s):
    l = list(s)
    for index, e1 in enumerate(l[:-1]):
        for e2 in l[index+1:]:
            yield (e1, e2)

def get_all_access_pairs(node):
    return all_pairs(get_accesses(node))

