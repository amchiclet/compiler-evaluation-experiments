from ast import LoopIR, LoopIREx

SIZE = 500
SIZE_STR = str(SIZE)
BEGIN_STR = '1'
END_STR = f'{SIZE-1}'

def format_loop_header(i, start, end, step):
  if step == 1:
    return f'for (int {i} = {start}; {i} < {end}; ++{i})'
  else:
    return f'for (int {i} = {start}; {i} < {end}; {i}+={step})'

def format_loop_ex(n_indent, loop_vars, loop_properties, body):
  print('printing body =============')
  print(body)
  if len(loop_vars) == 0:
    indentation = n_indent * '  '
    formatted = []
    for stmt in body:
      if type(stmt) == LoopIR:
        default_loop_properties = [LoopProperty(1, SIZE-1, 1)] * len(stmt.loop_vars)
        formatted.append(format_loop_ex(n_indent, stmt.loop_vars, default_loop_properties, stmt.body))
      elif type(stmt) == LoopIREx:
        formatted.append(format_loop_ex(n_indent, stmt.loop_vars, stmt.loop_properties, stmt.body))
      else:
        print(stmt)
        formatted.append(f'{indentation}{stmt.format_c()}')
    return '\n'.join(formatted)
  indentation = n_indent * '  '
  loop_header = format_loop_header(loop_vars[0].name,
                                   loop_properties[0].begin,
                                   loop_properties[0].end,
                                   loop_properties[0].step)
  inner = format_loop_ex(n_indent + 1, loop_vars[1:], loop_properties[1:], body)
  return f'{indentation}{loop_header} {{\n{inner}\n{indentation}}}'

# def format_loop(n_indent, loop_vars, body):
#   if len(loop_vars) == 0:
#     indentation = n_indent * '  '
#     formatted = []
#     for stmt in body:
#       if type(stmt) == LoopIR:
#         formatted.append(format_loop(n_indent, stmt.loop_vars, stmt.body))
#       else:
#         print(stmt)
#         formatted.append(f'{indentation}{stmt.format_c()}')
#     return '\n'.join(formatted)
#   indentation = n_indent * '  '
#   loop_header = format_loop_header(loop_vars[0].name, 1, SIZE-1, 1)
#   inner = format_loop(n_indent + 1, loop_vars[1:], body)
#   return f'{indentation}{loop_header} {{\n{inner}\n{indentation}}}'

def format_kernel(loop_vars, program):
  kernel = []
  for stmt in program:
    # perform loop interchange on loop vars
    kernel.append(format_loop(1, loop_vars, [stmt]))
  return '\n'.join(kernel)

def format_typedef(n_indent, type_name, n_dimensions):
  indentation = n_indent * '  '
  return f'{indentation}typedef float {type_name}{("[" + SIZE_STR + "]") * n_dimensions};'

def format_array_decl(n_indent, type_name, array_name, n_dimensions):
  indentation = n_indent * '  '
  return f'{indentation}{type_name} * restrict {array_name} = NULL;'

def format_array_decls(n_indent, type_name, array_names, n_dimensions):
  decls = []
  # decls.append(format_typedef(n_indent, type_name, n_dimensions))
  for array_name in array_names:
    decls.append(format_array_decl(n_indent, type_name, array_name, n_dimensions))
  return '\n'.join(decls)

def format_alloc(n_indent, type_name, array_name):
  indentation = n_indent * '  '
  return f'{indentation}{array_name} = malloc(sizeof({type_name}));'

def format_allocs(n_indent, type_name, array_names):
  allocs = []
  for array_name in array_names:
    allocs.append(format_alloc(n_indent, type_name, array_name))
  return '\n'.join(allocs)

def format_compare(expect, actual, n_dimensions):
  return f'compare_{n_dimensions}d((float*){expect}, (float*){actual}, {BEGIN_STR}, {END_STR}, {SIZE_STR}, {BEGIN_STR}, {END_STR}, {SIZE_STR}, {BEGIN_STR}, {END_STR}, {SIZE_STR}, tolerance)'

def format_compares(n_indent, array_names, test_array_names, n_dimensions):
  indentation = n_indent * '  '
  lines = [f'{indentation}int pass = 1;']
  for expect, actual in zip(array_names, test_array_names):
    compare = format_compare(expect, actual, n_dimensions)
    lines.append(f'{indentation}pass = pass && {compare};')
  return '\n'.join(lines)

def format_init(n_indent, array_name, n_dimensions):
  indentation = n_indent * '  '
  return f'{indentation}init_{n_dimensions}d((float*){array_name}, {", ".join([SIZE_STR]*n_dimensions)});'

def format_inits(n_indent, array_names, n_dimensions):
  inits = []
  for array_name in array_names:
    inits.append(format_init(n_indent, array_name, n_dimensions))
  return '\n'.join(inits)

def format_copy(n_indent, src, dst, n_dimensions):
  indentation = n_indent * '  '
  return f'{indentation}copy_{n_dimensions}d((float*){src}, (float*){dst}, {", ".join([SIZE_STR]*n_dimensions)});'

def format_copies(n_indent, src_names, dst_names, n_dimensions):
  copies = []
  for src, dst in zip(src_names, dst_names):
    copies.append(format_copy(n_indent, src, dst, n_dimensions))
  return '\n'.join(copies)

def format_program_ir_simple(program_ir):
  formatted_kernel = []
  for ir in program_ir:
    if type(ir) == LoopIR:
      loop_properties = [LoopProperty(1, SIZE-1, 1)] * len(ir.loop_vars)
      formatted = format_loop_ex(1, ir.loop_vars, loop_properties, ir.body)
    elif type(ir) == LoopIREx:
      formatted = format_loop_ex(1, ir.loop_vars, ir.loop_properties, ir.body)
    else:
      formatted = '  ' + ir.format_c()
    formatted_kernel.append(formatted)
  return '\n'.join(formatted_kernel)
