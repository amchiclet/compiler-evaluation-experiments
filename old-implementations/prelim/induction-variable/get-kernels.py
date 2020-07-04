prefix = 'test'
for p in range(10):
    for v in range(11):
        filename = f'{prefix}.p{p:02}.v{v:02}.c'
        print('==================')
        print(filename)
        print('==================')
        with open(filename) as f:
            kernel = []
            in_kernel = False
            for line in f:
                if not in_kernel:
                    if line.strip() == 'clock_t before = clock();':
                        in_kernel = True
                        continue
                else:
                    if line.strip() == 'clock_t after = clock();':
                        print(''.join(kernel))
                        break
                    else:
                        kernel.append(line)

