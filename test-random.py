import delegator
from pathlib import Path
import sys
from random import choice

assert(len(sys.argv) == 2)

def make_and_run(codelet):
    c = delegator.run('make', cwd=codelet)
    if c.return_code != 0:
        print(f'Failed to make: {c.err}')
        return
    print(c.out)
    c = delegator.run('./wrapper', cwd=codelet)
    if c.return_code != 0:
        print(f'Failed to run: {c.err}')
        return
    print(c.out)

codelets = [path.parent for path in Path(sys.argv[1]).rglob('core.c')]
codelet = choice(codelets)
print(codelet)
with open(f'{codelet}/core.c') as f:
    print(f.read())
make_and_run(codelet)
c = delegator.run('make clean', cwd=codelet)
print(c.out)
print(c.err)
