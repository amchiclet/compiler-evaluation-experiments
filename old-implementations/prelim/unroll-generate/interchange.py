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
