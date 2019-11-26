import delegator
import os
import os.path
from config import compilers, executables, Compiler, vtune_rounds
import argparse
import xml.etree.ElementTree as ET
import shutil
import statistics

# TODO create a database
# How to dump file to xml
# amplxe-cl -collect hpc-performance -r build/icc/conv_i232_c.report build/icc/conv_i232_c
# amplxe-cl -report summary -report-output build/icc/conv_i232_c.xml -r build/icc/conv_i232_c.log/ -format xml

class CommandBuilder:
    def __init__(self, exe, report, report_storage, xml, n_iterations):
        self.executable_path = exe
        self.vtune_output_path = report
        self.report_storage_path = report_storage
        self.xml_path = xml
        self.runtime_path = self.executable_path + '.vtune.runtimes'
        self.n_iterations = n_iterations
        print('Executable path: {}\nReport path: {}\nReport storage path: {}\nXml path: {}'.format(
            self.executable_path,
            self.vtune_output_path,
            self.report_storage_path,
            self.xml_path))

    def collect(self):
        return \
            f'amplxe-cl -collect hpc-performance -r "{self.vtune_output_path}" ' + \
            f'-- "{self.executable_path}" -o "{self.runtime_path}" -n "{self.n_iterations}"'

    def move_report_to_storage(self):
        pass
        
    def run(self):
        return self.executable_path

    def xml(self):
        return 'amplxe-cl -report summary -r "{}" -report-output "{}" -format xml'.format(
            self.report_storage_path, self.xml_path)

def parse_runtimes(path):
    runtimes = []
    with open(path) as f:
        for line in f:
            runtimes.append(int(line.split()[2]))
    return runtimes

def n_iterations_for_20_secs(build_root_dir, compiler_name, executable_name):
    path = f'{build_root_dir}/{compiler_name}/{executable_name}.runtimes'
    runtimes = parse_runtimes(path)
    mean = int(statistics.mean(runtimes))
    target = 20 * 1000000
    return target // mean

def measure(args):
    runtimes = {}
    vectorizations = {}
    def run_and_parse_output(compiler, executable, command_builder):
        nonlocal runtimes
        collect_again = not os.path.exists(command_builder.report_storage_path) or \
                        args.full
        print('collect again? {}'.format(collect_again))
        if collect_again:
            if os.path.exists(command_builder.vtune_output_path):
                shutil.rmtree(command_builder.vtune_output_path)
            if os.path.exists(command_builder.report_storage_path):
                shutil.rmtree(command_builder.report_storage_path)
            run_command = command_builder.collect()
        else:
            run_command = command_builder.run()
        print('Running ' + run_command)
        result = delegator.run(run_command)

        if not result.ok:
            print('the result is not ok')
            print(result.err)
            return None

        if collect_again:
            print('moving {}\n to {}'.format(command_builder.vtune_output_path,
                                             command_builder.report_storage_path))
            shutil.move(command_builder.vtune_output_path, command_builder.report_storage_path)

        if args.verbose:
            print(result.out)

        # The report path will exist at this point.
        if collect_again:
            if os.path.exists(command_builder.xml_path):
                os.remove(command_builder.xml_path)
            xml = command_builder.xml()
            print('Running ' + xml)
            result = delegator.run(xml)

            if not result.ok:
                print('the result is not ok')
                print(result.err)
                return None

            if args.verbose:
                print(result.out)

    for compiler in compilers:
        print('Executing tests for {}'.format(compiler.name))
        report_storage_dir =  os.path.join(args.report_root_dir, compiler.name)
        os.makedirs(report_storage_dir, exist_ok=True)

        for executable, _ in executables:
            # run for the set number of rounds, 20 seconds each
            for i in range(vtune_rounds):
                n_iterations = n_iterations_for_20_secs(args.build_root_dir, compiler.name, executable)
                executable_path = os.path.join(args.build_root_dir, compiler.build_dir, executable)
                vtune_output_path = executable_path + '.report'
                report_storage_path = os.path.join(report_storage_dir, executable + f'.{i}.report')
                xml_path = os.path.join(report_storage_dir, executable + f'.{i}.xml')
                command_builder = CommandBuilder(executable_path,
                                                 vtune_output_path,
                                                 report_storage_path,
                                                 xml_path,
                                                 n_iterations)
                run_and_parse_output(compiler, executable, command_builder)

if __name__ == '__main__':
    parser = argparse.ArgumentParser()
    parser.add_argument('--full', action='store_true', default=False)
    parser.add_argument('--verbose', action='store_true', default=False)
    parser.add_argument('--report_root_dir', required=True)
    parser.add_argument('--build_root_dir', required=True)

    args = parser.parse_args()

    measure(args)


    
