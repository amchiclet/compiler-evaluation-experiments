from format import format_array_decls, format_inits, format_kernel, format_loop, format_program_ir_simple, format_typedef, format_copies, format_allocs, format_compares

from util import get_file_contents, set_file_contents

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
