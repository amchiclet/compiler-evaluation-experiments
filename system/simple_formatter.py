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

def loop_header(indent, loop_var, begin, end):
    return '  ' * indent + \
        (f'for (int {loop_var} = {begin};'
         f'{loop_var} < {end};'
         f'++{loop_var}) {{')

def frand():
    return """
float frand(float min, float max) {
  float scale = rand() / (float) RAND_MAX;
  return min + scale * (max - min);
}
"""

def spaces(indent):
    return '  ' * indent
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
        lines = []
        for array in sorted(self.arrays.keys()):
            lines.append(self.array_decl(array, len(self.arrays[array])))
            test_array = array + 'test'
            lines.append(self.array_decl(test_array, len(self.arrays[array])))
        lines.append(frand())
        return '\n'.join(lines)
    def array_init(self, array, test_array, mentioned_loop_vars):
        lines = []
        ws = spaces(self.indent)
        n_dimensions = len(mentioned_loop_vars)

        # malloc
        total_size_str = ' * '.join([f'{self.dimension_size}'] * n_dimensions)
        lines.append(f'{ws}{array} = malloc(sizeof(float) * {total_size_str});')
        lines.append(f'{ws}{test_array} = malloc(sizeof(float) * {total_size_str});')

        # loop headers
        for loop_var in mentioned_loop_vars:
            lines.append(loop_header(self.indent, loop_var, 0, self.dimension_size))
            self.indent += 1

        # loop body
        ws = spaces(self.indent)
        init_var = 'v'
        init_value = f'{ws}float {init_var} = frand(0.0, 1.0);'
        indices_str = ''.join([f'[{loop_var}]' for loop_var in mentioned_loop_vars])
        lines.append(init_value)
        lines.append(f'{ws}(*{array}){indices_str} = {init_var};')
        lines.append(f'{ws}(*{test_array}){indices_str} = {init_var};')

        # close brackets
        for _ in range(len(mentioned_loop_vars)):
            self.indent -= 1
            lines.append('  ' * self.indent + '}')

        return '\n'.join(lines)
        
    def init(self):
        lines = []

        # function header
        lines.append(f'void init() {{')

        self.indent += 1

        # Seed the randomizer
        ws = spaces(self.indent)
        lines.append(f'{ws}srand(0);')
        for array in sorted(self.arrays.keys()):
            test_array = array + 'test'
            lines.append(self.array_init(array, test_array, self.arrays[array]))

        # close function
        self.indent -= 1
        lines.append('}')

        return '\n'.join(lines)

    def run(self):
        return self.format_program(self.program)
    def check(self):
        pass
    def array_decl(self, var, n_dimensions):
        return f'float (*{var})' + (''.join([f'[{self.dimension_size}]' * n_dimensions]) + ';')

from abstract_ast import Assignment, AbstractIndex, Access, BinOp, AbstractLoop, Program
from concrete_ast import CAssignment, CAccess, CScalar, CLiteral, CLoop, CBinOp, CProgram
class SimpleConcretizer:
    def concretize(self, node):
        if isinstance(node, Assignment):
            return CAssignment(
                self.concretize(node.lhs.clone()),
                self.concretize(node.rhs.clone()))
        elif isinstance(node, AbstractIndex):
            if node.relationship == 0:
                return CScalar(node.var)
            elif node.relationship > 0:
                return CBinOp('+', CScalar(node.var), CLiteral(node.relationship))
            else:
                return CBinOp('-', CScalar(node.var), CLiteral(-node.relationship))
        elif isinstance(node, Access):
            indices = [self.concretize(index) for index in node.indices]
            return CAccess(node.var, indices)
        elif isinstance(node, BinOp):
            return CBinOp('*',
                          self.concretize(node.left.clone()),
                          self.concretize(node.right.clone()))
        elif isinstance(node, AbstractLoop):
            stmts = [self.concretize(stmt.clone()) for stmt in node.body]
            return CLoop(list(node.loop_vars), stmts)
        elif isinstance(node, Program):
            loops = [self.concretize(loop.clone()) for loop in node.loops]
            return CProgram(loops)
        else:
            raise RuntimeError('Unhandled type of node ' + str(type(node)))
