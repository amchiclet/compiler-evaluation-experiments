from random import choice, choices, shuffle
from ast import Relation, AccessRelation, ArrayAccessExpr, BinaryExpr, AssignStmt, Literal, ScalarVar, ArrayVar
from format import format_array_decls, format_inits, format_kernel, format_loop, format_program_ir_simple, format_typedef, format_copies, format_allocs, format_compares
from util import get_file_contents, set_file_contents
import argparse

ARRAY_NAMES = ['A', 'B', 'C']
TEST_ARRAY_NAMES = [name + 'test' for name in ARRAY_NAMES]

def generate_index(i, relation):
  if relation == Relation.EQUAL:
    return i
  if relation == Relation.LESS:
    return BinaryExpr('-', i, Literal(1))
  if relation == Relation.GREATER:
    return BinaryExpr('+', i, Literal(1))
  raise NotImplementedError('Unimplemented index type')

# TODO: there should be two levels of randomness here
# (1) reuse an existing variable or introduce a new one
# (2) if reusing, which one
# (3) if not reusing, just pick the next fresh one (don't randomly choose)
def generate_array_var(n_dimensions):
  var_name = choice(ARRAY_NAMES)
  return ArrayVar(var_name, n_dimensions)

def generate_array_access_expr(n_dimensions):
  array_var = generate_array_var(n_dimensions)
  return ArrayAccessExpr(array_var, [None] * n_dimensions)

def generate_binary_expr(n_dimensions):
  op = choice(['+', '-', '*'])
  lhs = generate_array_access_expr(n_dimensions)
  rhs = generate_array_access_expr(n_dimensions)
  return BinaryExpr(op, lhs, rhs)

def generate_assignment(n_dimensions):
  lhs = generate_array_access_expr(n_dimensions)
  rhs = generate_binary_expr(n_dimensions)
  return AssignStmt(lhs, rhs)

def generate_access_pattern_lhs(access_expr, loop_vars):
  n_dimensions = len(loop_vars)
  assert(access_expr.var.n_dimensions == n_dimensions)
  for d in range(n_dimensions):
    access_expr.access[d] = loop_vars[d]

def generate_access_pattern_rhs(assignment, rhs, loop_vars):
  n_dimensions = len(loop_vars)
  assert(rhs.var.n_dimensions == n_dimensions)

  lhs = assignment.lhs

  # force one of them to be equal
  relations = choices([Relation.EQUAL, Relation.LESS, Relation.GREATER],
                      k = n_dimensions - 1)
  dimension_order = list(range(n_dimensions-1))

  # if the same variable appears on the right hand side,
  # make sure that the innermost dimension is always equal
  # this is to make sure that the statement is always vectorizable
  if lhs.var.name == rhs.var.name:
    shuffle(relations)
    # shuffle(dimension_order)
    relations.append(Relation.EQUAL)
    dimension_order.append(n_dimensions-1)
    assignment.dep_matrix.append(relations)
  else:
    shuffle(relations)
    shuffle(dimension_order)
    relations.append(Relation.EQUAL)
    dimension_order.append(n_dimensions-1)

  for i in range(n_dimensions):
    loop_var = loop_vars[i]
    dimension = dimension_order[i]
    relation = relations[i]
    rhs.access[dimension] = generate_index(loop_var, relation)

def generate_loop_vars(n_dimensions):
  return [ScalarVar(f'i{d}') for d in range(n_dimensions-1, -1, -1)]

def get_dependency_type(order, dep):
  for i in order:
    if dep[i] != Relation.EQUAL:
      return dep[i]
  return Relation.EQUAL

def is_legal(loop_vars, new_order, assignment):
  orig_order = list(range(len(loop_vars)))
  for dep in assignment.dep_matrix:
    if get_dependency_type(orig_order, dep) != get_dependency_type(new_order, dep):
      return False
  return True

def reorder_loop_vars(loop_vars, assignment):
  print('*** Reordering loops ***')
  order = list(range(len(loop_vars)))
  attemp = 0
  legal_ordering = list(order)
  for attempt in range(5):
    shuffle(order)
    if order == legal_ordering:
      continue
    if is_legal(loop_vars, order, assignment):
      print('LEGAL: ', [loop_vars[i].name for i in order])
      legal_ordering = order
      break
    else:
      print('ILLEGAL: ', [loop_vars[i].name for i in order])
      pass
  return [loop_vars[i] for i in legal_ordering]

