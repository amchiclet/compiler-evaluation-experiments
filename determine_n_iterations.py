import delegator
import argparse
import statistics
import math
from build import PathBuilder

def nsecs(command, n_iterations):
    c = delegator.run(f'{command} --measure {n_iterations}')
    if c.return_code != 0:
        raise RuntimeError(f'Return code ({c.return_code}) when running the following command: {command}')

    # The last token is expected to be the time in nano-seconds
    lines = c.out.split('\n')
    total = []
    for line in lines[1:1+n_iterations]:
        if line:
            total.append(int(line.split()[-1]))
    return statistics.mean(total)

def n_iterations(goal_ms, per_iteration_nsec):
    return math.ceil(goal_ms * 1e6 / per_iteration_nsec)

def determine_n_iterations(exe_name, n_iterations_name, goal_ms, min_iters=3, max_iters=100):
    with open(n_iterations_name, 'w') as f:
        per_iteration_nsec = nsecs(f'./{exe_name}', 1)
        iters = n_iterations(goal_ms, per_iteration_nsec)
        if iters > max_iters:
            iters = max_iters
        if iters < min_iters:
            iters = min_iters
        f.write(f'{iters}')
