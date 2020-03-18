space_per_indent = 2

class Node:
    def is_statement(self):
        raise NotImplementedError
    def is_loop(self):
        raise NotImplementedError
    def is_expression(self):
        raise NotImplementedError

class Assignment(Node):
    def __init__(self, lhs, rhs, surrounding_loop=None, node_id=0):
        self.node_id = node_id
        self.lhs = lhs
        self.rhs = rhs
        self.surrounding_loop = surrounding_loop
    def pprint(self, indent=0):
        ws = space_per_indent * indent * ' '
        return f'{ws}{self.lhs.pprint()} = {self.rhs.pprint()};'

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

class Access(Node):
    def __init__(self, var, indices=None, node_id=0):
        self.node_id = node_id
        self.var = var
        self.indices = indices if indices else []
    def pprint(self, indent=0):
        list_of_pprint = [f'[{index.pprint()}]' for index in self.indices]
        return f'{self.var}{"".join(list_of_pprint)}'

class AbstractLoop(Node):
    def __init__(self, loop_vars, body, node_id=0):
        self.node_id = node_id
        self.loop_vars = loop_vars
        self.body = body
        self.partial_loop_order = []
    def pprint(self, indent=0):
        ws = space_per_indent * indent * ' '
        header = f'{ws}for [{", ".join(self.loop_vars)}] {{'
        body = [f'{stmt.pprint(indent+1)}' for stmt in self.body]
        end = f'{ws}}}'
        return '\n'.join([header] + body + [end])

class BinOp(Node):
    def __init__(self, left, right, node_id=0):
        self.node_id = node_id
        self.left = left
        self.right = right
    def pprint(self, indent=0):
        return f'{self.left.pprint()} * {self.right.pprint()}'

class Program:
    def __init__(self, loops, node_id=0):
        self.node_id = node_id
        self.loops = loops
    def pprint(self, indent=0):
        body = [f'{loop.pprint(indent)}' for loop in self.loops]
        return '\n'.join(body)
