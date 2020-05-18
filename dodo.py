from tests import tests
from compilers import compilers, build_commands

def forall(f):
    for c in compilers:
        for m in ['vec', 'novec']:
            for t in tests:
                yield from f(c, m, t)
    
def task_rm():
    """Clean"""
    def rm(compiler, mode, test):
        exe_name = f'{test}.{compiler}.{mode}'
        yield {
            'name': exe_name,
            'actions': [['rm', '-f', exe_name]],
        }
        assembly_name = f'{exe_name}.s'
        yield {
            'name': assembly_name,
            'actions': [['rm', '-f', assembly_name]],
        }
    yield from forall(rm)

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
