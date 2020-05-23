from tests import tests
from compilers import compilers, build_commands
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

def task_measure():
    """Measure"""
    def measure(compiler, mode, test):
        exe_name = f'{test}.{compiler}.{mode}'
        measure_name = f'{exe_name}.runtimes'
        yield {
            'name': exe_name,
            'file_dep': [exe_name],
            'actions': [f'./{exe_name} --measure {get_var("iterations", 1)} > {measure_name}'],
            'targets': [measure_name]
        }
    yield from forall(measure)

def task_build():
    """Build"""
    def build(compiler, mode, test):
        assembly, exe = build_commands(compiler, mode, test)

        exe_name = f'{test}.{compiler}.{mode}'
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
