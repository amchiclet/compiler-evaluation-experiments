import pandas as pd

src_info_root = 'LoopGen'
runtime_info_root = 'path_to_dir_containing_runtime_info'

m = {
    'dbl_results.xlsx': 'reduction-unique-arrays-dbl-scalars/src_info.csv',
    'int_results.xlsx': 'reduction-unique-arrays-int-scalars/src_info.csv',
}

merged = None

for runtime, src in m.items():
    # read xlxs format
    runtime_info = f'{runtime_info_root}/{runtime}'
    runtime_xlsx = pd.read_excel(runtime_info, header=[0, 1], engine='openpyxl')

    # read csv format
    src_info = f'{src_info_root}/{src}'
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
    runtime_xlsx.set_index(('Run Info', 'Name'))
    src_csv.set_index(('Src Info', 'name'))
    joined = src_csv.join(runtime_xlsx)

    # accumulate (union) results
    if merged is None:
        merged = joined
    else:
        merged = pd.concat([merged, joined])

merged.to_excel('output.xlsx')
