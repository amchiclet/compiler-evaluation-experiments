import delegator
import os
import os.path
from config import compilers, executables, Compiler, vtune_rounds
import argparse
import xml.etree.ElementTree as ET
import shutil
import statistics

class Metrics:
    # all of these are supposed to have a function with name format_*
    def get_attribute_names():
        return [
            'runtime',
            'gflops',
            'sp_v32',
            'sp_v128',
            'sp_v256',
            'sp_v512',
            'dp_v32',
            'dp_v128',
            'dp_v256',
            'dp_v512',
            'cache',
            'dram',
        ]

    def __init__(self):
        self.gflops = []
        self.sp_v32_fraction = []
        self.sp_v128_fraction = []
        self.sp_v256_fraction = []
        self.sp_v512_fraction = []
        self.dp_v32_fraction = []
        self.dp_v128_fraction = []
        self.dp_v256_fraction = []
        self.dp_v512_fraction = []
        self.cache_bound_fraction = []
        self.dram_bound_fraction = []
        self.runtimes = []

    def format_values(self, values):
        if not values:
            return 'N/A'
        return self.format_range(values)
        
    def format_range(self, values):
        print(values)
        mean = statistics.mean(values)
        stddev = statistics.stdev(values)
        return f'{mean:.2f} ± {stddev:.2f}'

    def format_gflops(self):
        return self.format_values(self.gflops)

    def format_sp_v32(self):
        return self.format_values(self.sp_v32_fraction)

    def format_sp_v128(self):
        return self.format_values(self.sp_v128_fraction)

    def format_sp_v256(self):
        return self.format_values(self.sp_v256_fraction)

    def format_sp_v512(self):
        return self.format_values(self.sp_v512_fraction)

    def format_dp_v32(self):
        return self.format_values(self.dp_v32_fraction)

    def format_dp_v128(self):
        return self.format_values(self.dp_v128_fraction)

    def format_dp_v256(self):
        return self.format_values(self.dp_v256_fraction)

    def format_dp_v512(self):
        return self.format_values(self.dp_v512_fraction)

    def format_cache(self):
        return self.format_values(self.cache_bound_fraction)

    def format_dram(self):
        return self.format_values(self.dram_bound_fraction)

    def format_runtime(self):
        return self.format_values(self.runtimes)

    def parse_another_vtune_xml(self, path):
        if not os.path.exists(path):
            return

        tree = ET.parse(path)
        root = tree.getroot()

        self.gflops.append(float(
            root.find("./metric[@name='Elapsed Time']/metric[@name='SP GFLOPS']/value").text))

        instr_mix = root.find("./metric[@name='Vectorization']/metric[@name='Instruction Mix']")
        sp_flops = instr_mix.find("./metric[@name='SP FLOPs']")
        sp_total = sp_flops.find("./value")

        if sp_total is not None:
            sp_total_fraction = float(sp_total.text)
    
            v32 = sp_flops.find("./metric[@name='Scalar']/value")
            if v32 is not None:
                self.sp_v32_fraction.append(float(v32.text) * sp_total_fraction)

            sp_packed = sp_flops.find("./metric[@name='Packed']")
            v128 = sp_packed.find("./metric[@name='128-bit']/value")
            if v128 is not None:
                self.sp_v128_fraction.append(float(v128.text) * sp_total_fraction)

            v256 = sp_packed.find("./metric[@name='256-bit']/value")
            if v256 is not None:
                self.sp_v256_fraction.append(float(v256.text) * sp_total_fraction)

            v512 = sp_packed.find("./metric[@name='512-bit']/value")
            if v512 is not None:
                self.sp_v512_fraction.append(float(v512.text) * sp_total_fraction)

        dp_flops = instr_mix.find("./metric[@name='DP FLOPs']")
        dp_total = dp_flops.find("./value")

        if dp_total is not None:
            dp_total_fraction = float(dp_total.text)
    
            v32 = dp_flops.find("./metric[@name='Scalar']/value")
            if v32 is not None:
                self.dp_v32_fraction.append(float(v32.text) * dp_total_fraction)

            dp_packed = dp_flops.find("./metric[@name='Packed']")
            v128 = dp_packed.find("./metric[@name='128-bit']/value")
            if v128 is not None:
                self.dp_v128_fraction.append(float(v128.text) * dp_total_fraction)

            v256 = dp_packed.find("./metric[@name='256-bit']/value")
            if v256 is not None:
                self.dp_v256_fraction.append(float(v256.text) * dp_total_fraction)

            v512 = dp_packed.find("./metric[@name='512-bit']/value")
            if v512 is not None:
                self.dp_v512_fraction.append(float(v512.text) * dp_total_fraction)

        memory_bound = root.find("./metric[@name='Memory Bound']")
        if memory_bound is not None:
            cache_bound = memory_bound.find("./metric[@name='Cache Bound']/value")
            if cache_bound is not None:
                self.cache_bound_fraction.append(float(cache_bound.text))
            dram_bound = memory_bound.find("./metric[@name='DRAM Bound']/value")
            if dram_bound is not None:
                self.dram_bound_fraction.append(float(dram_bound.text))

    def parse_runtimes(self, path):
        if not os.path.exists(path):
            return
        runtimes = []
        with open(path) as f:
            for line in f:
                self.runtimes.append(int(line.split()[2]))

def parse_metrics(args):
    metrics = {}
    report_path = args.report_root_dir
    build_path = args.build_root_dir
    compiler_names = [c.name for c in compilers]
    for compiler_name in compiler_names:
        metrics[compiler_name] = {}
        for executable_name, _ in executables:
            metric = Metrics()
            for i in range(vtune_rounds):
                vtune_xml_path = f'{report_path}/{compiler_name}/{executable_name}.{i}.xml'
                metric.parse_another_vtune_xml(vtune_xml_path)

            runtime_path = f'{build_path}/{compiler_name}/{executable_name}.runtimes'
            metric.parse_runtimes(runtime_path)
            metrics[compiler_name][executable_name] = metric
    return metrics

def report_for_compiler_group(compiler_names, table):
    print(','.join(['program'] + compiler_names))
    for executable_name, _ in executables:
        print(executable_name)
        for attribute_name in Metrics.get_attribute_names():
            row = [attribute_name]
            for compiler_name in compiler_names:
                value = 'N/A'
                if compiler_name in table and \
                   attribute_name in table[compiler_name] and \
                   executable_name in table[compiler_name][attribute_name]:
                    value = table[compiler_name][attribute_name][executable_name] 
                row.append(value)
            print(','.join(row))

if __name__ == '__main__':
    parser = argparse.ArgumentParser()
    parser.add_argument('--report_root_dir', required=True)
    parser.add_argument('--build_root_dir', required=True)
    args = parser.parse_args()
    metrics = parse_metrics(args)

    table = {}
    compiler_names = [c.name for c in compilers]
    for compiler_name in compiler_names:
        table[compiler_name] = {}
        for attribute_name in Metrics.get_attribute_names():
            table[compiler_name][attribute_name] = {}
            for executable_name, _ in executables:
                metric = metrics[compiler_name][executable_name]
                formatter = getattr(metric, f'format_{attribute_name}')
                table[compiler_name][attribute_name][executable_name] = formatter()

    pgi_group = ['pgi_s', 'pgi_v']
    report_for_compiler_group(pgi_group, table)

    clang_group = ['clang_s', 'clang_v']
    report_for_compiler_group(clang_group, table)

    gcc_group = ['gcc_s', 'gcc_v']
    report_for_compiler_group(gcc_group, table)

    icc_group = ['icc_s', 'icc_v']
    report_for_compiler_group(icc_group, table)




    
