import pandas as pd
import openpyxl
import color_scheme

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
    df.columns = df.MultiIndex.from_product([[extra_header], df.columns])
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
            df = dfs[i][filter_columns + [on_index]].copy()
        df.set_index(on_index, inplace=True)
        renaming_dict = create_renaming_dict(df, names[i])
        df.rename(columns=renaming_dict, inplace=True)
        return df

    merged = prepare_df(0)
    for i in range(1, len(dfs)):
        df = prepare_df(i)
        merged = merged.merge(df, left_index=True, right_index=True, how='left')

    merged.reset_index(inplace=True)
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
