from math import floor
from abstract_ast import Assignment, AbstractIndex, Access, BinOp, AbstractLoop, Program, get_program_info
from concrete_ast import CAssignment, CAccess, CScalar, CLiteral, CLoop, CBinOp, CProgram, get_array_names

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

def irand():
    return """
float irand(int min, int max) {
  return min + (rand() % (max - min));
}
"""

def include():
    return """
#include <x86intrin.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include <limits.h>
#include <string.h>
"""

def main():
    return """
int main(int argc, char **argv) {
  if (argc < 2) {
    printf("Not enough number of arguments\\n");
    return 1;
  }

  srand(0);
  if (strcmp(argv[1], "--measure") == 0) {
    if (argc < 3) {
      printf("Not enough number of arguments for measure mode\\n");
      return 1;
    }
    int n_iterations = atoi(argv[2]);
    printf("Measuring with %d iterations\\n", n_iterations);
    init();
    run(n_iterations);
    return 0;
  } else if (strcmp(argv[1], "--test") == 0) {
    printf("Testing\\n");
    if (check()) {
      printf("PASSED\\n");
      return 0;
    } else {
      printf("FAILED\\n");
      return 1;
    }
  } else if (strcmp(argv[1], "--checksum") == 0) {
    printf("Calculating checksum\\n");
    init();
    kernel();
    checksum();
    return 0;
  } else {
    printf("Unsupported command %s\\n", argv[1]);
    return 1;
  }
}
"""

def run():
    return """
void run(int n_iterations) {
  // assuming micro seconds
  if (CLOCKS_PER_SEC != 1000000) {
    printf("WARNING: CLOCK_PER_SEC=%ld. Expected micro seconds (1000000).", CLOCKS_PER_SEC);
  }

  int *runtimes = (int*)malloc(n_iterations * sizeof(int));

  for (int i = 0; i < n_iterations; ++i) {
    runtimes[i] = (int)kernel();
  }

  for (int i = 0; i < n_iterations; ++i) {
    printf("Iteration %d %d\\n", i+1, runtimes[i]);
  }
  free(runtimes);
}
"""
MAX_SIZE_PER_ARRAY = 501 * 501 * 501

def spaces(indent):
    return '  ' * indent


MAX_SIZE_PER_ARRAY = 500 * 500 * 500

