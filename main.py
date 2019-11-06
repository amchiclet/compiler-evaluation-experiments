from enum import Enum, auto
from random import choice, choices

class AutoName(Enum):
  def _generate_next_value_(name, start, count, last_values):
    return name

class Relation(AutoName):
  EQUAL = auto()
  LESS = auto()
  GREATER = auto()
  INDIRECT = auto()
  INDEPENDENT = auto()

class AccessRelation:
  def __init__(self, ref_access, other_access, relation):
    self.ref_access = ref_access
    self.other_access = other_access
    self.relations = relations
    
class ArrayAccessExpr:
  def __init__(self, var, access):
    self.var = var
    self.access = access
  def __str__(self):
    return f'{self.var}[{self.access}]'

class BinaryExpr:
  def __init__(self, op, lhs, rhs):
    self.op = op
    self.lhs = lhs
    self.rhs = rhs
  def __str__(self):
    return f'({self.lhs} {self.op} {self.rhs})'

class AssignStmt:
  def __init__(self, lhs, rhs):
    self.lhs = lhs
    self.rhs = rhs
  def __str__(self):
    return f'{self.lhs} = {self.rhs}'

class Var:
  def __init__(self, name, dimensions):
    self.name = name
    self.dimensions = dimensions
  def __str__(self):
    return f'{self.name}'

def generate_var():

  var_name = choice(['A', 'B'])
  return Var(var_name, 2)

def generate_array_access_expr():
  var = generate_var()
  return ArrayAccessExpr(var, None)

def generate_binary_expr():
  op = choice(['+', '-', '*'])
  lhs = generate_array_access_expr()
  rhs = generate_array_access_expr()
  return BinaryExpr(op, lhs, rhs)

def generate_assignment():
  lhs = generate_array_access_expr()
  rhs = generate_binary_expr()
  return AssignStmt(lhs, rhs)

def generate_access_pattern(ast_template):
  assert(type(ast_template) == AssignStmt)
  assert(type(ast_template.lhs == ArrayAccessExpr))
  assert(type(ast_template.lhs.var == Var))
  n_dimensions = ast_template.lhs.var.dimensions
  relations = choices([Relation.EQUAL, Relation.LESS, Relation.GREATER],
                      k = n_dimensions)
  # force one of them to be equal
  print(relations)
  return ast_template

def emit_c(ast):
  print(ast)

def generate_program():
  ast_template = generate_assignment()
  ast = generate_access_pattern(ast_template)
  emit_c(ast)

generate_program()
