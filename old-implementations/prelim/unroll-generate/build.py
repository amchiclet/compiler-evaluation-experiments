import delegator
import os
import sys
import argparse

from config import compilers, executables

def build(build_root_dir, command, compiler, extra=None):
    result = command(build_root_dir, compiler, extra)
    if not result.ok:
        print('FAILED build\nSTDOUT:\n\n', result.out, '\n\nSTDERR:\n\n', result.err)
        return False

    if args.verbose:
        print('PASSED build\nSTDOUT:\n\n', result.out)
    return True

def meson(build_root_dir, compiler, extra):
    full_build_dir = os.path.join(build_root_dir, compiler.build_dir)
    command = 'CC={} meson {} {}'.format(compiler.cpp, compiler.extra_args, full_build_dir)
    print(command)
    return delegator.run(command)

def ninja(build_root_dir, compiler, extra):
    full_build_dir = os.path.join(build_root_dir, compiler.build_dir)
    return delegator.run('ninja -v', cwd = full_build_dir)

def assembler(build_root_dir, compiler, extra):
    full_build_dir = os.path.join(build_root_dir, compiler.build_dir)
    return delegator.run('ninja -v ' + extra, cwd = full_build_dir)

def main(args):
    print(os.getcwd())
    os.makedirs(args.build_root_dir, exist_ok = True)
    for compiler in compilers:
        # Run meson
        if args.full:
            if args.reconfigure:
                compiler.extra_args += ' --reconfigure '
                print('Building meson for {}'.format(compiler.name))
            if not build(args.build_root_dir, meson, compiler):
                return False

        # Run ninja
        print('Building ninja for {}'.format(compiler.name))
        if not build(args.build_root_dir, ninja, compiler):
            return False

        print('Building assembly for {}'.format(compiler.name))
        for executable, _ in executables:
            target = executable + '.s'
            if not build(args.build_root_dir, assembler, compiler, target):
                return False
    return True

if __name__ == '__main__':
    parser = argparse.ArgumentParser()
    parser.add_argument('--reconfigure', action='store_true', default=False)
    parser.add_argument('--full', action='store_true', default=False)
    parser.add_argument('--verbose', action='store_true', default=False)
    parser.add_argument('--build_root_dir', required=True)
    args = parser.parse_args()
    main(args)
