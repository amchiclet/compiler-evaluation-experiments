import pandas as pd

output_path = 'path_to_output.xlsx'
codelet_info = [
    ('path_to_runtime_csv', 'path_to_batch_directory'),
]

merged = None

for runtime_csv_path, batch_path in codelet_info:
    runtime_csv = pd.read_csv(runtime_csv_path)
    runtime_csv.columns = pd.MultiIndex.from_product([['Run Info'], runtime_csv.columns])

    src_info = f'{batch_path}/src_info.csv'
    src_csv = pd.read_csv(src_info)

    # sometimes the src_info.csv file needs some preprocessing
    # below is some example code how to perform various tasks

    # normalize column values to be merged
    src_csv['name'] = 'LoopGen: ' + src_csv['name'] + '_de'

    # add additional summarizing info
    # instead of
    #
    #   arrays
    #   1
    #   3+3 = 6
    #
    # make it
    #
    #   arrays      # total arrays refs
    #   1           1
    #   3+3 = 6     6
    src_csv['# total array refs'] = src_csv['array refs']

    src_csv.loc[
        src_csv['array refs'].str.contains('='), '# total array refs'
    ] = src_csv['array refs'].str.split(' ', expand = True)[2]

    # make header levels match
    # instead of
    #
    #   arrays  scalars
    #   ...     ...
    #
    # make it
    #
    #       Src Info
    #   arrays  scalars
    src_csv.columns = pd.MultiIndex.from_product([['Src Info'], src_csv.columns])

    # join by index
    name_column = None
    for col in runtime_csv.columns:
        if col[1] == 'Name':
            name_column = col
    if name_column is None:
        print('Unable to find "Name" column in the runtime info spreadsheet')
        exit(1)

    runtime_csv.set_index(name_column, inplace=True)
    src_csv.set_index(('Src Info', 'name'), inplace=True)
    joined = src_csv.merge(runtime_csv, left_index=True, right_index=True, how='left')
    joined.reset_index(inplace=True)

    # Also pre-process cores.xlsx
    cores_path = f'{batch_path}/cores.xlsx'
    cores_xlsx = pd.read_excel(cores_path, engine='openpyxl')
    cores_xlsx['name'] = 'LoopGen: ' + cores_xlsx['name'] + '_de'
    cores_xlsx.columns = pd.MultiIndex.from_product([['Code'], cores_xlsx.columns])

    joined.set_index(('Src Info', 'name'), inplace=True)
    cores_xlsx.set_index(('Code', 'name'), inplace=True)
    joined = joined.merge(cores_xlsx, left_index=True, right_index=True, how='left')
    joined.reset_index(inplace=True)
    joined.drop(('Code', 'Unnamed: 0'), axis=1, inplace=True)

    # accumulate (union) results
    if merged is None:
        merged = joined
    else:
        merged = pd.concat([merged, joined])

# clean up the index of concatenated results (they may restart at 0)
merged.reset_index(inplace=True)
merged.drop(('index', ''), axis=1, inplace=True)

merged.to_excel(output_path)
