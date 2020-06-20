from patterns import patterns
from compilers import compilers
from doit import get_var
from build import PathBuilder, CommandBuilder, iterate_mutations, iterate_programs, iterate_compiler_vec_novec, iterate_compiler_pair_fast, iterate_compiler_fast, iterate_compiler_modes
from determine_n_iterations import determine_n_iterations
from stats import \
    calculate_perf_slowdown, \
    calculate_vec_speedup, \
    calculate_peer_fraction, \
    calculate_ci_geometric, \
    calculate_ci_proportion, \
    find_min_for_program, \
    summarize_mutation, \
    calculate_max, \
    calculate_normalized, \
    calculate_sum_of_logs, \
    calculate_is_faster

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
    for (compiler, mode) in iterate_compiler_modes():
        for (pattern, program, mutation) in iterate_mutations(patterns):
            path_builder = PathBuilder(compiler, mode, pattern, program, mutation)
            exe_name = path_builder.exe_path()
            n_iterations_name = path_builder.n_iterations_path()
            goals_ms = 100
            yield {
                'name': exe_name,
                'file_dep': [exe_name],
                'actions': [(determine_n_iterations, [exe_name, n_iterations_name, goals_ms])],
                'targets': [n_iterations_name]
            }

def task_measure():
    """Measure"""
    for (compiler, mode) in iterate_compiler_modes():
        for (pattern, program, mutation) in iterate_mutations(patterns):
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

def task_test():
    """Test"""
    for (compiler, mode) in iterate_compiler_modes():
        for (pattern, program, mutation) in iterate_mutations(patterns):
            path_builder = PathBuilder(compiler, mode, pattern, program, mutation)
            exe_name = path_builder.exe_path()
            test_result_name = path_builder.test_result_path()
            yield {
                'name': exe_name,
                'file_dep': [exe_name],
                'actions': [f'./{exe_name} --test > {test_result_name}'],
                'targets': [test_result_name]
            }

def task_build():
    """Build"""
    for (compiler, mode) in iterate_compiler_modes():
        for (pattern, program, mutation) in iterate_mutations(patterns):
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

def task_assembly():
    """Assembly"""
    for (compiler, mode) in iterate_compiler_modes():
        for (pattern, program, mutation) in iterate_mutations(patterns):
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

def task_summarize_mutations():
    """Summarize program runtimes"""
    for (compiler, mode) in iterate_compiler_modes():
        for (pattern, program, mutation) in iterate_mutations(patterns):
            path_builder = PathBuilder(compiler, mode, pattern, program, mutation)
            summary_path = path_builder.summary_path()
            runtimes_path = path_builder.runtimes_path()
            yield {
                'name': summary_path,
                'file_dep': [runtimes_path],
                'actions': [(summarize_mutation, [runtimes_path, summary_path])],
                'targets': [summary_path]
            }

def task_find_min_of_programs():
    """Find min program runtimes"""
    for (compiler, mode) in iterate_compiler_modes():
        for (pattern, program, mutations) in iterate_programs(patterns):
            path_builder = PathBuilder(compiler, mode, pattern, program)
            min_path = path_builder.min_path()
            runtimes_files = []
            for m in mutations:
                runtimes_path = path_builder.runtimes_path(m)
                runtimes_files.append(runtimes_path)
            yield {
                'name': min_path,
                'file_dep': runtimes_files,
                'actions': [(find_min_for_program, [runtimes_files, min_path])],
                'targets': [min_path]
            }

def task_calculate_mutation_perf():
    """Calculate mutation perf mutation stability"""
    for (compiler, mode) in iterate_compiler_modes():
        for (pattern, program, mutations) in iterate_programs(patterns):
            path_builder = PathBuilder(compiler, mode, pattern, program)
            min_path = path_builder.min_path()
            for mutation in mutations:
                summary_path = path_builder.summary_path(mutation=mutation)
                stability_path = path_builder.perf_path(mutation=mutation)
                yield {
                    'name': stability_path,
                    'file_dep': [min_path, summary_path],
                    'actions': [(calculate_perf_slowdown,
                                 [min_path, summary_path, stability_path])],
                    'targets': [stability_path]
                }

