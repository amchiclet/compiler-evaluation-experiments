import pandas as pd
import code_to_xls
import sys

assert(len(sys.argv) == 2)
batch_path = sys.argv[1]

output = 'path_to_output.xlsx'

src_info = f'{batch_path}/src_info.csv'
src_csv = pd.read_csv(src_info)

src_csv.set_index('name', inplace=True)

code_to_xls.extract(batch_path)
cores_path = f'{batch_path}/cores.xlsx'
cores_xlsx = pd.read_excel(cores_path, engine='openpyxl')

cores_xlsx.set_index('name', inplace=True)
joined = src_csv.merge(cores_xlsx, left_index=True, right_index=True, how='left')
joined.reset_index(inplace=True)
joined.to_excel('output.xlsx')

