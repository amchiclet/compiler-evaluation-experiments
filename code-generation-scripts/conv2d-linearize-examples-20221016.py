from api import Skeleton, Mapping, CodegenConfig
from random import randint, seed
from codelet_generator import codelet_dir, generate_codelet_files, generate_batch_summary, SourceInfo
from pattern_ast import get_ordered_assignments, get_accesses, count_ops
from itertools import product

# vary vector size 8 and 16
# version 1: linearized array
# version 2: multi-dimensional array

args = {
    'ifh': 7,
    'ifw': 7,

    'img': 8,
    
    'ifm': 48,
    'ofm': 128,
    'kw': 5,
    'kh': 5,
    'ofh': 7,
    'ofw': 7,

    'sh': 1,
    'sw': 1,

    'ph': 2,
    'pw': 2,

    'ifhp': 11,
    'ifwp': 11,
}

skeleton_code = """
declare IMG;
declare IFM;
declare OFM;
declare IFHP;
declare IFWP;
declare OFH;
declare OFW;
declare IFH;
declare IFW;
declare KH;
declare KW;
declare SH;
declare SW;
declare PH;
declare PW;

local ij;
local kj_begin;
local kj_end;
local ii;
local ki_begin;
local ki_end;
local input_img_stride;
local input_ifm_stride;
local output_img_stride;
local output_ofm_stride;
local weight_ofm_stride;
local weight_ifm_stride;

declare input[IMG*IFM/{vec_length}*IFHP*IFWP*{vec_length}];
declare output[IMG*OFM/{vec_length}*OFH*OFW*{vec_length}];
declare filter[OFM/{vec_length}*IFM/{vec_length}*KH*KW*{vec_length}*{vec_length}];

input_img_stride = IFM*IFHP*IFWP;
input_ifm_stride = IFHP*IFWP*{vec_length};
output_img_stride = OFM*OFH*OFW;
output_ofm_stride = OFH*OFW*{vec_length};
weight_ofm_stride = IFM*KH*KW*{vec_length};
weight_ifm_stride = KH*KW*{vec_length}*{vec_length};

for [ (img, >=0, <=IMG - 1),
      (ifm_tile, >=0, <=IFM/{vec_length} - 1),
      (ofm_tile, >=0, <=OFM/{vec_length} - 1),
      (ofm, >=0, <={vec_length} - 1),
      (oj, >=0, <=OFH - 1) ] {{
  ij = oj*SH - PH;
  kj_begin = (ij < 0) ? (0-ij) : 0;
  kj_end = (ij+KH-1) >= IFH ? (ij+KH-IFH+1) : KH;
  for [ (oi, >=0, <=OFH - 1) ] {{
    ii = oi*SW - PW;
    ki_begin = (ii < 0) ? (0-ii) : 0;
    ki_end = (ii+KW-1) > IFW ? (ii+KW-IFW+1) : KW;
    for [ (kj, >=kj_begin, <=kj_end-1),
          (ki, >=ki_begin, <=ki_end-1),
          (ifm, >=0, <={vec_length} - 1) ] {{
      input   [img*input_img_stride       + ifm_tile*input_ifm_stride  + (ij+kj+PH)*IFWP*{vec_length}    + (ii+ki+PW)*{vec_length}      + ifm] =
        input [img*input_img_stride       + ifm_tile*input_ifm_stride  + (ij+kj+PH)*IFWP*{vec_length}    + (ii+ki+PW)*{vec_length}      + ifm] +
        output[img*output_img_stride      + ofm_tile*output_ofm_stride + oj*OFW*{vec_length}             + oi*{vec_length}              + ofm] *
        filter[ofm_tile*weight_ofm_stride + ifm_tile*weight_ifm_stride + kj*KW*{vec_length}*{vec_length} + ki*{vec_length}*{vec_length} + ofm*{vec_length} + ifm];
    }}
  }}
}}
"""

def gen_program(vec_length):
    s = skeleton_code.format(**{'vec_length': vec_length})
    program = Skeleton(s)
    return program

seed(0)
application = 'LoopGen'
batch = 'conv2d-linearized-examples-20221016'

source_infos = []
for vec_length in [2, 4, 8, 16]:
    skeleton = gen_program(vec_length)
    code = f'conv2d_linearized_vec{vec_length:02d}'
    codelet = f'{code}_de'

    config = CodegenConfig()
    config.possible_values = {
        'IMG': 8,
        'IFM': 48,
        'OFM': 128,
        'SH': 1,
        'SW': 1,
        'PH': 2,
        'PW': 2,
        'KH': 5,
        'KW': 5,
        'IFHP': 11,
        'IFWP': 11,
        'IFH': 7,
        'IFW': 7,
        'OFH': 7,
        'OFW': 7,
        'ii': (-2, 9),
        'ki': 0,
        'ki_begin': 0,
        'ki_end': 0,
        'ij': (-2, 9),
        'kj': 0,
        'kj_begin': 0,
        'kj_end': 0,
    }
    config.types = {
        **{ f'{var}': 'double' for var in ['input', 'output', 'filter'] },
    }
    config.initial_values = {
        **{ f'{var}' : 'drand(0.0, 1.0)' for var in ['input', 'ouput', 'filter'] },
        'IMG': 8,
        'IFM': 48,
        'OFM': 128,
        'SH': 1,
        'SW': 1,
        'PH': 2,
        'PW': 2,
        'KH': 5,
        'KW': 5,
        'IFHP': 11,
        'IFWP': 11,
        'IFH': 7,
        'IFW': 7,
        'OFH': 7,
        'OFW': 7,
    }
    config.template_dir = 'codelet-template-int-inputs'
    config.output_dir = generate_codelet_files(application,
                                               batch,
                                               code,
                                               codelet,
                                               10,
                                               [])
    config.array_as_ptr = True
    config.force = True
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
    si.extra_columns.append(args['ph']) # PH
    si.extra_columns.append(args['pw']) # PW
    si.extra_columns.append(args['ofh']) # OFH
    si.extra_columns.append(args['ofw']) # OFW
    si.extra_columns.append(args['ifhp']) # IFHP
    si.extra_columns.append(args['ifwp']) # IFWP
    si.extra_columns.append(args['ifh']) # IFH
    si.extra_columns.append(args['ifw']) # IFW
    si.extra_columns.append(args['kh']) # KH
    si.extra_columns.append(args['kw']) # KW
    si.extra_columns.append(vec_length)
    source_infos.append(si)

generate_batch_summary(
    application, batch, source_infos,
    ['# arrays',
     'IMG', 'IFM', 'OFM',
     'SH', 'SW', 'PH', 'PW',
     'OFH', 'OFW', 'IFHP', 'IFWP', 'IFH', 'IFW',
     'KH', 'KW',
     'VEC_LENGTH',
])
