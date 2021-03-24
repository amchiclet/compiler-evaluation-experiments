import os

dirs1 = [d for d in os.listdir('two-statements-850') if d.endswith('.c')]
for d1 in dirs1:
    d2s = os.listdir(d1)
    assert(len(d2s) == 1)
    d2 = d2s[0]
    print(d2)
    meta = f'{d1}/{d2}/codelet.meta'
    meta_new = f'{meta}.new'
    with open(meta) as fin, open(meta_new, 'w') as fout:
        old_content = fin.read()
        new_content = old_content.replace('two_statement', 'two-statement-850')
        print(old_content, new_content)

    
