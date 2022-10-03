from api import Skeleton, Mapping, CodegenConfig
from random import randint, seed
from codelet_generator import codelet_dir, generate_codelet_files, generate_batch_summary, SourceInfo
from pattern_ast import get_ordered_assignments, get_accesses, count_ops
from itertools import product

args = {
    'img': 512,
    'ifm': 5,
    'ofm': 5,
    'sh': 2,
    'sw': 2,
}

skeleton_code = """
declare IMG;
declare IFM;
declare OFM;
declare SH;
declare SW;

declare input[{img}][{ifm}][][];
declare output[{img}][{ofm}][][];
declare filter[{ofm}][{ifm}][][];

for [
  (img, >=0, <=IMG-1),
  (ifm, >=0, <=IFM-1),
  (ofm, >=0, <=OFM-1),
  (oj, >=0, <=#_:OH#-1),
  (oi, >=0, <=#_:OW#-1),
  (kj, >=0, <=#_:KH#-1),
  (ki, >=0, <=#_:KW#-1)
] {{
  input[img][ifm][oj*SH+kj][oi*SW+ki] = input[img][ifm][oj*SH+kj][oi*SW+ki] + output[img][ofm][oj][oi] * filter[ofm][ifm][kj][ki];
}}
""".format(**args)


def gen_program(oh, ow, kh, kw):
    problem = [
        Mapping('OH', [str(oh)]),
        Mapping('OW', [str(ow)]),
        Mapping('KH', [str(kh)]),
        Mapping('KW', [str(kw)]),
    ]
        
    program = Skeleton(skeleton_code)
    program = program.fill_expressions(problem)
    return program

seed(0)
application = 'LoopGen'
batch = 'conv2d-small-inner-20221002'

source_infos = []
for oh in range(5, 9):
    for ow in range(5, 9):
        for kh in range(1, 4):
            for kw in range(1, 4):
                print(f'oh({oh}) ow({ow}) kh({kh}) kw({kw})')
                skeleton = gen_program(oh, ow, kh, kw)
                code = f'conv2d_inner_O{oh}x{ow}_K{kh}x{kw}'
                codelet = f'{code}_de'

                config = CodegenConfig()
                config.possible_values = {
                    # **{ f'{var}[]': 8000000 for var in ['a', 'b', 'c', 'd'] },
                    'IMG': 512,
                    'IFM': 5,
                    'OFM': 5,
                    'SH': 2,
                    'SW': 2,
                }
                config.types = {
                    **{ f'{var}': 'double' for var in ['input', 'output', 'filter'] },
                }
                config.initial_values = {
                    **{ f'{var}' : 'drand(0.0, 1.0)' for var in ['input', 'ouput', 'filter'] },
                    'IMG': '512',
                    'IFM': '5',
                    'OFM': '5',
                    'SH': '2',
                    'SW': '2',
                }
                config.template_dir = 'codelet-template-int-inputs'
                config.output_dir = generate_codelet_files(application,
                                                           batch,
                                                           code,
                                                           codelet,
                                                           10,
                                                           [])
                config.array_as_ptr = True
                skeleton.generate_code(config)

                print(skeleton)

                # Gather source information
                si = SourceInfo()
                si.name = code
                si.n_stmts = 1
                si.scalars.append(18)
                si.arrays.append(3)
                si.ops.append(2)
                si.extra_columns.append(3) # num arrays
                si.extra_columns.append(args['img']) # IMG
                si.extra_columns.append(args['ifm']) # IFM
                si.extra_columns.append(args['ofm']) # OFM
                si.extra_columns.append(args['sh']) # SH
                si.extra_columns.append(args['sw']) # SW
                si.extra_columns.append(oh) # OH
                si.extra_columns.append(ow) # OW
                si.extra_columns.append(kh) # KH
                si.extra_columns.append(kw) # KW
                
                source_infos.append(si)

generate_batch_summary(application, batch, source_infos, ['# arrays', 'IMG', 'IFM', 'OFM', 'SH', 'SW', 'OH', 'OW', 'KH', 'KW'])
