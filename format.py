SIZE = 500
SIZE_STR = '500'

def format_loop_header(i, start, end):
  return f'for (int {i} = {start}; {i} < {end}; ++{i})'

def format_loop(n_indent, loop_vars, body):
  if len(loop_vars) == 0:
    indentation = n_indent * '  '
    formatted = []
    for stmt in body:
      formatted.append(f'{indentation}{stmt.format_c()}')
    return '\n'.join(formatted)
  indentation = n_indent * '  '
  loop_header = format_loop_header(loop_vars[0].name, 1, SIZE-1)
  inner = format_loop(n_indent + 1, loop_vars[1:], body)
  return f'{indentation}{loop_header} {{\n{inner}\n{indentation}}}'

def format_kernel(loop_vars, program):
  kernel = []
  for stmt in program:
    # perform loop interchange on loop vars
    kernel.append(format_loop(1, loop_vars, [stmt]))
  return '\n'.join(kernel)

def format_array_decl(n_indent, array_name, n_dimensions):
  indentation = n_indent * '  '
  return f'{indentation}float {array_name}{("[" + SIZE_STR + "]") * n_dimensions};'

def format_array_decls(n_indent, array_names, n_dimensions):
  decls = []
  for array_name in array_names:
    decls.append(format_array_decl(n_indent, array_name, n_dimensions))
  return '\n'.join(decls)

def format_init(n_indent, array_name, n_dimensions):
  indentation = n_indent * '  '
  return f'{indentation}init_{n_dimensions}d((float*){array_name}, {", ".join([SIZE_STR]*n_dimensions)});'

def format_inits(n_indent, array_names, n_dimensions):
  inits = []
  for array_name in array_names:
    inits.append(format_init(n_indent, array_name, n_dimensions))
  return '\n'.join(inits)

def format_program(array_names, dimensions, loop_vars, program):
  decls = format_array_decls(0, ARRAY_NAMES, n_dimensions)
  inits = format_inits(1, ARRAY_NAMES, n_dimensions)
  kernel = format_kernel(loop_vars, program)

  template = get_file_contents('run.c.template')
  code = template.replace('///DECLARE_ARRAY', decls) \
                 .replace('///INITIALIZE', inits) \
                 .replace('///KERNEL', kernel)

  # output_path = 'generated.c'
  # set_file_contents(output_path, code)
  # print(f'Wrote code to {output_path}.')
