from math import floor
from abstract_ast import Assignment, AffineIndex, Access, BinOp, AbstractLoop, Declaration, Program, get_program_info
from concrete_ast import CAssignment, CAccess, CScalar, CLiteral, CLoop, CBinOp, CProgram, get_array_names

def loop_header(indent, loop_var, begin, end):
    return '  ' * indent + \
        (f'for (int {loop_var} = {begin}; '
         f'{loop_var} <= {end}; '
         f'++{loop_var}) {{')

def frand():
    return """float frand(float min, float max) {
  float scale = rand() / (float) RAND_MAX;
  return min + scale * (max - min);
}"""

def irand():
    return """float irand(int min, int max) {
  return min + (rand() % (max - min));
}"""

def include():
    return """#include <x86intrin.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>
#include <assert.h>
#include <limits.h>
#include <string.h>"""

def spaces(indent):
    return '  ' * indent

# TODO: test program needs to be a different program
class SimpleFormatter:
    def __init__(self, test_program, ref_program, var_map, array_sizes):
        self.array_sizes = array_sizes
        self.var_map = var_map
        self.indent = 0
        self.test_program = test_program

        # concretize
        self.c_test_program = SimpleConcretizer(test_program,
                                                var_map,
                                                array_sizes).concretize_program()
        self.c_ref_program = SimpleConcretizer(ref_program,
                                               var_map,
                                               array_sizes).concretize_program()

    def array_param(self, ty, name, sizes):
        return f'{ty} {name}' + (''.join([f'[{size}]' for size in sizes]))

    def array_decl(self, ty, name, sizes):
        ws = spaces(self.indent)
        return f'{ws}{ty} (*{name})' + (''.join([f'[{size}]' for size in sizes]) + ';')

    def declare_data(self):
        lines = []
        ws = spaces(self.indent)
        lines.append('struct Data {')
        self.indent += 1
        for array in sorted(self.array_sizes.keys()):
            lines.append(self.array_decl('float', array, self.array_sizes[array]))
        self.indent -= 1
        lines.append('};')
        return '\n'.join(lines)

    def nested_loop(self, loop_vars, sizes, body_lines):
        lines = []
        # loop headers
        for loop_var, size in zip(loop_vars, sizes):
            lines.append(loop_header(self.indent, loop_var, 0, size-1))
            self.indent += 1
        ws = spaces(self.indent)
        for body_line in body_lines:
            lines.append(f'{ws}{body_line}')

        # close brackets
        for _ in range(len(loop_vars)):
            self.indent -= 1
            lines.append('  ' * self.indent + '}')
        return '\n'.join(lines)

    def checksum_inner(self):
        lines = []
        ws = spaces(self.indent)

        params = []
        for array in sorted(self.array_sizes.keys()):
            params.append(self.array_param('float', array, self.array_sizes[array]))

        lines.append(f'{ws}float checksum_inner({", ".join(params)}) {{')

        self.indent += 1
        ws = spaces(self.indent)

        lines.append(f'{ws}float total = 0.0;')

        for array, sizes in self.array_sizes.items():
            loop_vars = [f'i{dimension}' for dimension in range(len(sizes))]
            indices_str = ''.join([f'[{loop_var}]' for loop_var in loop_vars])
            body_lines = [f'total += {array}{indices_str};']
            lines.append(self.nested_loop(loop_vars, sizes, body_lines))

        lines.append(f'{ws}return total;')
        self.indent -= 1
        ws = spaces(self.indent)
        lines.append(f'{ws}}}')
        return '\n'.join(lines)

    def cast_data(self):
        ws = spaces(self.indent)
        return f'{ws}struct Data *data = (struct Data*)void_ptr;'
    def return_inner(self, function_name):
        ws = spaces(self.indent)
        params = [f'*data->{field}' for field in sorted(self.array_sizes.keys())]
        return f'{ws}return {function_name}({", ".join(params)});'

    def wrapper(self, return_type, wrapper_name, inner_name):
        lines = []
        ws = spaces(self.indent)
        lines.append(f'{ws}{return_type} {wrapper_name}(void *void_ptr) {{')
        self.indent += 1
        lines.append(self.cast_data())
        lines.append(self.return_inner(inner_name))
        self.indent -= 1
        lines.append(f'{ws}}};')
        return '\n'.join(lines)

    def init(self):
        return self.wrapper('void', 'init', 'init_inner')
    def checksum(self):
        return self.wrapper('float', 'checksum', 'checksum_inner')
    def kernel(self):
        return self.wrapper('unsigned long long', 'kernel', 'core')
    def declare_core(self):
        params = []
        for array in sorted(self.array_sizes.keys()):
            params.append(self.array_param('float', array, self.array_sizes[array]))
        ws = spaces(self.indent)
        return f'{ws}unsigned long long core({", ".join(params)});'
    def array_allocate(self, ty, arrays, sizes):
        lines = []
        ws = spaces(self.indent)
        
        # malloc
        total_size_str = ' * '.join([f'{size}' for size in sizes])
        for array in arrays:
            lines.append(f'{ws}{array} = malloc(sizeof({ty}) * {total_size_str});')
        return '\n'.join(lines)

    def array_init(self, ty, arrays, sizes, init_value):
        lines = []
        ws = spaces(self.indent)
        loop_vars = [f'i{dimension}' for dimension in range(len(sizes))]
        n_dimensions = len(loop_vars)

        # loop headers
        for dimension, loop_var in enumerate(loop_vars):
            lines.append(loop_header(self.indent, loop_var, 0, sizes[dimension]))
            self.indent += 1

        # loop body
        ws = spaces(self.indent)
        init_var = 'v'
        init_stmt = f'{ws}{ty} {init_var} = {init_value};'
        lines.append(init_stmt)
        indices_str = ''.join([f'[{loop_var}]' for loop_var in loop_vars])
        for array in arrays:
            lines.append(f'{ws}{array}{indices_str} = {init_var};')

        # close brackets
        for _ in range(n_dimensions):
            self.indent -= 1
            lines.append('  ' * self.indent + '}')

        return '\n'.join(lines)

    def allocate(self):
        lines = []
        lines.append(f'void *allocate() {{')
        self.indent += 1
        ws = spaces(self.indent)
        lines.append(f'{ws}struct Data *data = malloc(sizeof(struct Data));')
        for array in sorted(self.array_sizes.keys()):
            lhs = f'data->{array}'
            lines.append(self.array_allocate('float', [lhs], self.array_sizes[array]))
        lines.append(f'{ws}return (void*)data;')
        self.indent -= 1
        lines.append('}')

        return '\n'.join(lines)

    # TODO: create initialization program
    def init_inner(self):
        lines = []

        # array parameters
        params = []
        for array in sorted(self.array_sizes.keys()):
            params.append(self.array_param('float', array, self.array_sizes[array]))
        
        # function header
        lines.append(f'void init_inner({", ".join(params)}) {{')
        self.indent += 1

        # Seed the randomizer
        ws = spaces(self.indent)
        lines.append(f'{ws}allocate();')

        init_value = 'frand(0.0, 1.0)'
        for array in sorted(self.array_sizes.keys()):
            loop_ends = [size - 1 for size in self.array_sizes[array]]
            lines.append(self.array_init('float', [array], loop_ends, init_value))

        # close function
        self.indent -= 1
        lines.append('}')

        return '\n'.join(lines)

    # TODO: create run program
    def run(self):
        return run()
    def main(self):
        return main()
    def core(self):
        lines = []
        ws = spaces(self.indent)

        params = []
        for array in sorted(self.array_sizes.keys()):
            params.append(self.array_param('float', array, self.array_sizes[array]))
        lines.append(f'{ws}unsigned long long core({", ".join(params)}) {{')
        self.indent += 1
        ws = spaces(self.indent)
        lines.append(f'{ws}struct timespec before, after;')
        lines.append(f'{ws}clock_gettime(CLOCK_MONOTONIC, &before);')
        lines.append(self.c_test_program.pprint(self.indent))
        lines.append(f'{ws}clock_gettime(CLOCK_MONOTONIC, &after);')
        lines.append(f'{ws}unsigned long long duration = (after.tv_sec - before.tv_sec) * 1e9;')
        lines.append(f'{ws}duration += after.tv_nsec - before.tv_nsec;')
        lines.append(f'{ws}return duration;')
        self.indent -= 1
        ws = spaces(self.indent)
        lines.append(f'{ws}}}')
        return '\n'.join(lines)
    def array_compare(self, test_array, ref_array, sizes):
        lines = []
        n_dimensions = len(sizes)
        loop_vars = [f'i{dimension}' for dimension in range(n_dimensions)]
        # loop headers
        loop_ends = [size - 1 for size in sizes]
        for dimension, loop_var in enumerate(loop_vars):
            lines.append(loop_header(self.indent, loop_var, 0, loop_ends[dimension]))
            self.indent += 1

        # loop body
        ws = spaces(self.indent)

        indices_str = ''.join([f'[{loop_var}]' for loop_var in loop_vars])
        lines.append(f'{ws}if ((*{test_array}){indices_str} != (*{ref_array}){indices_str}) return 0;')

        # close brackets
        for _ in range(n_dimensions):
            self.indent -= 1
            lines.append('  ' * self.indent + '}')

        return '\n'.join(lines)

    def check(self):
        lines = []
        ws = spaces(self.indent)
        lines.append(f'{ws}int check() {{')
        self.indent += 1
        ws = spaces(self.indent)

        test_program_rename_map = {}
        ref_program_rename_map = {}
        for array in sorted(self.array_sizes.keys()):
            ref = array + '_ref'
            ref_program_rename_map[array] = ref
            test = array + '_test'
            test_program_rename_map[array] = test
            n_dimensions = len(self.array_sizes[array])
            sizes = self.array_sizes[array]
            lines.append(self.array_decl('int', ref, sizes))
            lines.append(self.array_decl('int', test, sizes))

        lines.append(f'{ws}// Initialization')
        for array in sorted(self.array_sizes.keys()):
            ref = array + '_ref'
            test = array + '_test'
            loop_ends = [size - 1 for size in self.array_sizes[array]]
            lines.append(self.array_allocate('int', [ref, test], self.array_sizes[array]))
            lines.append(self.array_init('int', [ref, test], loop_ends, 'irand(1, 10)'))

        # make test program
        c_test_program = self.c_test_program.clone()
        c_ref_program = self.c_ref_program.clone()
        c_test_program.rename(test_program_rename_map)
        c_ref_program.rename(ref_program_rename_map)

        lines.append(f'{ws}// Test program')
        lines.append(c_test_program.pprint(self.indent))

        lines.append(f'{ws}// Reference program')
        lines.append(c_ref_program.pprint(self.indent))

        # compare the results
        lines.append(f'{ws}// Compare the results')
        for array in sorted(self.array_sizes.keys()):
            ref = array + '_ref'
            test = array + '_test'
            lines.append(self.array_compare(test, ref, self.array_sizes[array]))

        # if it reaches here, everything is good
        lines.append(f'{ws}return 1;')
        self.indent -= 1
        ws = spaces(self.indent)
        lines.append(f'{ws}}}')
        return '\n'.join(lines)

    def write_kernel_wrapper(self, file_name):
        with open(file_name, 'w') as f:
            f.write(include())
            f.write('\n\n')
            f.write(self.declare_core())
            f.write('\n\n')
            f.write(self.declare_data())
            f.write('\n\n')
            f.write(frand())
            f.write('\n\n')
            f.write(irand())
            f.write('\n\n')
            f.write(self.allocate())
            f.write('\n\n')
            f.write(self.init_inner())
            f.write('\n\n')
            f.write(self.checksum_inner())
            f.write('\n\n')
            f.write(self.init())
            f.write('\n\n')
            f.write(self.checksum())
            f.write('\n\n')
            f.write(self.kernel())
            f.write('\n\n')
        
    def write_core(self, file_name):
        with open(file_name, 'w') as f:
            f.write(include())
            f.write('\n\n')
            f.write(self.core())
            f.write('\n\n')

