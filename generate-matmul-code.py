import argparse
import pathlib
import skeletons.matmul as generate
import codelet_generator
import randomstate
import checksum
import shutil
import delegator
import datetime
import random
import pandas as pd
import os
import stat
import loguru

parser = argparse.ArgumentParser()
parser.add_argument('--output_dir', type=pathlib.Path, default=pathlib.Path('./out'))
parser.add_argument('--temp_dir', type=pathlib.Path, default=pathlib.Path('./tmp'))
parser.add_argument('--tiers', type=int, nargs='+', default=[1, 2])
parser.add_argument('--unit', type=str, default='control')
parser.add_argument('--batch_size', type=int, default=2)
parser.add_argument('--max_attempts', type=int, default=3)
parser.add_argument('--batch_prefix', type=str, default=None)
parser.add_argument('--random_state', type=pathlib.Path, default=None)
parser.add_argument('--experiment_name', type=str, default=None)
parser.add_argument('--how_many', type=int, default=1)
args = parser.parse_args()

if args.random_state is not None:
    randomstate.restore(args.random_state)

checksums = checksum.gather_checksums(args.output_dir, '*/*/*/core.c')

logger = loguru.logger

experiment_name = args.experiment_name
if args.experiment_name is None:
    t = datetime.datetime.now()
    experiment_name = f'experiment-{t.year}{t.month:02d}{t.day:02d}-{t.hour:02d}{t.minute:02d}'

def generate_batch(batch, n_codelets, max_try_factor=3, params_prototype=None):
    max_tries = n_codelets * max_try_factor
    sis = []
    params = {}
    for _ in range(max_tries):
        index = len(sis) + 1
        result = generate_codelet(batch, index, params_prototype)
        if result is not None:
            code, codelet, si, codegen_params = result
            params[code] = codegen_params
            logger.debug(f'Generated {batch}/{code}/{codelet}')
            sis.append(si)
            if len(sis) == n_codelets:
                break

    shutil.copytree(args.temp_dir/batch, args.output_dir/batch)
    codelet_generator.generate_batch_summary_flex(
        args.output_dir, batch, sis, generate.source_info_header
    )
    return sis, params

def generate_codelet(batch, index, params_prototype=None):
    t = datetime.datetime.now()
    code = f'program_{index:02d}'
    codelet = f'{code}_de'
    codelet_dir = codelet_generator.codelet_dir(args.temp_dir, batch, code, codelet)
    codelet_path = pathlib.Path(codelet_dir)
    codelet_path.mkdir(parents=True, exist_ok=True)
    randomstate_path = codelet_path / 'random.state'
    randomstate.checkpoint(randomstate_path)

    codegen_params = generate.randomly_create_code_generation_parameters()

    gen_result = generate.gen_program(codegen_params)
    if gen_result is None:
        return None

    skeleton, si, config, default_inputs = gen_result
    if skeleton is None:
        return None

    si['batch'] = batch
    si['name'] = code
    si['codelet name'] = codelet
    si['generate function'] = 'skeletons.matmul.gen_program'

    config.template_dir = 'codelet-template-int-inputs'
    config.output_dir = codelet_generator.generate_codelet_files(
        args.temp_dir, batch, code, codelet, 10, default_inputs
    )

    skeleton.generate_code(config)
    new_checksum = checksum.get_checksum(codelet_path / 'core.c')
    if new_checksum in checksums:
        logger.debug('codelet already generated')
        return None

    return code, codelet, si, codegen_params

def extract_loop(batch_path):
    loops = {}

    for path in sorted(pathlib.Path(batch_path).glob('*/*/core.c')):
        name = path.parts[-3]

        # names.append(f'LoopGen: {codelet}_de')
        lines = []
        with open(path) as f:
            function_start = False
            for line in f:
                if 'core(' in line:
                    function_start = True
                    continue
                if 'return 0' in line:
                    break
                if not function_start:
                    continue
                lines.append(line)
        no_empty = []
        for line in lines:
            if len(line.strip()) > 0:
                no_empty.append(line)
        # codes.append(''.join(no_empty))

        code = ''.join(no_empty)
        loops[name] = code

    return loops

# Overview
# 1) generate batch
# 2) run cape scripts
# 3) parse csv file to see whether the generated codelets have what we want

control_unit_nodes = [
    'Stall[RS]_%',
    'Stall[SB]_%',
    'Stall[LB]_%',
    'Stall[LM]_%',
    'Stall[RS]_%',
    'Stall[ROB]_%',
]

# save all data in full_df
full_df = pd.DataFrame()

# generate batch
batch_prefix = experiment_name
if args.batch_prefix is not None:
    batch_prefix = args.batch_prefix
batch = f'{batch_prefix}-batch'
source_infos, codegen_params = generate_batch(batch,
                                              args.batch_size,
                                              max_try_factor=3)

# run 'build_vrun_script batch' to generate vrun_new.sh
current_dir = pathlib.Path('.')
log_path = current_dir / f'{batch}.log'
vrun_dir = current_dir / '..' / 'cape-experiment-scripts' / 'vrun'
vrun_input = f'{current_dir.resolve().name}/{args.output_dir}/{batch}'
logger.debug(vrun_input)
vrun_sh = 'vrun_matmul_new.sh'
command = delegator.run(f'./build_vrun_matmul {vrun_input} matmul_sizes.txt {vrun_sh}', cwd=vrun_dir)
logger.debug(command.out)
logger.debug(command.err)

# run the newly generated vrun script
vrun_new_sh = vrun_dir / vrun_sh
st = os.stat(vrun_new_sh)
os.chmod(vrun_new_sh, st.st_mode | stat.S_IEXEC | stat.S_IXGRP | stat.S_IXOTH)

logger.info(f'Running cape script. To view ')
logger.info(f'less +F {log_path.resolve()}')
command = delegator.run(f'./{vrun_sh} test | tee {log_path.resolve()}', cwd=vrun_dir)

# find the generated SI data csv file
line_start = command.out.index("Cape SI data")
si_filename_start = command.out.index(":", line_start) + 2
si_filename_end = command.out.index(".csv", line_start) + 4
si_path = command.out[si_filename_start:si_filename_end].strip()
si_csv = pathlib.Path(si_path)

si_df = pd.read_csv(si_path)

# add source info to the dataframe

loops = extract_loop(args.output_dir / batch)

source_info_dict = {}
source_info_dict['si name'] = []
source_info_dict['code'] = []

for source_info in source_infos:
    for k, v in source_info.m.items():
        if k not in source_info_dict:
            source_info_dict[k] = []
        source_info_dict[k].append(v)
    source_info_dict['si name'].append(f'LoopGen: {source_info["name"]}_de')
    source_info_dict['code'].append(loops[source_info['name']])

source_info_df = pd.DataFrame.from_dict(source_info_dict)
logger.debug(source_info_df)
si_df = pd.merge(si_df, source_info_df, how="outer", left_on="Name", right_on="si name")

full_df = full_df.append(si_df)

columns = ['Name', 'Tier', 'Sat_Node', '# statements', 'code']
full_df = full_df.reindex()

logger.info('*********** All codelets generated **********')
logger.info(f'\n{full_df[columns]}')

full_df.to_csv(f'{args.output_dir}/{experiment_name}_codelet_all.csv', index = True, header = True)
