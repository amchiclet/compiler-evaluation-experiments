import delegator
import argparse
import statistics
import math

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

parser = argparse.ArgumentParser()
parser.add_argument('--command', required=True, type=str)
parser.add_argument('--goal_ms', required=True, type=int)
args = parser.parse_args()
per_iteration_nsec = nsecs(args.command, 1)
print(n_iterations(args.goal_ms, per_iteration_nsec))