# TODO: test program needs to be a different program
class SimpleFormatter:
    def __init__(self, test_program, ref_program=None):
        arrays, loop_vars = get_program_info(test_program)
        # TODO: check whether test program and ref program have the same array names, dimensions
        self.arrays = arrays
        self.loop_vars = loop_vars
        self.dimension_size = determine_dimension_size(arrays, MAX_SIZE_PER_ARRAY)
        self.indent = 0
        self.test_program = test_program

        # concretize
        self.c_test_program = SimpleConcretizer(test_program).concretize_program()
        self.c_ref_program = SimpleConcretizer(ref_program).concretize_program()

    def array_decl(self, ty, var, n_dimensions):
        ws = spaces(self.indent)
        return f'{ws}{ty} (*{var})' + (''.join([f'[{self.dimension_size}]' * n_dimensions]) + ';')
    def declare(self, ty, arrays):
        lines = []
        for array in sorted(arrays.keys()):
            lines.append(self.array_decl(ty, array, len(arrays[array])))
        return '\n'.join(lines)
    def declare_globals(self):
        lines = []
        lines.append(include())
        lines.append(self.declare('float', self.arrays))
        lines.append(frand())
        lines.append(irand())
        return '\n'.join(lines)

    def nested_loop(self, loop_vars, body_lines):
        lines = []
        # loop headers
        for loop_var in loop_vars:
            lines.append(loop_header(self.indent, loop_var, 0, self.dimension_size))
            self.indent += 1
        ws = spaces(self.indent)
        for body_line in body_lines:
            lines.append(f'{ws}{body_line}')

        # close brackets
        for _ in range(len(loop_vars)):
            self.indent -= 1
            lines.append('  ' * self.indent + '}')
        return '\n'.join(lines)

    def checksum(self):
        lines = []
        ws = spaces(self.indent)
        lines.append(f'{ws}void checksum() {{')

        self.indent += 1
        ws = spaces(self.indent)

        lines.append(f'{ws}float total = 0.0;')
        for array, loop_vars in self.arrays.items():
            # loop_vars = self.loop_vars[array]
            indices_str = ''.join([f'[{loop_var}]' for loop_var in loop_vars])
            body_lines = [f'total += (*{array}){indices_str};']
            lines.append(self.nested_loop(loop_vars, body_lines))

        lines.append(f'{ws}printf("Checksum is %f\\n", total);')
        self.indent -= 1
        ws = spaces(self.indent)
        lines.append(f'{ws}}}')
        return '\n'.join(lines)

    def array_init(self, ty, arrays, mentioned_loop_vars, init_value):
        lines = []
        ws = spaces(self.indent)
        n_dimensions = len(mentioned_loop_vars)

        # malloc
        total_size_str = ' * '.join([f'{self.dimension_size}'] * n_dimensions)
        for array in arrays:
            lines.append(f'{ws}{array} = malloc(sizeof({ty}) * {total_size_str});')

        # loop headers
        for loop_var in mentioned_loop_vars:
            lines.append(loop_header(self.indent, loop_var, 0, self.dimension_size))
            self.indent += 1

        # loop body
        ws = spaces(self.indent)
        init_var = 'v'
        init_stmt = f'{ws}{ty} {init_var} = {init_value};'
        lines.append(init_stmt)
        indices_str = ''.join([f'[{loop_var}]' for loop_var in mentioned_loop_vars])
        for array in arrays:
            lines.append(f'{ws}(*{array}){indices_str} = {init_var};')
        # lines.append(f'{ws}(*{test_array}){indices_str} = {init_var};')

        # close brackets
        for _ in range(len(mentioned_loop_vars)):
            self.indent -= 1
            lines.append('  ' * self.indent + '}')

        return '\n'.join(lines)

    # TODO: create initialization program
    def init(self):
        lines = []

        # function header
        lines.append(f'void init() {{')
        self.indent += 1

        # Seed the randomizer
        ws = spaces(self.indent)
        init_value = 'frand(0.0, 1.0)'
        for array in sorted(self.arrays.keys()):
            lines.append(self.array_init('float', [array], self.arrays[array], init_value))

        # close function
        self.indent -= 1
        lines.append('}')

        return '\n'.join(lines)

    # TODO: create run program
    def run(self):
        return run()
    def main(self):
        return main()

    def kernel(self):
        lines = []
        ws = spaces(self.indent)
        lines.append(f'{ws}clock_t kernel() {{')
        self.indent += 1
        ws = spaces(self.indent)
        lines.append(f'{ws}clock_t before = clock();')
        lines.append(self.c_test_program.pprint(self.indent + 1))
        lines.append(f'{ws}clock_t after = clock();')
        lines.append(f'{ws}return after - before;')
        self.indent -= 1
        ws = spaces(self.indent)
        lines.append(f'{ws}}}')
        return '\n'.join(lines)
    def array_compare(self, test_array, ref_array, mentioned_loop_vars):
        lines = []
        # loop headers
        for loop_var in mentioned_loop_vars:
            lines.append(loop_header(self.indent, loop_var, 0, self.dimension_size))
            self.indent += 1

        # loop body
        ws = spaces(self.indent)

        indices_str = ''.join([f'[{loop_var}]' for loop_var in mentioned_loop_vars])
        lines.append(f'{ws}if ((*{test_array}){indices_str} != (*{ref_array}){indices_str}) return 0;')

        # close brackets
        for _ in range(len(mentioned_loop_vars)):
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
        for array in sorted(self.arrays.keys()):
            ref = array + '_ref'
            ref_program_rename_map[array] = ref
            test = array + '_test'
            test_program_rename_map[array] = test
            n_dimensions = len(self.arrays[array])
            lines.append(self.array_decl('int', ref, n_dimensions))
            lines.append(self.array_decl('int', test, n_dimensions))

        lines.append(f'{ws}// Initialization')
        for array in sorted(self.arrays.keys()):
            ref = array + '_ref'
            test = array + '_test'
            lines.append(self.array_init('int', [ref, test], self.arrays[array], 'irand(1, 10)'))

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
        for array in sorted(self.arrays.keys()):
            ref = array + '_ref'
            test = array + '_test'
            lines.append(self.array_compare(test, ref, self.arrays[array]))

        # if it reaches here, everything is good
        lines.append(f'{ws}return 1;')
        self.indent -= 1
        ws = spaces(self.indent)
        lines.append(f'{ws}}}')
        return '\n'.join(lines)

class SimpleConcretizer:
    def __init__(self, program):
        arrays, loop_vars = get_program_info(program)
        self.program = program
        self.array = arrays
        self.loop_vars = loop_vars
        self.dimension_size = determine_dimension_size(arrays, MAX_SIZE_PER_ARRAY)
        for var, (lower, upper) in loop_vars.items():
            assert(upper - lower < self.dimension_size)
    def concretize_program(self):
        return self.concretize(self.program)
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
            body = [self.concretize(stmt.clone()) for stmt in node.body]
            reversed_loop_vars = list(node.loop_vars)
            reversed_loop_vars.reverse()
            inner_loop = None
            for loop_var in reversed_loop_vars:
                start = 0 - self.loop_vars[loop_var][0]
                end = self.dimension_size - self.loop_vars[loop_var][1]
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
