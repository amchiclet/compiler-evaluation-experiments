from build import PathBuilder
from simple_formatter import SimpleFormatter
from loguru import logger
from pathlib import Path
import os

class CodeGen:
    def __init__(self, output_dir):
        self.output_dir = output_dir

        Path(output_dir).mkdir(parents=True, exist_ok=True)

        root_dir = os.path.dirname(os.path.abspath(__file__))
        src_dodo_path= f'{root_dir}/dodo.py'
        dodo_path = f'{output_dir}/dodo.py'
        if not os.path.exists(dodo_path):
            os.symlink(src_dodo_path, dodo_path)
        src_main_c_path = f'{root_dir}/main.c'
        main_c_path = f'{output_dir}/main.c'
        if not os.path.exists(main_c_path):
            os.symlink(src_main_c_path, main_c_path)

    def generate_wrapper(self, pattern_str, instance_str, instance):
        pb = PathBuilder(pattern=pattern_str, program=instance_str)
        sf = SimpleFormatter(instance)
        logger.info(f'Generating wrapper for {pattern_str}.{instance_str}')
        wrapper = pb.wrapper_path()
        sf.write_kernel_wrapper(f'{self.output_dir}/{wrapper}')

    def generate_code(self, pattern_str, instance_str, mutation_str, instance):
        pb = PathBuilder(pattern=pattern_str, program=instance_str, mutation=mutation_str)
        sf = SimpleFormatter(instance)
        logger.info(f'Generating code for {pattern_str}.{instance_str}.{mutation_str}\n'
                    f'{instance.pattern.pprint()}')
        core = pb.core_path()
        sf.write_core(f'{self.output_dir}/{core}')
        # TODO copy main

    def generate_pattern_file(self, patterns_map):
        patterns = []
        for pattern in sorted(patterns_map.keys()):
            instances = []
            for instance in sorted(patterns_map[pattern].keys()):
                mutations = sorted(patterns_map[pattern][instance])
                instances.append((instance, mutations))
            patterns.append((pattern, instances))

        # Print out the patterns for the build script to work
        # once this is serializable, then we will be able to iterate through mutations
        from pprint import PrettyPrinter
        with open(f'{self.output_dir}/patterns.py', 'w') as f:
            f.write('patterns = ')
            PrettyPrinter(indent=2, stream=f).pprint(patterns)
