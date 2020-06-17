from patterns import patterns
from compilers import compilers
from doit import get_var
from build import forall_mutations, forall_programs, PathBuilder, CommandBuilder
from aggregate import find_min_for_program, summarize_mutation
from determine_n_iterations import determine_n_iterations
from stats import calculate_stability

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
        exe_name = path_builder.full_prefix()
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
        exe_name = path_builder.full_prefix()
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
        exe_name = path_builder.full_prefix()
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
        command_builder = CommandBuilder(path_builder)
        source_path = path_builder.source_code_path()
        exe_name = path_builder.full_prefix()
        exe_command = command_builder.build_exe()
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
        command_builder = CommandBuilder(path_builder)
        source_path = path_builder.source_code_path()
        assembly_name = path_builder.assembly_path()
        assembly_command = command_builder.build_assembly()
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
        summary_path = path_builder.mutation_summary_path()
        runtimes_path = path_builder.runtimes_path()
        yield {
            'name': summary_path,
            'file_dep': [runtimes_path],
            'actions': [(summarize_mutation, args)],
            'targets': [summary_path]
        }
    yield from forall_mutations(patterns, aggregate)

def task_find_min_for_programs():
    """Find min program runtimes"""
    def find_min(compiler, mode, pattern, program, mutations):
        args = [compiler, mode, pattern, program]
        path_builder = PathBuilder(*args)
        min_path = path_builder.min_of_program_path()
        runtimes_files = []
        for m in mutations:
            path_builder.mutation = m
            runtimes_path = path_builder.runtimes_path()
            runtimes_files.append(runtimes_path)
        yield {
            'name': min_path,
            'file_dep': runtimes_files,
            'actions': [(find_min_for_program, args + [mutations])],
            'targets': [min_path]
        }
    yield from forall_programs(patterns, find_min)

def task_calculate_program_stability():
    """Calculate runtime stability"""
    def calculate(compiler, mode, pattern, program, _):
        args = [compiler, mode, pattern, program]
        path_builder = PathBuilder(*args)
        summary_path = path_builder.program_summary_path()
        stability_path = path_builder.program_stability_path()
        yield {
            'name': stability_path,
            'file_dep': [summary_path],
            'actions': [(calculate_stability, args)],
            'targets': [stability_path]
        }
    yield from forall_programs(patterns, calculate)
