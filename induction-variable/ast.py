from enum import Enum, auto
import copy

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
    access_strs = [str(i) for i in self.access]
    return f'{self.var}[{", ".join(access_strs)}]'
  def get_array_access_exprs(self):
    return [self]
  def get_array_names(self):
    return [self.var.name]
  def format_c(self):
    access_strs = [i.format_c() for i in self.access]
    return f'(*{self.var.format_c()})[{"][".join(access_strs)}]'
  def rename(self, rename_map):
    renamed_access = [d.rename(rename_map)
                      if d is not None else None
                      for d in self.access]
    return ArrayAccessExpr(self.var.rename(rename_map), renamed_access)
  def substitute(self, substituter):
    renamed_access = [substituter.substitute(d)
                      if d is not None else None
                      for d in self.access]
    renamed_expr = ArrayAccessExpr(substituter.substitute(self.var), renamed_access)
    substituter.increment_index()
    return renamed_expr

class BinaryExpr:
  def __init__(self, op, lhs, rhs):
    self.op = op
    self.lhs = lhs
    self.rhs = rhs
  def __str__(self):
    return f'({self.lhs} {self.op} {self.rhs})'
  def get_array_access_exprs(self):
    return self.lhs.get_array_access_exprs() + self.rhs.get_array_access_exprs()
  def evaluate(self, valuation):
    if self.op == '-':
      return self.lhs.evaluate(valuation) - self.rhs.evaluate(valuation)
    if self.op == '+':
      return self.lhs.evaluate(valuation) + self.rhs.evaluate(valuation)
    if self.op == '*':
      return self.lhs.evaluate(valuation) * self.rhs.evaluate(valuation)
    raise UnimplementedError('Unsupported operation {self.op}')
  def get_array_names(self):
    return self.lhs.get_array_names() + self.rhs.get_array_names()
  def format_c(self):
    return f'({self.lhs.format_c()} {self.op} {self.rhs.format_c()})'
  def rename(self, rename_map):
    return BinaryExpr(self.op,
                      self.lhs.rename(rename_map),
                      self.rhs.rename(rename_map))
  def substitute(self, substituter):
    return BinaryExpr(self.op,
                      self.lhs.substitute(substituter),
                      self.rhs.substitute(substituter))

class AssignStmt:
  def __init__(self, lhs, rhs):
    self.lhs = lhs
    self.rhs = rhs
    self.dep_matrix = []
  def __str__(self):
    return f'{self.lhs} = {self.rhs}'
  def get_array_access_exprs(self):
    return self.lhs.get_array_access_exprs() + self.rhs.get_array_access_exprs()
  def get_array_names(self):
    return self.lhs.get_array_names() + self.rhs.get_array_names()
  def format_c(self):
    return f'{self.lhs.format_c()} = {self.rhs.format_c()};'
  def rename(self, rename_map):
    renamed = AssignStmt(self.lhs.rename(rename_map),
                         self.rhs.rename(rename_map))
    renamed.dep_matrix = copy.deepcopy(self.dep_matrix)
    return renamed
  def substitute(self, substituter):
    renamed = AssignStmt(self.lhs.substitute(substituter),
                         self.rhs.substitute(substituter))
    renamed.dep_matrix = copy.deepcopy(self.dep_matrix)
    return renamed

def format_loop_header(i, start, end):
  return f'for (int {i} = {start}; {i} < {end}; ++{i})'

class Literal:
  def __init__(self, c):
    self.c = c
  def __str__(self):
    return f'{self.c}'
  def get_array_access_exprs(self):
    return []
  def evaluate(self, valuation):
    return self.c
  def get_array_names(self):
    return []
  def format_c(self):
    return f'{self.c}'
  def rename(self, rename_map):
    return Literal(self.c)
  def substitute(self, substituter):
    return Literal(self.c)

class ScalarVar:
  def __init__(self, name):
    self.name = name
  def __str__(self):
    return f'{self.name}'
  def get_array_access_exprs(self):
    return []
  def evaluate(self, valuation):
    return valuation[name]
  def get_array_names(self):
    return []
  def format_c(self):
    return f'{self.name}'
  def rename(self, rename_map):
    print(f'checking {self.name}')
    if self.name in rename_map:
      print(f'renaming {self.name} to {rename_map[self.name]}')
      return ScalarVar(rename_map[self.name])
    else:
      print('not renaming')
      return ScalarVar(self.name)
  def substitute(self, substituter):
    if self.name in substituter.substitute_map:
      return substituter.substitute_map[self.name]
    else:
      return ScalarVar(self.name)

class ArrayVar:
  def __init__(self, name, n_dimensions):
    self.name = name
    self.n_dimensions = n_dimensions
  def __str__(self):
    return f'{self.name}'
  def get_array_access_exprs(self):
    return []
  def get_array_names(self):
    return [self.name]
  def format_c(self):
    return f'{self.name}'
  def rename(self, rename_map):
    if self.name in rename_map:
      return ArrayVar(rename_map[self.name], self.n_dimensions)
    else:
      return ArrayVar(self.name, self.n_dimensions)
  def substitute(self, substituter):
    if self.name in substituter.substitute_map:
      v = substituter.substitute_map[self.name]
      print(f'substituting {self} for {v}')
      return v
    else:
      return ArrayVar(self.name, self.n_dimensions)

class LoopIR:
  def __init__(self, loop_vars, body):
    self.loop_vars = loop_vars
    self.body = body
  def rename(self, rename_map):
    return LoopIR(self.loop_vars,
                  [stmt.rename(rename_map) for stmt in self.body])
  def get_array_access_exprs(self):
    exprs = []
    for stmt in self.body:
      exprs += stmt.get_array_access_exprs()
    return exprs
  def substitute(self, substituter):
    return LoopIR(self.loop_vars,
                  [stmt.substitute(substituter) for stmt in self.body])

class Substituter:
  def substitute(self, ast):
    pass