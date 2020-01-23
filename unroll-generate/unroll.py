from generate import generate_loop_vars, generate_program, ARRAY_NAMES, TEST_ARRAY_NAMES
from ast import ScalarVar, AssignStmt, Literal, LoopIR, Substituter, BinaryExpr, LoopIREx, LoopProperty
from codegen import write_program_to_file, generate_meson_build_file, generate_benchmark_file
import argparse
from random import randint, sample, shuffle

from format import SIZE

def debug_str(program_ir):
  s = []
  for ir in program_ir:
    s.append(str(ir))
    # s.append('[' + ','.join([v.name for v in loop_ir.loop_vars]) + ']')
  return ' '.join(s)

class LoopVarSubstituter(Substituter):
  def __init__(self, substitute_map):
    self.substitute_map = substitute_map
  def increment_index(self):
    pass
  def substitute(self, ast):
    return ast.substitute(self)

def unroll_body(body, loop_var, unroll_factor):
  unrolled = []
  for i in range(unroll_factor):
    substitute_map = {loop_var.name : BinaryExpr('+', loop_var, Literal(i))}
    print(substitute_map)
    substituter = LoopVarSubstituter(substitute_map)
    unrolled_stmts = []
    for stmt in body:
      print('before')
      print(stmt)
      substituted = stmt.substitute(substituter)
      print('after')
      print(substituted)
      unrolled_stmts.append(substituted)
    unrolled += unrolled_stmts
  print('unrolled ===========')
  for s in unrolled:
    print(s)
  return unrolled
  
def generate_loop_ir_ex(should_unroll, loop_vars, body):
  if len(loop_vars) == 0:
    return body

  begin = 1
  end = SIZE - 1
  step = 1

  inner_body = generate_loop_ir_ex(should_unroll[1:], loop_vars[1:], body)
  if not should_unroll[0]:
    return [LoopIREx([loop_vars[0]],
                     [LoopProperty(begin, end, step)],
                     inner_body)]

  # Below is unrolling
  assert(should_unroll[0])

  unroll_factor = randint(2, 30)
  size = end - begin
  normalized_begin = 0
  normalized_end = (end - begin) // step
  normalized_step = 1
  n_iterations = normalized_end - normalized_begin
  n_middle = n_iterations // unroll_factor
  n_rest_from_unroll = n_iterations % unroll_factor
  n_before = randint(0, n_rest_from_unroll)
  n_after = n_rest_from_unroll - n_before
  before_begin_index = begin
  before_end_index = before_begin_index + n_before * step
  middle_begin_index = before_end_index
  middle_end_index = middle_begin_index + n_middle * step * unroll_factor
  after_begin_index = middle_end_index
  after_end_index = end

  if before_end_index == before_begin_index:
    before_loop = []
  else:
    before_loop = [LoopIREx([loop_vars[0]],
                            [LoopProperty(before_begin_index, before_end_index, 1)],
                            inner_body)]
  unrolled_body = unroll_body(inner_body, loop_vars[0], unroll_factor)
  middle_loop = [LoopIREx([loop_vars[0]],
                          [LoopProperty(middle_begin_index, middle_end_index, unroll_factor)],
                          unrolled_body)]
  if after_begin_index == after_end_index:
    after_loop = []
  else:
    after_loop = [LoopIREx([loop_vars[0]],
                           [LoopProperty(after_begin_index, after_end_index, 1)],
                           inner_body)]
  return before_loop + middle_loop + after_loop

  # new_body = generate_loop_ir_ex(loop_vars[1:], body)
  # # HARDCODED
  # return [LoopIREx([loop_vars[0]], [LoopProperty(1, SIZE-1, 1)], new_body)]

def generate_variant_program_ir(program, loop_vars, n_dimensions):
  program_ir = []
  for assign_stmt in program:
    # randomize
    # (1) unroll factor
    # (2) how to divide the leftovers
    loop_properties = []

    # For now only unroll / unroll and jam one loop
    should_unroll = [False] * len(loop_vars)
    should_unroll[-1] = True
    shuffle(should_unroll)

    loop_ir_ex = generate_loop_ir_ex(should_unroll, loop_vars, [assign_stmt])
    program_ir += loop_ir_ex
  return program_ir

def generate_program_and_variants(filename_prefix, program_index, max_variants, benchmarks):
  # TODO: make these program arguments
  n_statements = 1
  n_dimensions = 3

  loop_vars = generate_loop_vars(n_dimensions)
  program = generate_program(n_statements, n_dimensions, loop_vars)

  # Variant 0 is the original program with no transformations
  default_loop_properties = [LoopProperty(1, SIZE-1, 1)] * len(loop_vars)
  program_ir = [LoopIREx(loop_vars, default_loop_properties, [stmt]) for stmt in program]
  variants = [program_ir]

  for i in range(max_variants):
    variant = generate_variant_program_ir(program, loop_vars, n_dimensions)
    print('got variant ===============')
    print(debug_str(variant))
    variants.append(variant)

  rename_map = {src:dst for src, dst in zip(ARRAY_NAMES, TEST_ARRAY_NAMES)}
  test_program_ir = [LoopIREx(loop_vars, default_loop_properties, [assign_stmt.rename(rename_map)])
                     for assign_stmt in program]

  for variant_index in range(len(variants)):
    path = f'{filename_prefix}.p{program_index:02d}.v{variant_index:02d}.c'
    benchmarks.append(path)
    program_ir = variants[variant_index]
    write_program_to_file(ARRAY_NAMES,
                          TEST_ARRAY_NAMES,
                          n_dimensions,
                          program_ir,
                          test_program_ir,
                          path)
    print(f'Wrote program to file {path}.')

def main(args):
  benchmarks = []
  for program_index in range(args.max_programs):
    generate_program_and_variants(args.filename_prefix,
                                  program_index,
                                  args.max_variants,
                                  benchmarks)
  generate_meson_build_file(benchmarks)
  generate_benchmark_file(benchmarks)

if __name__ == '__main__':
  parser = argparse.ArgumentParser()
  parser.add_argument('--filename_prefix', required=True)
  parser.add_argument('--max_programs', type=int, default=1)
  parser.add_argument('--max_variants', type=int, default=1)
  args = parser.parse_args()
  main(args)

# TODO
# * randomize n_statements, n_dimensions
# * infer array size + loop sizes
# * generate multiple programs and build script
# * factor out generation and 
# * how many ways to increment 1
#   * += 1
#   * += /2 increment 2
#   * += *2.0 increment 0.5
#   * += 