def task_find_best_vec_speedup_of_programs():
    """Find best vec speedup"""
    for compiler in iterate_compiler_vec_novec():
        for (pattern, program, mutations) in iterate_programs(patterns):
            path_builder = PathBuilder(compiler=compiler, pattern=pattern, program=program)
            best_vec_path = path_builder.best_vec_speedup_path()
            speedup_paths = []
            for m in mutations:
                speedup_path = path_builder.vec_speedup_path(mutation=m)
                speedup_paths.append(speedup_path)
            yield {
                'name': best_vec_path,
                'file_dep': speedup_paths,
                'actions': [(calculate_max, [speedup_paths, best_vec_path])],
                'targets': [best_vec_path]
            }

def task_calculate_mutation_normalized_vec_speedup():
    """Calculate vec perf mutation stability"""
    for compiler in iterate_compiler_vec_novec():
        for (pattern, program, mutations) in iterate_programs(patterns):
            path_builder = PathBuilder(compiler=compiler, pattern=pattern, program=program)
            best_vec_path = path_builder.best_vec_speedup_path()
            for m in mutations:
                vec_path = path_builder.vec_speedup_path(mutation=m)
                normalized_vec_path = path_builder.normalized_vec_speedup_path(mutation=m)
                yield {
                    'name': normalized_vec_path,
                    'file_dep': [best_vec_path, vec_path],
                    'actions': [(calculate_normalized,
                                 [vec_path, best_vec_path, normalized_vec_path])],
                    'targets': [normalized_vec_path]
                }

def task_calculate_mutation_vec():
    """Calculate mutation vec speedup"""
    for (pattern, program, mutation) in iterate_mutations(patterns):
        path_builder = PathBuilder(pattern=pattern, program=program, mutation=mutation)
        for compiler in iterate_compiler_vec_novec():
            vec_path = path_builder.summary_path(compiler=compiler, mode='fast')
            novec_path = path_builder.summary_path(compiler=compiler, mode='novec')
            speedup_path = path_builder.vec_speedup_path(compiler=compiler)
            success_path = path_builder.vec_success_path(compiler=compiler)
            yield {
                'name': speedup_path,
                'file_dep': [vec_path, novec_path],
                'actions': [(calculate_vec_speedup,
                             [vec_path, novec_path, speedup_path, success_path])],
                'targets': [speedup_path, success_path]
            }

def task_calculate_mutation_peer():
    """Calculate mutation peer fraction"""
    for c1, c2 in iterate_compiler_pair_fast():
        c1_is_faster = PathBuilder(mode='fast').peer_is_faster_path(c1, c2)
        for (pattern, program, mutation) in iterate_mutations(patterns):
            pb = PathBuilder(mode='fast',
                             pattern=pattern,
                             program=program,
                             mutation=mutation)
            c1_path = pb.summary_path(compiler=c1)
            c2_path = pb.summary_path(compiler=c2)
            fraction_path = pb.peer_fraction_path(c1, c2)
            is_faster_path = pb.peer_is_faster_path(c1, c2)
            yield {
                'name': fraction_path,
                'file_dep': [c1_path, c2_path, c1_is_faster],
                'actions': [(calculate_peer_fraction,
                             [c1_path, c2_path, c1_is_faster, fraction_path, is_faster_path])],
                'targets': [fraction_path, is_faster_path]
            }

def task_find_best_peer_fraction_of_programs():
    """Find best peer fraction speedup"""
    for c1, c2 in iterate_compiler_pair_fast():
        for (pattern, program, mutations) in iterate_programs(patterns):
            path_builder = PathBuilder(mode='fast', pattern=pattern, program=program)
            best_path = path_builder.best_peer_fraction_path(c1, c2)
            fraction_paths = []
            for m in mutations:
                fraction_path = path_builder.peer_fraction_path(c1, c2, mutation=m)
                fraction_paths.append(fraction_path)
            yield {
                'name': best_path,
                'file_dep': fraction_paths,
                'actions': [(calculate_max, [fraction_paths, best_path])],
                'targets': [best_path]
            }

def task_calculate_mutation_normalized_peer_fraction():
    """Calculate normalized peer fraction"""
    for c1, c2 in iterate_compiler_pair_fast():
        for (pattern, program, mutations) in iterate_programs(patterns):
            pb = PathBuilder(mode='fast', pattern=pattern, program=program)
            best_path = pb.best_peer_fraction_path(c1, c2)
            for m in mutations:
                peer_fraction_path = pb.peer_fraction_path(c1, c2, mutation=m)
                normalized_path = pb.normalized_peer_fraction_path(c1, c2, mutation=m)
                yield {
                    'name': normalized_path,
                    'file_dep': [best_path, peer_fraction_path],
                    'actions': [(calculate_normalized,
                                 [peer_fraction_path, best_path, normalized_path])],
                    'targets': [normalized_path]
                }

