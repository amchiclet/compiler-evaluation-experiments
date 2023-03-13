import argparse
import pathlib
import skeletons.recurrence as recurrence
import codelet_generator
import randomstate
import checksum
import shutil
import delegator

parser = argparse.ArgumentParser()
parser.add_argument('--output_dir', type=pathlib.Path, default=pathlib.Path('./out'))
parser.add_argument('--temp_dir', type=pathlib.Path, default=pathlib.Path('./tmp'))
parser.add_argument('--run_script_path', type=pathlib.Path, default=pathlib.Path('./run.sh'))
parser.add_argument('--how_many', type=int, default=1)
parser.add_argument('--random_state', type=pathlib.Path, default=None)
args = parser.parse_args()

if args.random_state is not None:
    randomstate.restore(args.random_state)

print(args.output_dir, args.temp_dir)

checksums = checksum.gather_checksums(args.output_dir, '*/*/*/core.c')

batch_number = 1
while batch_number < 3:
    batch = f'2023-03-13-batch{batch_number:02d}'
    code = f'recurrence_001'
    codelet = f'{code}_de'
    codelet_dir = codelet_generator.codelet_dir(args.temp_dir, batch, code, codelet)
    codelet_path = pathlib.Path(codelet_dir)
    codelet_path.mkdir(parents=True, exist_ok=True)
    randomstate_path = codelet_path / 'random.state'
    randomstate.checkpoint(randomstate_path)

    skeleton, source_info, config, default_inputs = recurrence.generate()
    source_info['name'] = code
    config.template_dir = 'codelet-template-int-inputs'
    config.output_dir = codelet_generator.generate_codelet_files(
        args.temp_dir, batch, code, codelet, 10, default_inputs
    )

    skeleton.generate_code(config)
    codelet_generator.generate_batch_summary_flex(
        args.temp_dir, batch, [source_info], recurrence.source_info_header
    )
    new_checksum = checksum.get_checksum(codelet_path / 'core.c')
    if new_checksum in checksums:
        print('codelet already generated')
        shutil.rmtree(args.temp_dir/batch)
        continue
    else:
        shutil.copytree(args.temp_dir/batch, args.output_dir/batch)
        batch_number += 1

    if not args.run_script_path.exists():
        print('Run script does not exist. Exiting without running.')

    run_command = delegator.run(f'{args.run_script_path.resolve()} {batch} | tee {batch}.log')
    if not run_command.ok:
        print(run_command.err)
        exit(1)

    print(run_command.out)
