import pandas as pd

xlsx1 = 'path_to_xlsx1.xlsx'
xlsx2 = 'path_to_xlsx2.xlsx'
output = 'path_to_output.xlsx'

def load_excel(path):
    xlsx = pd.read_excel(path, engine='openpyxl', header=[0, 1], skiprows=0)
    xlsx.drop(('Unnamed: 0_level_0', 'Unnamed: 0_level_1'), axis=1, inplace=True)
    return xlsx

f1 = load_excel(xlsx1)
f2 = load_excel(xlsx2)

unioned = pd.concat([f1, f2])

f1_src_info_order = [col for (head, col) in f1.columns if head == 'Src Info']
f2_src_info_order = [col for (head, col) in f2.columns if head == 'Src Info']
f1_run_info_order = [col for (head, col) in f1.columns if head == 'Run Info']
f2_run_info_order = [col for (head, col) in f2.columns if head == 'Run Info']
# sort by src_info, code, then run info.
def sorting(k):
    head, col = k
    if head == 'Src Info':
        if col in f1_src_info_order:
            return f1_src_info_order.index(col)
        return (len(f1_src_info_order) +
                f2_src_info_order.index(col))

    if head == 'Code':
        return (len(f1_src_info_order) +
                len(f2_src_info_order))

    if k[0] == 'Run Info':
        if col in f1_run_info_order:
            return (len(f1_src_info_order) +
                    len(f2_src_info_order) +
                    1 +
                    f1_run_info_order.index(col))
        return (len(f1_src_info_order) +
                len(f2_src_info_order) +
                1 +
                len(f1_run_info_order) +
                f2_run_info_order.index(col))

    return (len(f1_src_info_order) +
            len(f2_src_info_order) +
            1 +
            len(f1_run_info_order) +
            len(f2_run_info_order))

column_order = unioned.columns.tolist()
column_order.sort(key=sorting)
unioned = unioned[column_order]

unioned.reset_index(inplace=True)
unioned.drop(('index', ''), axis=1, inplace=True)
unioned.to_excel(output)