class SimpleConcretizer:
    def __init__(self, program, var_map, array_sizes):
        self.program = program
        self.var_map = var_map
        self.array_sizes = array_sizes
    def concretize_program(self):
        return self.concretize(self.program)
    def concretize(self, node):
        if isinstance(node, Assignment):
            return CAssignment(
                self.concretize(node.lhs.clone()),
                self.concretize(node.rhs.clone()))
        elif isinstance(node, Declaration):
            # Nothing to do for declarations
            pass
            # return CDeclaration(node.name,
            #                     self.array_sizes[node.name])
        elif isinstance(node, AffineIndex):
            if not node.var or node.coeff == 0:
                return CLiteral(node.offset)
            if node.coeff == 1:
                left = CScalar(node.var)
            else:
                left = CBinOp('*', CLiteral(node.coeff), CScalar(node.var))
            if node.offset == 0:
                return left
            else:
                if node.offset > 0:
                    return CBinOp('+', left, CLiteral(node.offset))
                else:
                    return CBinOp('-', left, CLiteral(-node.offset))
        elif isinstance(node, Access):
            indices = [self.concretize(index) for index in node.indices]
            return CAccess(node.var, indices)
        elif isinstance(node, BinOp):
            return CBinOp(node.op,
                          self.concretize(node.left.clone()),
                          self.concretize(node.right.clone()))
        elif isinstance(node, AbstractLoop):
            body = [self.concretize(stmt.clone()) for stmt in node.body]
            reversed_loop_vars = list(node.loop_vars)
            reversed_loop_vars.reverse()
            inner_loop = None
            for loop_var in reversed_loop_vars:
                start = self.var_map.get_min(loop_var)
                end = self.var_map.get_max(loop_var)
                if inner_loop:
                    inner_loop = CLoop(loop_var, start, end, [inner_loop])
                else:
                    inner_loop = CLoop(loop_var, start, end, body)

            return inner_loop
        elif isinstance(node, Program):
            loops = [self.concretize(loop.clone()) for loop in node.loops]
            return CProgram(loops)
        else:
            raise RuntimeError('Unhandled type of node ' + str(type(node)))
