import pandas as pd
import sys
from pathlib import Path

def extract(batch):
    names = []
    codes = []

    for path in sorted(Path(batch).glob('*/*/core.c')):
        codelet = path.parts[-3]
        names.append(codelet)
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
        codes.append(''.join(no_empty))

    df = pd.DataFrame()
    df['name'] = names
    df['code'] = codes
    df.to_excel(f'{batch}/cores.xlsx')

if __name__ == '__main__':
    assert(len(sys.argv) == 2)
    extract(sys.argv[1])
