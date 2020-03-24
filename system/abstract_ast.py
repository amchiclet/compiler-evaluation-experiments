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
        self.is_write = False
        self.parent_stmt = None
    def pprint(self, indent=0):
        list_of_pprint = [f'[{index.pprint()}]' for index in self.indices]
        return f'{self.var}{"".join(list_of_pprint)}'
    def clone(self):
        cloned_indices = [i.clone() for i in self.indices]
        cloned = Access(self.var, cloned_indices, self.node_id)
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

