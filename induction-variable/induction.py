from generate import generate_loop_vars, generate_program, ARRAY_NAMES, TEST_ARRAY_NAMES
from ast import ScalarVar, AssignStmt, Literal, LoopIR, Substituter, BinaryExpr
from codegen import write_program_to_file, generate_meson_build_file, generate_benchmark_file
import argparse
from random import randint, sample

class IVMap:
  def __init__(self):
    self.iv_decls = []
    self.loop_var_map = {}

class IvDecl:
  def __init__(self, lhs, rhs):
    self.lhs = lhs
    self.rhs = rhs
  def __str__(self):
    return f'int {self.lhs} = {self.rhs}'
  def format_c(self):
    return f'int {self.lhs.format_c()} = {self.rhs.format_c()};'
  # don't rename iv declarations
  def rename(self, rename_map):
    return IvDecl(self.lhs, self.rhs)

class IvUpdateStmt:
  def __init__(self, lhs, rhs):
    self.lhs = lhs
    self.rhs = rhs
  def format_c(self):
    return f'{self.lhs.format_c()} = {self.rhs.format_c()};'
  def rename(self, rename_map):
    return IvUpdateStmt(self.lhs, self.rhs)
  def substitute(self, substituter):
    return IvUpdateStmt(self.lhs, self.rhs)
  def get_array_access_exprs(self):
    return []

class LoopVarSubstituter(Substituter):
  def __init__(self, substitute_map, indices):
    self.current_index = 0
    self.substitute_map = substitute_map
    self.indices_to_rename = indices
  def increment_index(self):
    self.current_index += 1
  def substitute(self, ast):
    substituted = ast
    renamed = False
    if self.current_index not in self.indices_to_rename:
      renamed = False
    else:
      renamed = True
      substituted = ast.substitute(self)
    print(f'renamed index {self.current_index}')
    return substituted

iv_count = 0
def reset_iv_var():
  global iv_count
  iv_count = 0

def fresh_iv_var():
  global iv_count
  var_name = f'iv_{iv_count}'
  iv_count += 1
  return ScalarVar(var_name)

def debug_str(program_ir):
  s = []
  for ir in program_ir:
    s.append(str(ir))
    # s.append('[' + ','.join([v.name for v in loop_ir.loop_vars]) + ']')
  return ' '.join(s)

def generate_loop_ir(loop_vars, body, iv_map):
  if len(loop_vars) == 0:
    return body

  # insert induction variable assignment
  n_strategies = 2
  strategy = randint(0, n_strategies - 1)
  iv_var = fresh_iv_var()


  # strategy 0 increment by 1, substitute with iv
  # strategy 1 offset by 3 increment by 1, substitute with iv - 3
  # strategy 2 increment by 2, substitute with iv / 2
  # otherwise update in sync with loop var
  strategy = randint(0, 2)
  if strategy == 0:
    iv_map.loop_var_map[loop_vars[0].name] = ScalarVar(iv_var.name)
    iv_map.iv_decls.append(IvDecl(iv_var, Literal(1)))
    new_body = generate_loop_ir(loop_vars[1:], body, iv_map)
    iv_update = IvUpdateStmt(iv_var, BinaryExpr('+', iv_var, Literal(1)))
    loop_ir = [LoopIR([loop_vars[0]], new_body + [iv_update])]
  elif strategy == 1:
    offset = randint(3, 33)
    increment = randint(5, 55)

    print(f'offset {offset}, increment {increment}')
    minus_offset = BinaryExpr('-', ScalarVar(iv_var.name), Literal(offset))
    sub = BinaryExpr('/', minus_offset, Literal(increment))
    iv_map.loop_var_map[loop_vars[0].name] = sub

    initial_offset = BinaryExpr('+', Literal(offset), Literal(increment))
    iv_map.iv_decls.append(IvDecl(iv_var, initial_offset))
    new_body = generate_loop_ir(loop_vars[1:], body, iv_map)

    increment_iv = BinaryExpr('+', iv_var, Literal(increment))
    iv_update = IvUpdateStmt(iv_var, increment_iv)
    loop_ir = [LoopIR([loop_vars[0]], new_body + [iv_update])]
  else:
    iv_map.loop_var_map[loop_vars[0].name] = ScalarVar(iv_var.name)
    iv_map.iv_decls.append(IvDecl(iv_var, Literal(0)))
    new_body = generate_loop_ir(loop_vars[1:], body, iv_map)
    iv_update = IvUpdateStmt(iv_var, loop_vars[0])
    loop_ir = [LoopIR([loop_vars[0]], [iv_update] + new_body)]

  return loop_ir

def generate_variant_program_ir(program, loop_vars, n_dimensions):
  program_ir = []
  iv_decls = []
  for assign_stmt in program:
    # print('*** Assignment ***')
    # print(assign_stmt.format_c())
    reset_iv_var()
    iv_map = IVMap()
    irs = generate_loop_ir(loop_vars, [assign_stmt], iv_map)
    # print(iv_map.loop_var_map)
    for ir in irs:
      # randomize how many to rename and which ones
      access_exprs = ir.get_array_access_exprs()
      n_exprs = len(access_exprs)
      renamed_ir = ir
      for loop_var in iv_map.loop_var_map:
        # pick at least 1 place to rename
        n_renames = randint(1, n_exprs)
        all_indices = [x for x in range(n_exprs)]
        indices_to_rename = sample(all_indices, k=n_renames)
        loop_var_map = {loop_var : iv_map.loop_var_map[loop_var]}
        substituter = LoopVarSubstituter(loop_var_map, indices_to_rename)
        print(f'indices to rename {indices_to_rename}')
        renamed_ir = renamed_ir.substitute(substituter)
      program_ir.append(renamed_ir)
    iv_decls += iv_map.iv_decls
    # print('=====================')

  return iv_decls + program_ir

def generate_program_and_variants(filename_prefix, program_index, max_variants, benchmarks):
  # TODO: make these program arguments
  n_statements = 1
  n_dimensions = 3

  loop_vars = generate_loop_vars(n_dimensions)
  program = generate_program(n_statements, n_dimensions, loop_vars)

  # Variant 0 is the original program with no transformations
  program_ir = [LoopIR(loop_vars, [stmt]) for stmt in program]
  variants = [program_ir]

  # iv_decls = []
  # for stmt in program:
  #   variants = [LoopIR(loop_vars, [stmt])]
  #   reset_iv_var()
  #   iv_map = IVMap()
  #   ir = generate_loop_ir(loop_vars, [stmt], iv_map)
  #   program_ir += ir
  #   iv_decls += iv_map.iv_decls
  # variants = [iv_decls + program_ir]

  for i in range(max_variants):
    variant = generate_variant_program_ir(program, loop_vars, n_dimensions)
    variants.append(variant)

  rename_map = {src:dst for src, dst in zip(ARRAY_NAMES, TEST_ARRAY_NAMES)}
  test_program_ir = [LoopIR(loop_vars, [assign_stmt.rename(rename_map)])
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
