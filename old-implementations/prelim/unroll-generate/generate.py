from random import choice, choices, shuffle, uniform

from ast import Relation, AccessRelation, ArrayAccessExpr, BinaryExpr, AssignStmt, Literal, ScalarVar, ArrayVar, LoopIR

ARRAY_NAMES = ['A', 'B', 'C']
SCALAR_NAMES = ['iv']
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

def generate_literal():
  f = uniform(0.001, 0.999)
  return Literal(f)

def generate_binary_expr(n_dimensions):
  op = choice(['+', '-', '*'])
  lhs = generate_array_access_expr(n_dimensions)
  rhs = generate_array_access_expr(n_dimensions)
  return BinaryExpr(op, lhs, rhs)

def generate_scalar_var():
  var_name = choice(SCALAR_NAMES)
  return ScalarVar(var_name)

def generate_scalar_assignment(n_dimensions):
  lhs = generate_scalar_var()
  rhs = generate_binary_expr(n_dimensions)
  return AssignStmt(lhs, rhs)

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
  return [ScalarVar(f'i_{d}')
          for d in range(n_dimensions)]

def generate_program(n_statements, n_dimensions, loop_vars):
  print('*** Generating program ***')
  program = []
  for _ in range(n_statements):
    assign_stmt = generate_assignment(n_dimensions)
    generate_access_pattern_lhs(assign_stmt.lhs, loop_vars)
    for rhs_access_expr in assign_stmt.rhs.get_array_access_exprs():
      generate_access_pattern_rhs(assign_stmt, rhs_access_expr, loop_vars)
    # print(assign_stmt)
    # print(assign_stmt.dep_matrix)
    program.append(assign_stmt)
  return program
