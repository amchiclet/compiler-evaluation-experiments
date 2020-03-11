space_per_indent = 2

class Assignment:
    def __init__(self, lhs, rhs):
        self.lhs = lhs
        self.rhs = rhs
    def pprint(self, indent=0):
        ws = space_per_indent * indent * ' '
        return f'{ws}{self.lhs.pprint()} = {self.rhs.pprint()};'

class Index:
    def __init__(self, var, relationship=0):
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

class Access:
    def __init__(self, var, indices=None):
        self.var = var
        self.indices = indices if indices else []
    def pprint(self, indent=0):
        list_of_pprint = [f'[{index.pprint()}]' for index in self.indices]
        return f'{self.var}{"".join(list_of_pprint)}'

class AbstractLoop:
    def __init__(self, loop_vars, body):
        self.loop_vars = loop_vars
        self.body = body
    def pprint(self, indent=0):
        ws = space_per_indent * indent * ' '
        header = f'{ws}for [{", ".join(self.loop_vars)}] {{'
        body = [f'{stmt.pprint(indent+1)}' for stmt in self.body]
        end = f'{ws}}}'
        return '\n'.join([header] + body + [end])

class BinOp:
    def __init__(self, left, right):
        self.left = left
        self.right = right
    def pprint(self, indent=0):
        return f'{self.left.pprint()} * {self.right.pprint()}'
