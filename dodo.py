from tests import tests
from compilers import compilers
from build import build_commands, get_exe_name, get_measure_name, get_n_iterations_name
from doit import get_var

DOIT_CONFIG = {
    'default_tasks': ['nothing'],
}

def task_nothing():
    """Default command. Does nothing."""
    return {
        'actions': ['echo Please check available commands with \\"doit list\\"'],
        'verbosity': 2,
    }

def forall(f):
    for c in compilers:
        for m in ['vec', 'novec']:
            for t in tests:
                yield from f(c, m, t)

def task_determine_iterations():
    """Determine number of iterations"""
    def determine(compiler, mode, test):
        exe_name = get_exe_name(compiler, mode, test)
        n_iterations_name = get_n_iterations_name(compiler, mode, test)
        yield {
            'name': exe_name,
            'file_dep': [exe_name],
            'actions': [f'python3 determine_n_iterations.py '
                        f'--command ./{exe_name} '
                        f'--goal_ms 100 > {n_iterations_name}'],
            'targets': [n_iterations_name]
        }
    yield from forall(determine)

def task_measure():
    """Measure"""
    def measure(compiler, mode, test):
        exe_name = get_exe_name(compiler, mode, test)
        measure_name = get_measure_name(compiler, mode, test)
        n_iterations_name = get_n_iterations_name(compiler, mode, test)
        yield {
            'name': exe_name,
            'file_dep': [exe_name],
            'actions': [f'./{exe_name} --measure $(cat {n_iterations_name}) > {measure_name}'],
            'targets': [measure_name]
        }
    yield from forall(measure)

def task_build():
    """Build"""
    def build(compiler, mode, test):
        assembly, exe = build_commands(compiler, mode, test)

        exe_name = get_exe_name(compiler, mode, test)
        yield {
            'name': exe_name,
            'file_dep': [test],
            'actions': [exe(exe_name)],
            'targets': [exe_name],
        }

        assembly_name = f'{exe_name}.s'
        yield {
            'name': assembly_name,
            'file_dep': [test],
            'actions': [assembly(assembly_name)],
            'targets': [assembly_name],
        }
    yield from forall(build)