def debug_str(program_ir):
  s = []
  for loop_ir in program_ir:
    s.append('[' + ','.join([v.name for v in loop_ir.loop_vars]) + ']')
  return ' '.join(s)

class LoopIR:
  def __init__(self, loop_vars, assign_stmt):
    self.loop_vars = loop_vars
    self.assign_stmt = assign_stmt    

def generate_variant_program_ir(program, loop_vars):
  program_ir = []
  for assign_stmt in program:
    print('*** Assignment ***')
    print(assign_stmt.format_c())
    reordered_loop_vars = reorder_loop_vars(loop_vars, assign_stmt)
    loop_ir = LoopIR(reordered_loop_vars, assign_stmt)
    program_ir.append(loop_ir)
    print('=====================')
  return program_ir

def generate_program(n_statements, n_dimensions, loop_vars):
  print('*** Generating program ***')
  program = []
  for _ in range(n_statements):
    assign_stmt = generate_assignment(n_dimensions)
    generate_access_pattern_lhs(assign_stmt.lhs, loop_vars)
    for rhs_access_expr in assign_stmt.rhs.get_array_access_exprs():
      generate_access_pattern_rhs(assign_stmt, rhs_access_expr, loop_vars)
    print(assign_stmt)
    print(assign_stmt.dep_matrix)
    program.append(assign_stmt)
  return program


def write_program_to_file(array_names, test_array_names, n_dimensions, program_ir, test_ir, path):
  type_name = f'Array{n_dimensions}D'

  all_arrays = array_names + test_array_names

  decls = format_typedef(0, type_name, n_dimensions) + '\n' + \
          format_array_decls(0, type_name, all_arrays, n_dimensions)

  inits = format_allocs(1, type_name, all_arrays) + '\n' + \
          format_inits(1, array_names, n_dimensions) + '\n' + \
          format_copies(1, array_names, test_array_names, n_dimensions)

  kernel = format_program_ir_simple(program_ir)

  test = format_program_ir_simple(test_ir) + '\n' + \
         format_compares(1, array_names, test_array_names, n_dimensions)

  template = get_file_contents('run.c.template')
  code = template.replace('///DECLARE_ARRAY', decls) \
                 .replace('///INITIALIZE', inits) \
                 .replace('///KERNEL', kernel) \
                 .replace('///TEST', test)
  set_file_contents(path, code)

def generate_meson_build_file(paths):
  template = get_file_contents('meson.template')
  formatted = ',\n'.join(["  '" + p + "'" for p in paths])
  script = template.replace('###BENCHMARKS', formatted)
  set_file_contents('meson.build', script)

def generate_benchmark_file(paths):
  formatted_paths = [f"    ('{p.replace('.', '_')}', 5)," for p in paths]
  file_content =  'executables = [\n' + '\n'.join(formatted_paths) + '\n]\n'
  set_file_contents('benchmarks.py', file_content)

def generate_program_and_variants(filename_prefix, program_index, max_variants, benchmarks):
  # TODO: make these program arguments
  n_statements = 1
  n_dimensions = 3

  loop_vars = generate_loop_vars(n_dimensions)
  program = generate_program(n_statements, n_dimensions, loop_vars)

  # Variant 0 is the original program with no loops interchanged  
  program_ir = [LoopIR(loop_vars, assign_stmt) for assign_stmt in program]
  variants = [program_ir]

  for i in range(max_variants):
    variant = generate_variant_program_ir(program, loop_vars)
    print(debug_str(variant))
    variants.append(variant)

  rename_map = {src:dst for src, dst in zip(ARRAY_NAMES, TEST_ARRAY_NAMES)}
  test_program_ir = [LoopIR(loop_vars, assign_stmt.rename(rename_map))
                     for assign_stmt in program]

  print('looping after')
  for variant_index in range(len(variants)):
    path = f'{filename_prefix}.p{program_index:02d}.v{variant_index:02d}.c'
    benchmarks.append(path)
    program_ir = variants[variant_index]
    print(debug_str(program_ir))
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
    generate_program_and_variants(args.filename_prefix, program_index, args.max_variants, benchmarks)
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
