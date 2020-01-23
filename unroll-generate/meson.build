project('benchmarks', 'c')

benchmarks = [
  'test.p00.v00.c',
  'test.p00.v01.c',
  'test.p00.v02.c',
  'test.p00.v03.c',
  'test.p00.v04.c',
  'test.p00.v05.c',
  'test.p00.v06.c',
  'test.p00.v07.c',
  'test.p00.v08.c',
  'test.p00.v09.c',
  'test.p00.v10.c',
  'test.p01.v00.c',
  'test.p01.v01.c',
  'test.p01.v02.c',
  'test.p01.v03.c',
  'test.p01.v04.c',
  'test.p01.v05.c',
  'test.p01.v06.c',
  'test.p01.v07.c',
  'test.p01.v08.c',
  'test.p01.v09.c',
  'test.p01.v10.c',
  'test.p02.v00.c',
  'test.p02.v01.c',
  'test.p02.v02.c',
  'test.p02.v03.c',
  'test.p02.v04.c',
  'test.p02.v05.c',
  'test.p02.v06.c',
  'test.p02.v07.c',
  'test.p02.v08.c',
  'test.p02.v09.c',
  'test.p02.v10.c',
  'test.p03.v00.c',
  'test.p03.v01.c',
  'test.p03.v02.c',
  'test.p03.v03.c',
  'test.p03.v04.c',
  'test.p03.v05.c',
  'test.p03.v06.c',
  'test.p03.v07.c',
  'test.p03.v08.c',
  'test.p03.v09.c',
  'test.p03.v10.c',
  'test.p04.v00.c',
  'test.p04.v01.c',
  'test.p04.v02.c',
  'test.p04.v03.c',
  'test.p04.v04.c',
  'test.p04.v05.c',
  'test.p04.v06.c',
  'test.p04.v07.c',
  'test.p04.v08.c',
  'test.p04.v09.c',
  'test.p04.v10.c',
  'test.p05.v00.c',
  'test.p05.v01.c',
  'test.p05.v02.c',
  'test.p05.v03.c',
  'test.p05.v04.c',
  'test.p05.v05.c',
  'test.p05.v06.c',
  'test.p05.v07.c',
  'test.p05.v08.c',
  'test.p05.v09.c',
  'test.p05.v10.c',
  'test.p06.v00.c',
  'test.p06.v01.c',
  'test.p06.v02.c',
  'test.p06.v03.c',
  'test.p06.v04.c',
  'test.p06.v05.c',
  'test.p06.v06.c',
  'test.p06.v07.c',
  'test.p06.v08.c',
  'test.p06.v09.c',
  'test.p06.v10.c',
  'test.p07.v00.c',
  'test.p07.v01.c',
  'test.p07.v02.c',
  'test.p07.v03.c',
  'test.p07.v04.c',
  'test.p07.v05.c',
  'test.p07.v06.c',
  'test.p07.v07.c',
  'test.p07.v08.c',
  'test.p07.v09.c',
  'test.p07.v10.c',
  'test.p08.v00.c',
  'test.p08.v01.c',
  'test.p08.v02.c',
  'test.p08.v03.c',
  'test.p08.v04.c',
  'test.p08.v05.c',
  'test.p08.v06.c',
  'test.p08.v07.c',
  'test.p08.v08.c',
  'test.p08.v09.c',
  'test.p08.v10.c',
  'test.p09.v00.c',
  'test.p09.v01.c',
  'test.p09.v02.c',
  'test.p09.v03.c',
  'test.p09.v04.c',
  'test.p09.v05.c',
  'test.p09.v06.c',
  'test.p09.v07.c',
  'test.p09.v08.c',
  'test.p09.v09.c',
  'test.p09.v10.c'
]
compile_opts = []
link_opts = ['-lm']

compiler = meson.get_compiler('c')
compiler_id = compiler.get_id()
compiler_command = compiler.cmd_array()

# # Hack to pass an argument to meson
# # Using localedir to check for the handtuned option
# # Using infodif to check for assembly generation option
# is_handtuned = get_option('localedir') == 'handtuned'

also_gen_assembly = get_option('infodir') == 'also_gen_assembly'
no_optimization = get_option('localstatedir') == 'no_optimization'
no_vec = get_option('localstatedir') == 'no_vec'

message('Detected compiler: ' + compiler_id)

# TODO use more aggressive options to vectorize
if compiler_id == 'pgi'
  compile_opts += ['-Minfo']
  optimization = ['-fast']
elif compiler_id == 'gcc'
  compile_opts += ['-march=native']
  optimization = ['-Ofast']
elif compiler_id == 'intel'
  # To use xCORE-AVX512, make sure to use -Ofast, not -fast
  compile_opts += ['-xCORE-AVX512', '-qopt-zmm-usage=high']
  optimization = ['-Ofast', '-ipo', '-static']

  # -fast means -Ofast, -ipo, -static, -xHost
  # compile_opts += ['-march=native']
  # optimization = ['-fast']
elif compiler_id == 'clang'
  #compile_opts += ['-march=skylake-avx512']
  compile_opts += ['-march=native']
  # llvm requires loop interchange to be enabled
  # (http://lists.llvm.org/pipermail/llvm-dev/2017-November/119186.html)
  optimization = ['-Ofast', '-mllvm', '-enable-loopinterchange']
endif

# override the optimization flag if "no optimization" is specified
if no_optimization
  optimization = ['-O0']
endif

if no_vec
  if compiler_id == 'pgi'
    optimization += ['-Mnovect']
  elif compiler_id == 'gcc'
    optimization += ['-fno-tree-vectorize']
  elif compiler_id == 'intel'
    optimization += ['-no-vec']
  elif compiler_id == 'clang'
    optimization += ['-fno-vectorize']
  endif
endif

# Always use O0 for the naive implementation
lib_optimization = ['-O0']

dummy_lib = static_library('dummy', 'dummy/dummy.c', cpp_args : compile_opts + lib_optimization)
util_lib = static_library('util', ['util/init.c'], cpp_args : compile_opts + lib_optimization)
test_lib = static_library('naive_impl', ['test/naive_impl.c', 'test/ulp.c'], cpp_args : compile_opts + lib_optimization)
argparse_lib = static_library('argparse', 'argparse/argparse.c', c_args : compile_opts + lib_optimization)

# assembly_opts = ['-S'] + compile_opts + optimization

foreach file : benchmarks
  message('Generating build scripts for ' + file)
  src = file
  exe = executable(file.underscorify(), src, link_with : [dummy_lib, util_lib, test_lib, argparse_lib], c_args : compile_opts + optimization, link_args : link_opts)
  custom_target(
    src.underscorify() + '.s',
    output : src.underscorify() + '.s',
    input : files(src),
    command : [compiler_command, '-S', '-I../..'] + compile_opts + optimization + ['@INPUT@'],
  )
endforeach