def task_calculate_vec_ci():
    """Calculate compiler vectorization ci"""
    for compiler in iterate_compiler_vec_novec():
        pb = PathBuilder(compiler)
        speedup_samples = [pb.normalized_vec_speedup_path(pattern=pattern,
                                                          program=program,
                                                          mutation=mutation)
                           for (pattern, program, mutation) in iterate_mutations(patterns)]
        speedup_output = pb.vec_speedup_ci_path()
        yield {
            'name': speedup_output,
            'file_dep': speedup_samples,
            'actions': [(calculate_ci_geometric, [speedup_samples, speedup_output])],
            'targets': [speedup_output]
        }

        # success_samples = [pb.vec_success_path(pattern=pattern,
        #                                                  program=program,
        #                                                  mutation=mutation)
        #                    for (pattern, program, mutation) in iterate_mutations(patterns)]
        # success_output = pb.vec_success_path()
        # yield {
        #     'name': success_output,
        #     'file_dep': success_samples,
        #     'actions': [(calculate_ci_proportion, [success_samples, success_output])],
        #     'targets': [success_output]
        # }

def task_calculate_sum_of_logs():
    """Calculate compiler sum of logs"""
    for compiler in iterate_compiler_fast():
        pb = PathBuilder(compiler, 'fast')
        samples = [pb.summary_path(pattern=pattern,
                                   program=program,
                                   mutation=mutation)
                   for (pattern, program, mutation) in iterate_mutations(patterns)]
        output = pb.sum_of_logs_path()
        yield {
            'name': output,
            'file_dep': samples,
            'actions': [(calculate_sum_of_logs, [samples, output])],
            'targets': [output]
        }

def task_calculate_peer_order():
    """Calculate mutation peer order"""
    for c1, c2 in iterate_compiler_pair_fast():
        pb = PathBuilder(mode='fast')
        c1_sol = pb.sum_of_logs_path(compiler=c1)
        c2_sol = pb.sum_of_logs_path(compiler=c2)
        output = pb.peer_is_faster_path(c1, c2)
        yield {
            'name': output,
            'file_dep': [c1_sol, c2_sol],
            'actions': [(calculate_is_faster, [c1_sol, c2_sol, output])],
            'targets': [output]
        }

def task_calculate_perf_ci():
    """Calculate compiler perf ci"""
    for compiler in iterate_compiler_fast():
        pb = PathBuilder(compiler, 'fast')
        samples = [pb.perf_path(pattern=pattern,
                                program=program,
                                mutation=mutation)
                   for (pattern, program, mutation) in iterate_mutations(patterns)]
        output = pb.perf_ci_path()
        yield {
            'name': output,
            'file_dep': samples,
            'actions': [(calculate_ci_geometric, [samples, output])],
            'targets': [output]
        }

def task_calculate_peer_ci():
    """Calculate compiler peer ci"""
    for c1, c2 in iterate_compiler_pair_fast():
        pb = PathBuilder(mode='fast')
        fraction_samples = [pb.normalized_peer_fraction_path(c1, c2,
                                                             pattern=pattern,
                                                             program=program,
                                                             mutation=mutation)
                            for (pattern, program, mutation) in iterate_mutations(patterns)]
        fraction_output = pb.peer_fraction_ci_path(c1, c2)
        yield {
            'name': fraction_output,
            'file_dep': fraction_samples,
            'actions': [(calculate_ci_geometric, [fraction_samples, fraction_output])],
            'targets': [fraction_output]
        }

        is_faster_samples = [pb.peer_is_faster_path(c1,
                                                    c2,
                                                    pattern=pattern,
                                                    program=program,
                                                    mutation=mutation)
                             for (pattern, program, mutation) in iterate_mutations(patterns)]
        is_faster_output = pb.peer_is_faster_ci_path(c1, c2)
        yield {
            'name': is_faster_output,
            'file_dep': is_faster_samples,
            'actions': [(calculate_ci_proportion, [is_faster_samples, is_faster_output])],
            'targets': [is_faster_output]
        }
