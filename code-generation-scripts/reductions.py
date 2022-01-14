from api import Skeleton, Mapping, CodegenConfig
from random import randint, seed
from codelet_generator import codelet_dir, generate_codelet_files

skeleton_code = """
declare size;

declare Arr01[];
declare Arr02[];
declare Arr03[];
declare Arr04[];
declare Arr05[];
declare Arr06[];
declare Arr07[];
declare Arr08[];
declare Arr09[];
declare Arr10[];
declare Arr11[];
declare Arr12[];
declare Arr13[];
declare Arr14[];
declare Arr15[];
declare Arr16[];
declare Arr17[];
declare Arr18[];
declare Arr19[];
declare Arr20[];
declare Arr21[];
declare Arr22[];
declare Arr23[];
declare Arr24[];
declare Arr25[];
declare scalar1;
declare scalar2;
declare scalar3;
declare scalar4;
declare scalar5;

for [(i, >=0, <=size-1)] {
  $_$
  $_$
  $_$
  $_$
  $_$
}
"""

def gen_program(n_stmts, n_arrs):
    stmts = [
        Mapping(
            '_',
            [f'scalar{i} = scalar{i} * #_# + #_# * #_# + #_# * #_#;' for i in range(1, n_stmts + 1)] +
            [';'] * (5 - n_stmts),
            is_finite = True,
        )
    ]
    exprs = [
        Mapping('_', [f'Arr{i:02d}[i]' for i in range(1, n_arrs + 1)])
    ]
        
    program = Skeleton(skeleton_code)
    program = program.fill_statements(stmts)
    program = program.fill_expressions(exprs)
    return program

seed(0)
application = 'LoopGen'
batch = 'reduction'

programs = set()
for n_stmts in range(1, 6):
    n_generated = 0
    while n_generated < 5:
        n_arrs = randint(1, 25)
        if n_arrs > n_stmts * 5:
            continue
        if (n_stmts, n_arrs) in programs:
            continue
        n_generated += 1
        programs.add((n_stmts, n_arrs))
        program = gen_program(n_stmts, n_arrs)
        code = f'{n_stmts}_scalars_{n_arrs:02d}_arrays'
        codelet = f'{code}_de'

        config = CodegenConfig()
        config.possible_values = {
            **{f'Arr{i:02d}[]': 32000 for i in range(1, 26)},
            'size': 32000
        }
        config.types = { f'Arr{i:02d}': 'double' for i in range(1, 26) }
        config.initial_values = {
            **{ f'Arr{i:02d}' : 'drand(0.0, 1.0)' for i in range(1, 26) },
            'size': '32000',
        }
        config.template_dir = 'codelet-template-int-inputs'
        config.output_dir = generate_codelet_files(application, batch, code, codelet, 10, [])
        program.generate_code(config)
