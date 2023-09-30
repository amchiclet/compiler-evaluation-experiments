import pandas as pd
import openpyxl
import color_scheme
import pathlib
import matplotlib.pyplot as plt

# Example::
#
# interested_columns = [
#     ('group1', 'columna'),
#     ('group2', 'columna'),
#     ('group2', 'columnb'),
# ]

# index_column = ('group3', 'columna')

# df1 = ss.read_excel('excel1.xlsx')
# df2 = ss.read_excel('excel2.xlsx')
# df3 = ss.read_excel('excel3.xlsx')
# merged = ss.merge_left(
#     [df1, df2, df3],
#     ['source1', 'source2', 'source3'],
#     interested_columns,
#     index_column
# )

def read_excel(path):
    return pd.read_excel(path, engine='openpyxl', header=[0, 1])

def read_csv(path, extra_header):
    df = pd.read_csv(path)
    df.columns = pd.MultiIndex.from_product([[extra_header], df.columns])
    return df

def merge_left(dfs, names, on_index, filter_columns=None):
    assert(len(dfs) > 1)

    def create_renaming_dict(df, name):
        return {
            c[0]:(c[0] if c == on_index else f'{c[0]} ({name})')
            for c in df.columns
        }

    def prepare_df(i):
        if filter_columns is None:
            df = dfs[i].copy()
        else:
            df = dfs[i][filter_columns + on_index].copy()
        df.set_index(on_index, inplace=True)
        renaming_dict = create_renaming_dict(df, names[i])
        df.rename(columns=renaming_dict, inplace=True)
        return df

    merged = prepare_df(0)
    for i in range(1, len(dfs)):
        df = prepare_df(i)
        merged = merged.merge(df, left_index=True, right_index=True, how='left')

    return merged

def color(path_in, path_out):
    wb = openpyxl.load_workbook(path_in)
    ws = wb.active

    for col in ws.iter_cols(min_col=2, min_row=2):
        name = col[0].value
        if name not in color_scheme.default:
            continue
        color_scheme.default[name](col[1:])

    wb.save(path_out)

def extract_df(batch):
    names = []
    codes = []

    for path in sorted(pathlib.Path(batch).glob('*/*/core.c')):
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
    return df

def get_src_and_code_df(batch):
    src_df = pd.read_csv(f'{batch}/src_info.csv')
    code_df = extract_df(batch)

    src_df.set_index('name', inplace=True)
    code_df.set_index('name', inplace=True)
    src_and_code = src_df.merge(code_df, left_index=True, right_index=True, how='left')
    src_and_code.reset_index(inplace=True)
    src_and_code.columns = pd.MultiIndex.from_product([['Src Info'], src_and_code.columns])
    return src_and_code

def create_series_key(single_cell_key):
    if single_cell_key is None:
        return None
    return lambda series: [single_cell_key(i) for i in series]

def estimate_width(df):
    return len(df) // 4

# Example:
# spreadsheet.compare(
#     [naive, mkl],
#     ['naive', 'mkl'],
#     ('Run Info', 'DataSet'),
#     ('Timing Metrics', 'Loop (s)'),
#     sorter=lambda x: list(map(int, x.split('-'))),
#     output_path='/home/username/runtime_comparison.png'
# )
def compare(paths, labels, x_column, y_column, sorter=None, output_path=None):
    colors = ['blue', 'red', 'green', 'black']
    assert(len(paths) >= 1)
    assert(len(paths) <= 4)

    key = create_series_key(sorter)

    dfs = [read_excel(p) for p in paths]
    x = dfs[0][x_column]
    x = x.sort_values(key=key)

    plt.figure(figsize=(estimate_width(x), 10))
    for df, label, color in zip(dfs, labels, colors):
        df.sort_values(x_column, inplace=True, key=key)
        y = df[y_column]
        plt.plot(x, y, color=color, linestyle='-', label=label)
    plt.xlabel(str(x_column))
    plt.ylabel(str(y_column))
    plt.yscale('log')
    x_ticks = x if len(x) < 100 else x[::int(len(x)/100)]
    plt.xticks(x_ticks, rotation=90)
    plt.legend()
    if output_path is None:
        plt.show()
    else:
        plt.savefig(output_path)

# Example:
# spreadsheet.compare_speedup(
#     [mkl],
#     naive,
#     ['mkl'],
#     'naive',
#     ('Run Info', 'DataSet'),
#     ('Timing Metrics', 'Loop (s)'),
#     sorter=lambda x: list(map(int, x.split('-'))),
#     output_path='/home/username/speedup.png'
# )
def compare_speedup(paths, path_of_base, labels, base_label, x_column, y_column, sorter=None, output_path=None):
    colors = ['blue', 'red', 'green', 'black']
    assert(len(paths) >= 1)
    assert(len(paths) <= 4)
    dfs = [read_excel(p) for p in paths]
    base_df = read_excel(path_of_base)

    key = create_series_key(sorter)

    base_df.sort_values(x_column, inplace=True, key=key)
    x = dfs[0][x_column]
    x = x.sort_values(key=key)

    plt.figure(figsize=(estimate_width(x), 10))
    for df, label, color in zip(dfs, labels, colors):
        df.sort_values(x_column, inplace=True, key=key)
        y_speedup = base_df[y_column] / df[y_column]
        plt.plot(x, y_speedup, color=color, linestyle='-', label=label)
    plt.xlabel(str(x_column))
    plt.ylabel(f'{y_column} speedup over {base_label}')
    # plt.yscale('log')
    x_ticks = x if len(x) < 100 else x[::int(len(x)/100)]
    plt.xticks(x_ticks, rotation=90)
    plt.legend()
    if output_path is None:
        plt.show()
    else:
        plt.savefig(output_path)
