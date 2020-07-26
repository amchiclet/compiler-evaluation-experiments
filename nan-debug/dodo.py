from patterns import patterns
from compilers import compilers
from doit import get_var
from build import PathBuilder, CommandBuilder, iterate_mutations, iterate_programs, iterate_compiler_vec_novec, iterate_compiler_pair_fast, iterate_compiler_fast, iterate_compiler_modes
from measure import calculate_ns_per_iteration, measure_runtime, calculate_checksum

from vtune import measure_vrate

DOIT_CONFIG = {
    'default_tasks': ['nothing'],
}

def task_nothing():
    """Default command. Does nothing."""
    return {
        'actions': ['echo Please check available commands with \\"doit list\\"'],
        'verbosity': 2,
    }

def task_find_ns_per_iteration():
    """Determine nanosecond per iteration"""
    for (compiler, mode) in iterate_compiler_modes():
        for (pattern, program, mutation) in iterate_mutations(patterns):
            path_builder = PathBuilder(compiler, mode, pattern, program, mutation)
            exe_name = path_builder.exe_path()
            output_path = path_builder.ns_per_iteration_path()
            yield {
                'name': output_path,
                'file_dep': [exe_name],
                'actions': [(calculate_ns_per_iteration, [exe_name, output_path])],
                'targets': [output_path]
            }

def task_measure_runtimes():
    """Determine runtimes nanosec"""
    for (compiler, mode) in iterate_compiler_modes():
        for (pattern, program, mutation) in iterate_mutations(patterns):
            path_builder = PathBuilder(compiler, mode, pattern, program, mutation)
            exe_name = path_builder.exe_path()
            ns_per_iteration_path = path_builder.ns_per_iteration_path()
            output_path = path_builder.runtimes_ns_path()
            yield {
                'name': output_path,
                'file_dep': [exe_name, ns_per_iteration_path],
                'actions': [(measure_runtime, [exe_name, ns_per_iteration_path, output_path])],
                'targets': [output_path]
            }

def task_calculate_checksum():
    """Calculate checksum"""
    for (compiler, mode) in iterate_compiler_modes():
        for (pattern, program, mutation) in iterate_mutations(patterns):
            path_builder = PathBuilder(compiler, mode, pattern, program, mutation)
            exe_name = path_builder.exe_path()
            output_path = path_builder.checksum_path()
            yield {
                'name': output_path,
                'file_dep': [exe_name],
                'actions': [(calculate_checksum, [exe_name, output_path])],
                'targets': [output_path]
            }

def task_measure_vector_rates():
    """Determine vector rates"""
    for (compiler, mode) in iterate_compiler_modes():
        for (pattern, program, mutation) in iterate_mutations(patterns):
            path_builder = PathBuilder(compiler, mode, pattern, program, mutation)
            exe_name = path_builder.exe_path()
            ns_per_iteration_path = path_builder.ns_per_iteration_path()
            output_path = path_builder.vector_rate_path()
            yield {
                'name': output_path,
                'file_dep': [exe_name, ns_per_iteration_path],
                'actions': [(measure_vrate, [exe_name, ns_per_iteration_path, output_path])],
                'targets': [output_path]
            }

def task_build():
    """Build"""
    for compiler in compilers:
        pb = PathBuilder(compiler)
        main_path = pb.main_path()
        main_obj_path = pb.main_obj_path()
        main_command = CommandBuilder().build_object(compiler, 'novec', main_path, main_obj_path)
        yield {
            'name': main_obj_path,
            'file_dep': [main_path],
            'actions': [f'echo {" ".join(main_command)}', main_command],
            'targets': [main_obj_path],
        }

    for (compiler, mode) in iterate_compiler_modes():
        for (pattern, program, _) in iterate_programs(patterns):
            pb = PathBuilder(compiler, mode, pattern, program)
            wrapper_path = pb.wrapper_path()
            wrapper_obj_path = pb.wrapper_obj_path()
            wrapper_command = CommandBuilder().build_object(compiler,
                                                            'novec',
                                                            wrapper_path,
                                                            wrapper_obj_path)
            yield {
                'name': wrapper_obj_path,
                'file_dep': [wrapper_path],
                'actions': [f'echo {" ".join(wrapper_command)}', wrapper_command],
                'targets': [wrapper_obj_path],
            }

    for (compiler, mode) in iterate_compiler_modes():
        for (pattern, program, mutation) in iterate_mutations(patterns):
            pb = PathBuilder(compiler, mode, pattern, program, mutation)

            # Only the core is compiled with the needed setting
            core_path = pb.core_path()
            core_obj_path = pb.core_obj_path()
            core_command = CommandBuilder().build_object(compiler, mode, core_path, core_obj_path)
            yield {
                'name': core_obj_path,
                'file_dep': [core_path],
                'actions': [f'echo {" ".join(core_command)}', core_command],
                'targets': [core_obj_path],
            }

            main_obj_path = PathBuilder(compiler).main_obj_path()
            wrapper_obj_path = PathBuilder(compiler, mode, pattern, program).wrapper_obj_path()

            objs = [main_obj_path, wrapper_obj_path, core_obj_path]
            exe_name = pb.exe_path()
            exe_command = CommandBuilder().link_objects(compiler, 'novec', objs, exe_name)
            yield {
                'name': exe_name,
                'file_dep': objs,
                'actions': [f'echo {" ".join(exe_command)}', exe_command],
                'targets': [exe_name],
            }

def task_assembly():
    """Assembly"""
    for (compiler, mode) in iterate_compiler_modes():
        for (pattern, program, mutation) in iterate_mutations(patterns):
            path_builder = PathBuilder(compiler, mode, pattern, program, mutation)
            source_path = path_builder.core_path()
            assembly_name = path_builder.assembly_path()
            assembly_command = CommandBuilder().build_assembly(compiler, mode, source_path, assembly_name)
            yield {
                'name': assembly_name,
                'file_dep': [source_path],
                'actions': [f'echo {" ".join(assembly_command)}', assembly_command],
                'targets': [assembly_name],
            }
