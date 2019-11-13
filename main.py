from random import choice, choices, shuffle
from ast import Relation, AccessRelation, ArrayAccessExpr, BinaryExpr, AssignStmt, Literal, ScalarVar, ArrayVar
from format import format_array_decls, format_inits, format_kernel, format_loop
from util import get_file_contents, set_file_contents
import argparse

ARRAY_NAMES = ['A', 'B', 'C']

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
    relations.append(Relation.EQUAL)
    dimension_order.append(n_dimensions-1)
    shuffle(relations)
    shuffle(dimension_order)

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
  return [loop_vars[i] for i in legal_ordering]

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
  program = []
  for _ in range(n_statements):
    assign_stmt = generate_assignment(n_dimensions)
    generate_access_pattern_lhs(assign_stmt.lhs, loop_vars)
    for rhs_access_expr in assign_stmt.rhs.get_array_access_exprs():
      generate_access_pattern_rhs(assign_stmt, rhs_access_expr, loop_vars)
    print('*** Generated assignment ***')
    print(assign_stmt)
    print(assign_stmt.dep_matrix)
    program.append(assign_stmt)
  return program

def main(args):
  # TODO: make these program arguments
  n_statements = 2
  n_dimensions = 3
  loop_vars = generate_loop_vars(n_dimensions)
  program = generate_program(n_statements, n_dimensions, loop_vars)

  # Variant 0 is the original program with no loops interchanged
  program_ir = [LoopIR(loop_vars, assign_stmt) for assign_stmt in program]
  variants = [program_ir]

  for i in range(args.max_variants):
    variants.append(generate_variant_program_ir(program, loop_vars))

  for i in range(len(variants)):
    program_ir = variants[i]
    print('=======================')
    print(f'VARIANT {i}')
    formatted_kernel = []
    for loop_ir in program_ir:
      formatted_loop = format_loop(1, loop_ir.loop_vars, [loop_ir.assign_stmt])
      formatted_kernel.append(formatted_loop)
    print('\n'.join(formatted_kernel))

if __name__ == '__main__':
  parser = argparse.ArgumentParser()
  parser.add_argument('--prefix')
  parser.add_argument('--max_variants', type=int, default=5)
  args = parser.parse_args()
  main(args)

# TODO
# * randomize n_statements, n_dimensions
# * infer array size + loop sizes
# * generate multiple programs and build script
# * factor out generation and 
