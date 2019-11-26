import argparse
import delegator
import os.path
from config import compilers, executables, Compiler

# TODO create a database

def run(build_root_dir, always_run):
    for compiler in compilers:
        print(f'Compiler: {compiler.name}')
        for executable, n_iterations in executables:
            print(f'Program: {executable}', end='')
            executable_path = os.path.join(build_root_dir, compiler.build_dir, executable)
            runtime_log_path = executable_path + '.runtimes'
            if not always_run and os.path.exists(runtime_log_path):
                print(' (SKIPPED)')
                continue
            else:
                print('')

            command = [ executable_path,
                        '--n_iterations',
                        n_iterations,
                        '--runtime_log_path',
                        runtime_log_path ]
            command_str = ' '.join([str(part) for part in command])
            print(f'Running:\n  {command_str}')
            result = delegator.run(command_str)
            print(result)
            print(result.out)
            if not result.ok:
                print('the result is not ok')
                print(result.err)

if __name__ == '__main__':
    parser = argparse.ArgumentParser()
    parser.add_argument('--full', action='store_true', default=False)
    parser.add_argument('--build_root_dir', required=True)    
    args = parser.parse_args()
    run(args.build_root_dir, args.full)

    
