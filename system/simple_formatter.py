from abstract_ast import BinOp
from math import floor

def determine_dimension_size(arrays, max_size_per_array):
    # sort array names by their depth
    depth_of_deepest_array = -1
    for var, mentioned_loop_vars in arrays.items():
        if len(mentioned_loop_vars) > depth_of_deepest_array:
            depth_of_deepest_array = len(mentioned_loop_vars)
    assert(depth_of_deepest_array > 0)
    return floor(max_size_per_array ** (1 / depth_of_deepest_array))

class SimpleFormatter:
    # TODO: implement dispatcher
    def __init__(self, arrays, loop_vars, max_size_per_array, program, indent=0):
        self.arrays = arrays
        self.loop_vars = loop_vars
        self.dimension_size = determine_dimension_size(arrays, max_size_per_array)
        self.indent = indent
        self.program = program
        for var, (lower, upper) in loop_vars.items():
            assert(upper - lower < self.dimension_size)
    def declare(self):
        pass
    def init(self):
        pass
    def run(self):
        return self.format_program(self.program)
    def check(self):
        pass

    def array_decl(self, var):
        return f'float *{var}' + ''.join([f'[{dimension_size}]' * len(self.arrays[var])])

    def assignment(self, a):
        return '  ' * self.indent + f'{self.access(a.lhs)} = {self.binop(a.rhs)};'

    def index(self, i):
        if i.relationship == 0:
            return f'{i.var}'
        elif i.relationship > 0:
            return f'{i.var}+{i.relationship}'
        else:
            return f'{i.var}{i.relationship}'

    def access(self, a):
        list_of_pprint = [f'[{self.index(i)}]' for i in a.indices]
        return f'{a.var}{"".join(list_of_pprint)}'

    def binop(self, b):
        if isinstance(b, BinOp):
            return f'{self.binop(b.left)} * {self.binop(b.right)}'
        else:
            return self.access(b)

    def loop_header(self, loop_var):
        return '  ' * self.indent + \
            (f'for (int {loop_var} = {0-self.loop_vars[loop_var][0]};'
             f'{loop_var} < {self.dimension_size - self.loop_vars[loop_var][1]};'
             f'++{loop_var}) {{')

    def loop(self, l):
        lines = []
        for loop_var in l.loop_vars:
            lines.append(self.loop_header(loop_var))
            self.indent += 1
        lines += [self.assignment(stmt) for stmt in l.body]
        for _ in range(len(l.loop_vars)):
            self.indent -= 1
            lines.append('  ' * self.indent + '}')
        return '\n'.join(lines)

    def format_program(self, p):
        lines = []
        for l in p.loops:
            lines.append(self.loop(l))
        return '\n'.join(lines)
