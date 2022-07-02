import pandas as pd

output_path = 'path_to_output.xlsx'
codelet_info = [
    ('path_to_xlsx', 'path_to_batch_directory'),
]

merged = None

for runtime_xlsx_path, batch_path in codelet_info:
    # read xlxs format
    runtime_xlsx = pd.read_excel(runtime_xlsx_path, header=[0, 1], engine='openpyxl')

    # read csv format
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
    #   arrays      # arrays
    #   1           1
    #   3+3 = 6     6
    src_csv['# arrays'] = src_csv['arrays']
    src_csv.loc[
        src_csv['arrays'].str.contains('='), '# arrays'
    ] = src_csv['arrays'].str.split(' ', expand = True)[2]

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
    for col in runtime_xlsx.columns:
        if col[1] == 'Name':
            name_column = col
    if name_column is None:
        print('Unable to find "Name" column in the runtime info spreadsheet')
        exit(1)

    runtime_xlsx.set_index(name_column, inplace=True)
    src_csv.set_index(('Src Info', 'name'), inplace=True)
    joined = src_csv.merge(runtime_xlsx, left_index=True, right_index=True, how='left')
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
