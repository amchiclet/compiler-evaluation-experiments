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
unioned.reset_index(inplace=True)
unioned.drop(('index', ''), axis=1, inplace=True)
unioned.to_excel(output)
