import argparse
import pathlib
import skeletons.recurrence as recurrence
import skeletons.generate as generate
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

parser = argparse.ArgumentParser()
parser.add_argument('--output_dir', type=pathlib.Path, default=pathlib.Path('./out'))
parser.add_argument('--temp_dir', type=pathlib.Path, default=pathlib.Path('./tmp'))
parser.add_argument('--run_script_path', type=pathlib.Path, default=pathlib.Path('./run.sh'))
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

experiment_name = args.experiment_name
if args.experiment_name is None:
    t = datetime.datetime.now()
    experiment_name = f'experiment-{t.year}{t.month:02d}{t.day:02d}-{t.hour:02d}{t.minute:02d}'

def generate_batch(batch, n_codelets, max_try_factor=3):
    max_tries = n_codelets * max_try_factor
    sis = []
    for _ in range(max_tries):
        index = len(sis) + 1
        result = generate_codelet(batch, index)
        if result is not None:
            code, codelet, si = result
            print(f'Generated {batch}/{code}/codelet')
            sis.append(si)
            if len(sis) == n_codelets:
                break

    shutil.copytree(args.temp_dir/batch, args.output_dir/batch)
    codelet_generator.generate_batch_summary_flex(
        args.output_dir, batch, sis, generate.source_info_header
    )

def generate_codelet(batch, index):
    t = datetime.datetime.now()
    code = f'program_{index:02d}'
    codelet = f'{code}_de'
    codelet_dir = codelet_generator.codelet_dir(args.temp_dir, batch, code, codelet)
    codelet_path = pathlib.Path(codelet_dir)
    codelet_path.mkdir(parents=True, exist_ok=True)
    randomstate_path = codelet_path / 'random.state'
    randomstate.checkpoint(randomstate_path)

    # skeleton, source_info, config, default_inputs = recurrence.generate()
    n_stmts = random.randint(3, 5)
    n_ops = random.randint(n_stmts, n_stmts*5)
    n_lc_deps = random.randint(0, n_stmts)
    n_li_deps = random.randint(0, n_stmts)
    n_ro = random.randint(1, 5)
    n_arrs = random.randint(n_stmts+1, n_stmts+n_ro)
    gen_result = generate.gen_program(n_stmts, n_arrs, n_ops, n_lc_deps, n_li_deps, n_ro)
    if gen_result is None:
        return None

    skeleton, si, config, default_inputs = gen_result
    si['name'] = code
    if skeleton is None:
        return None

    config.template_dir = 'codelet-template-int-inputs'
    config.output_dir = codelet_generator.generate_codelet_files(
        args.temp_dir, batch, code, codelet, 10, default_inputs
    )

    skeleton.generate_code(config)
    new_checksum = checksum.get_checksum(codelet_path / 'core.c')
    if new_checksum in checksums:
        print('codelet already generated')
        return None

    return code, codelet, si

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

full_df = pd.DataFrame()
result_df = pd.DataFrame()

count = 0
for attempt in range(1, args.max_attempts+1):
    # generate batch
    batch_prefix = experiment_name
    if args.batch_prefix is not None:
        batch_prefix = args.batch_prefix
    batch = f'{batch_prefix}-batch{attempt:02d}'
    generate_batch(batch, args.batch_size)

    # run batch

    # save all data in full_df
    # save data that meets constraints in result_df

    # run 'build_vrun_script batch' to generate vrun_new.sh
    current_dir = pathlib.Path('.')
    log_path = current_dir / f'{batch}.log'
    vrun_dir = current_dir / '..' / 'cape-experiment-scripts' / 'vrun'
    vrun_input = f'{current_dir.resolve().name}/{args.output_dir}/{batch}'
    print(vrun_input)
    command = delegator.run(f'./build_vrun_script {vrun_input}', cwd=vrun_dir)
    print(command.out)
    print(command.err)

    # run the newly generated vrun_new.sh
    vrun_new_sh = vrun_dir / 'vrun_new.sh'
    st = os.stat(vrun_new_sh)
    os.chmod(vrun_new_sh, st.st_mode | stat.S_IEXEC | stat.S_IXGRP | stat.S_IXOTH)

    print(f'Running cape script. To view ')
    print(f'less +F {log_path.resolve()}')
    command = delegator.run(f'./vrun_new.sh test | tee {log_path.resolve()}', cwd=vrun_dir)

    # find the generated SI data csv file
    line_start = command.out.index("Cape SI data")
    si_filename_start = command.out.index(":", line_start) + 2
    si_filename_end = command.out.index(".csv", line_start) + 4
    si_path = command.out[si_filename_start:si_filename_end].strip()
    si_csv = pathlib.Path(si_path)

    si_df = pd.read_csv(si_path)
    full_df = full_df.append(si_df)

    # yield_df = si_df.loc[si_df['Tier'].isin(args.tiers)]
    # print(f'--------tier = {args.tiers}-----------')
    # print(yield_df)

    # yield_df = si_df.loc[si_df['Sat_Node'].isin(control_unit_nodes)]
    # print('control unit')
    # print(yield_df)

    yield_df = si_df.loc[si_df['Tier'].isin(args.tiers) & si_df['Sat_Node'].isin(control_unit_nodes)]
    result_df = result_df.append(yield_df)
    # print('both')
    # print(yield_df)
    if not yield_df.empty:
        print(f'Found codelets saturating the control unit at tier {args.tiers}')
        print(yield_df[['Name', 'Tier', 'Sat_Node']])
        count += len(yield_df)
        if count >= args.how_many:
            break
        continue

    print(f'Finished attempt {attempt}/{args.max_attempts}')
    print(f'Did not find any codelets saturating the control units at tier {args.tiers}')
    print(full_df[['Name', 'Tier', 'Sat_Node']])

print('*********** All codelets generated **********')
print(full_df[['Name', 'Tier', 'Sat_Node']])

print(f'************ Codelets saturating the control unit at tiers {args.tiers} ***********')
print(result_df[['Name', 'Tier', 'Sat_Node']])

full_df.to_csv(f'{args.output_dir}/{experiment_name}_codelet_all.csv', index = True, header = True)
result_df.to_csv(f'{args.output_dir}/{experiment_name}_codelet_yield.csv', index = True, header = True)
