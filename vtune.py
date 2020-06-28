# How to dump file to xml
# amplxe-cl -collect hpc-performance -r build/icc/conv_i232_c.report build/icc/conv_i232_c
# amplxe-cl -report summary -report-output build/icc/conv_i232_c.xml -r build/icc/conv_i232_c.log/ -format xml
import delegator
import math
import shutil
import xml.etree.ElementTree as ET
import os

def get_vectorization_rate(path):
    tree = ET.parse(path)
    root = tree.getroot()
    vec_rate = root.find("./metric[@name='Vectorization']/value")
    return float(vec_rate.text)

# TODO: refactor these beacuse it's copied from another file.
def n_iterations_per_ms(goal_ms, per_iteration_nsec):
    return math.ceil(goal_ms * 1e6 / per_iteration_nsec)

def run(command):
    c = delegator.run(command)
    if c.return_code != 0:
        raise RuntimeError(f'Return code ({c.return_code}) '
                           f'when running the following command: {command}\n'
                           f'Error: {c.err}')
    return c.out

def remove_rf(path):
    if os.path.exists(path):
        shutil.rmtree(path)

def run_and_parse_results(command, vtune_dir):
    xml_path = f'{vtune_dir}/summary.xml'
    
    # remove_rf(vtune_dir)
    # remove_rf(xml_path)

    collect = (f'amplxe-cl -collect hpc-performance '
               f'-r "{vtune_dir}" '
               f'-- '
               f'{command}')
    report = (f'amplxe-cl -report summary '
              f'-r {vtune_dir} '
              f'-report-output {xml_path} '
              f'-format xml')

    collect_stdout = run(collect)
    report_stdout = run(report)
    vrate = get_vectorization_rate(xml_path)
    return vrate

def measure_vrate(exe_name, ns_per_iteration_path, output_path):
    with open(ns_per_iteration_path) as f:
        ns_per_iteration = float(f.read())

    # how mnay iterations for 100ms
    n_iterations = n_iterations_per_ms(2000, ns_per_iteration)
    command = f'./{exe_name} --measure {n_iterations}'
    vtune_path = f'{exe_name}.vtune'
    vrate = run_and_parse_results(command, vtune_path)
    with open(output_path, 'w') as f:
        f.write(f'{vrate}')

# exe_name = 'multiple.p0004.m0003.icc.fast.exe'
# ns_per_iter = 'multiple.p0004.m0003.icc.fast.nanosec_per_iteration'
# # exe_name = 'a.out'
# # ns_per_iter = 'periter.txt'
# measure_vrate(f'./{exe_name}', ns_per_iter, 'temp.output')
