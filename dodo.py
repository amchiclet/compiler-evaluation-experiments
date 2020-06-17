from patterns import patterns
from compilers import compilers
from doit import get_var
from build import forall_modes, forall_mutations, forall_programs, PathBuilder, CommandBuilder, iterate_mutations
from aggregate import find_min_for_program, summarize_mutation
from determine_n_iterations import determine_n_iterations
from stats import calculate_mutation_perf_stability, calculate_perf_stability

DOIT_CONFIG = {
    'default_tasks': ['nothing'],
}

def task_nothing():
    """Default command. Does nothing."""
    return {
        'actions': ['echo Please check available commands with \\"doit list\\"'],
        'verbosity': 2,
    }

def task_determine_iterations():
    """Determine number of iterations"""
    def determine(compiler, mode, pattern, program, mutation):
        args = [compiler, mode, pattern, program, mutation]
        path_builder = PathBuilder(*args)
        exe_name = path_builder.exe_path()
        n_iterations_name = path_builder.n_iterations_path()
        goals_ms = 100
        yield {
            'name': exe_name,
            'file_dep': [exe_name],
            'actions': [(determine_n_iterations, args + [goals_ms])],
            # [f'python3 determine_n_iterations.py '
            #             f'--command ./{exe_name} '
            #             f'--goal_ms 100 > {n_iterations_name}'],
            'targets': [n_iterations_name]
        }
    yield from forall_mutations(patterns, determine)

def task_measure():
    """Measure"""
    def measure(compiler, mode, pattern, program, mutation):
        path_builder = PathBuilder(compiler, mode, pattern, program, mutation)
        exe_name = path_builder.exe_path()
        measure_name = path_builder.runtimes_path()
        n_iterations_name = path_builder.n_iterations_path()
        yield {
            'name': exe_name,
            'file_dep': [exe_name, n_iterations_name],
            'actions': [f'./{exe_name} --measure $(cat {n_iterations_name}) > {measure_name}'],
            'targets': [measure_name]
        }
    yield from forall_mutations(patterns, measure)

def task_test():
    """Test"""
    def test(compiler, mode, pattern, program, mutation):
        path_builder = PathBuilder(compiler, mode, pattern, program, mutation)
        exe_name = path_builder.exe_path()
        test_result_name = path_builder.test_result_path()
        yield {
            'name': exe_name,
            'file_dep': [exe_name],
            'actions': [f'./{exe_name} --test > {test_result_name}'],
            'targets': [test_result_name]
        }
    yield from forall_mutations(patterns, test)

def task_build():
    """Build"""
    def build(compiler, mode, pattern, program, mutation):
        path_builder = PathBuilder(compiler, mode, pattern, program, mutation)
        source_path = path_builder.source_code_path()
        exe_name = path_builder.exe_path()
        exe_command = CommandBuilder().build_exe(compiler, mode, source_path, exe_name)
        yield {
            'name': exe_name,
            'file_dep': [source_path],
            'actions': [f'echo {" ".join(exe_command)}', exe_command],
            'targets': [exe_name],
        }
    yield from forall_mutations(patterns, build)

def task_assembly():
    """Assembly"""
    def assembly(compiler, mode, pattern, program, mutation):
        path_builder = PathBuilder(compiler, mode, pattern, program, mutation)
        source_path = path_builder.source_code_path()
        assembly_name = path_builder.assembly_path()
        assembly_command = CommandBuilder().build_assembly(compiler, mode, source_path, assembly_name)
        yield {
            'name': assembly_name,
            'file_dep': [source_path],
            'actions': [f'echo {" ".join(assembly_command)}', assembly_command],
            'targets': [assembly_name],
        }
    yield from forall_mutations(patterns, assembly)

def task_summarize_mutations():
    """Summarize program runtimes"""
    def aggregate(compiler, mode, pattern, program, mutation):
        args = [compiler, mode, pattern, program, mutation]
        path_builder = PathBuilder(*args)
        summary_path = path_builder.summary_path()
        runtimes_path = path_builder.runtimes_path()
        yield {
            'name': summary_path,
            'file_dep': [runtimes_path],
            'actions': [(summarize_mutation, args)],
            'targets': [summary_path]
        }
    yield from forall_mutations(patterns, aggregate)

def task_find_min_of_programs():
    """Find min program runtimes"""
    def find_min(compiler, mode, pattern, program, mutations):
        args = [compiler, mode, pattern, program]
        path_builder = PathBuilder(*args)
        min_path = path_builder.min_path()
        runtimes_files = []
        for m in mutations:
            runtimes_path = path_builder.runtimes_path(m)
            runtimes_files.append(runtimes_path)
        yield {
            'name': min_path,
            'file_dep': runtimes_files,
            'actions': [(find_min_for_program, args + [mutations])],
            'targets': [min_path]
        }
    yield from forall_programs(patterns, find_min)

def task_calculate_mutation_perf_stability():
    """Calculate mutation perf mutation stability"""
    def calculate(compiler, mode, patterns):
        for pattern, programs in patterns:
            for program, mutations in programs:
                path_builder = PathBuilder(compiler, mode, pattern, program)
                min_path = path_builder.min_path()
                for mutation in mutations:
                    summary_path = path_builder.summary_path(mutation=mutation)
                    stability_path = path_builder.perf_stability_path(mutation=mutation)
                    yield {
                        'name': stability_path,
                        'file_dep': [min_path, summary_path],
                        'actions': [(calculate_mutation_perf_stability,
                                     [min_path, summary_path, stability_path])],
                        'targets': [stability_path]
                    }
    yield from forall_modes(patterns, calculate)

def task_calculate_compiler_perf_stability():
    """Calculate compiler perf mutation stability"""
    def calculate(compiler, mode, patterns):
        path_builder = PathBuilder(compiler, mode)
        stability_path = path_builder.perf_stability_path()
        print(stability_path)
        mutation_stabilities = [path_builder.perf_stability_path(*args)
                                for args in iterate_mutations(patterns)]
        yield {
            'name': stability_path,
            'file_dep': mutation_stabilities,
            'actions': [(calculate_perf_stability,
                         [mutation_stabilities, stability_path])],
            'targets': [stability_path]
        }
    yield from forall_modes(patterns, calculate)
