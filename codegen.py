from build import PathBuilder
from simple_formatter import SimpleFormatter

class CodeGen:
    def __init__(self, output_dir):
        self.output_dir = output_dir
        from pathlib import Path
        Path(output_dir).mkdir(parents=True, exist_ok=True)
        import os
        dodo_path = f'{output_dir}/dodo.py'
        if not os.path.exists(dodo_path):
            os.symlink('../dodo.py', dodo_path)
        main_c_path = f'{output_dir}/main.c'
        if not os.path.exists(main_c_path):
            os.symlink('../main.c', main_c_path)

        self.patterns_map = {}

    def generate_wrapper(self, pattern_str, program_str,
                         ast, var_map):
        if pattern_str not in self.patterns_map:
            self.patterns_map[pattern_str] = {}
        if program_str not in self.patterns_map[pattern_str]:
            self.patterns_map[pattern_str][program_str] = []
        pb = PathBuilder(pattern=pattern_str, program=program_str)
        sf = SimpleFormatter(ast, var_map)
        wrapper = pb.wrapper_path()
        sf.write_kernel_wrapper(f'{self.output_dir}/{wrapper}')

    def generate_code(self, pattern_str, program_str, mutation_str,
                      ast, var_map):
        if pattern_str not in self.patterns_map:
            self.patterns_map[pattern_str] = {}
        if program_str not in self.patterns_map[pattern_str]:
            self.patterns_map[pattern_str][program_str] = []
        self.patterns_map[pattern_str][program_str].append(mutation_str)
        pb = PathBuilder(pattern=pattern_str, program=program_str, mutation=mutation_str)
        sf = SimpleFormatter(ast, var_map)
        core = pb.core_path()
        sf.write_core(f'{self.output_dir}/{core}')
        # TODO copy main

    def generate_pattern_file(self):
        patterns = []
        for pattern in sorted(self.patterns_map.keys()):
            programs = []
            for program in sorted(self.patterns_map[pattern].keys()):
                mutations = sorted(self.patterns_map[pattern][program])
                programs.append((program, mutations))
            patterns.append((pattern, programs))

        # Print out the patterns for the build script to work
        # once this is serializable, then we will be able to iterate through mutations
        from pprint import PrettyPrinter
        with open(f'{self.output_dir}/patterns.py', 'w') as f:
            f.write('patterns = ')
            PrettyPrinter(indent=2, stream=f).pprint(patterns)
