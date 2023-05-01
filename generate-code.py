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

parser = argparse.ArgumentParser()
parser.add_argument('--output_dir', type=pathlib.Path, default=pathlib.Path('./out'))
parser.add_argument('--temp_dir', type=pathlib.Path, default=pathlib.Path('./tmp'))
parser.add_argument('--run_script_path', type=pathlib.Path, default=pathlib.Path('./run.sh'))
parser.add_argument('--how_many', type=int, default=1)
parser.add_argument('--random_state', type=pathlib.Path, default=None)
parser.add_argument('--node', type=str, default=None)
parser.add_argument('--tier', type=int, default=None)
args = parser.parse_args()

if args.random_state is not None:
    randomstate.restore(args.random_state)

print(args.output_dir, args.temp_dir)

checksums = checksum.gather_checksums(args.output_dir, '*/*/*/core.c')

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
    skeleton, si, config, default_inputs = generate.gen_program(n_stmts, n_arrs, n_ops, n_lc_deps, n_li_deps, n_ro)
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
    # if not args.run_script_path.exists():
    #     print('Run script does not exist. Exiting without running.')

    # run_command = delegator.run(f'{args.run_script_path.resolve()} {batch} | tee {batch}.log')
    # if not run_command.ok:
    #     print(run_command.err)
    #     exit(1)

    # print(run_command.out)

t = datetime.datetime.now()
batch = f'batch-{t.year}{t.month:02d}{t.day:02d}-{t.hour:02d}{t.minute:02d}'
generate_batch(batch, 2)
