import delegator
import argparse
import statistics
import math
from build import PathBuilder

def measure_runtime_and_parse_results(command, n_iterations):
    full_command = f'{command} --measure {n_iterations}'
    c = delegator.run(full_command)
    if c.return_code != 0:
        raise RuntimeError(f'Return code ({c.return_code}) '
                           f'when running the following command: {full_command}')

    lines = c.out.split('\n')
    ints = []
    for line in lines[1:]:  # first line is header. skip it.
        if line:
            ints.append(int(line.split()[-1])) # last token is the ns time
    return ints

# run up to at most 1 second or 10 iterations and get the average
def calculate_avg_nsecs(command, n_iterations):
    runtimes = measure_runtime_and_parse_results(command, n_iterations)
    return statistics.mean(runtimes)

def n_iterations_per_ms(goal_ms, per_iteration_nsec):
    return math.ceil(goal_ms * 1e6 / per_iteration_nsec)

def calculate_ns_per_iteration(exe_name, output_path):
    max_iterations = 100
    nsec_per_iteration = calculate_avg_nsecs(f'./{exe_name}', 1)
    n_iterations = n_iterations_per_ms(1000, nsec_per_iteration)
    if n_iterations == 1:
        avg_nsec_per_iteration = nsec_per_iteration
    elif n_iterations < max_iterations:
        avg_nsec_per_iteration = calculate_avg_nsecs(f'./{exe_name}', n_iterations)
    else:
        avg_nsec_per_iteration = calculate_avg_nsecs(f'./{exe_name}', max_iterations)
    with open(output_path, 'w') as f:
        f.write(f'{avg_nsec_per_iteration}')

def measure_runtime(exe_name, ns_per_iteration_path, output_path):
    with open(ns_per_iteration_path) as f:
        ns_per_iteration = float(f.read())

    # run for 100 ms (or at most 100 iterations) and take the average
    n_iterations = n_iterations_per_ms(100, ns_per_iteration)
    if n_iterations > 100:
        n_iterations = 100
    runtimes = measure_runtime_and_parse_results(f'./{exe_name}', n_iterations)
    with open(output_path, 'w') as f:
        f.write(' '.join(map(str, runtimes)))

def checksum_and_parse_results(command):
    return checksum

def calculate_checksum(exe_name, output_path):
    full_command = f'./{exe_name} --checksum'
    c = delegator.run(full_command)
    if c.return_code != 0:
        raise RuntimeError(f'Return code ({c.return_code}) '
                           f'when running the following command: {full_command}')

    lines = c.out.split('\n')
    checksum = lines[1].split()[-1]

    with open(output_path, 'w') as f:
        f.write(checksum)
