from api import Skeleton, Mapping, CodegenConfig
from random import randint, seed
from codelet_generator import codelet_dir, generate_codelet_files, generate_batch_summary, SourceInfo
from pattern_ast import get_ordered_assignments, get_accesses, count_ops
from itertools import product

skeleton_code = """
declare size;
declare n_arrs;

for [(i, >=#_:order#, <=(size-1)/n_arrs)] {
  $_$
  $_$
  $_$
}
"""

def gen_program(order, n_zeroes, n_nonzeroes):
    stmts = [
        Mapping(
            '_',
            [f'{var}[i] = {var}[i-{order}] + #_# + #_# + #_# + #_# + #_#;'
             for var in ['A', 'B', 'C']],
            is_finite = True,
        )
    ]

    offset = [
        Mapping('order', [str(order)])
    ]

    zeroes = [
        Mapping('_', ['0']*n_zeroes + ['#_#']*n_nonzeroes, is_finite=True)
    ]

    rest = [
        Mapping('_',
                [ f'{var}[i-{order}]'
                  for (var, order) in product(['A', 'B', 'C'], range(1, order+1))
                ]
        )
    ]
        
    program = Skeleton(skeleton_code)
    program = program.fill_statements(stmts)
    program = program.fill_expressions(offset)
    program = program.fill_expressions(zeroes)
    program = program.fill_expressions(rest)
    return program

seed(0)
application = 'LoopGen'
batch = 'recurrence-fullness-20220814'

programs = set()
source_infos = []
n_arrs = 3
for order in range(1, 4):
    n_blanks = 15
    for n_zeroes in range(n_blanks, -1, -1):
        for v in range(3):
            n_terms = 18
            n_atoms = n_terms - n_zeroes
            skeleton = gen_program(order, n_zeroes, n_blanks-n_zeroes)

            code = f'3_stmts_recurrence_{order}_order_{n_atoms:02d}_atoms_v{v+1}'
            codelet = f'{code}_de'

            config = CodegenConfig()
            config.possible_values = {
                **{f'{var}[]': 8388608 for var in ['A', 'B', 'C']},
                'size': 8388608,
                'n_arrs': n_arrs,
            }
            config.types = {
                **{ f'{var}': 'double' for var in ['A', 'B', 'C'] },
            }
            config.initial_values = {
                **{ f'{var}' : 'drand(0.0, 1.0)' for var in ['A', 'B', 'C'] },
                'size': 'inputs[0]',
                'n_arrs': 'inputs[1]',
            }
            config.template_dir = 'codelet-template-int-inputs'
            config.output_dir = generate_codelet_files(application,
                                                       batch,
                                                       code,
                                                       codelet,
                                                       10,
                                                       [32000, n_arrs])
            config.array_as_ptr = True
            skeleton.generate_code(config)

            print(skeleton)
        
            # Gather source information
            si = SourceInfo()
            si.name = code
            si.n_stmts = 3
            uniq_atoms = set()
            graph = {}
            for assignment in get_ordered_assignments(skeleton.program):
                n_arrays = 0
                n_scalars = 0

                for access in get_accesses(assignment, ignore_indices=False):
                    if access.is_scalar():
                        n_scalars += 1
                    else:
                        n_arrays += 1

                # extra RHS counting
                lhs = assignment.lhs.var
                for access in get_accesses(assignment.rhs, ignore_indices=True):
                    # count unique aroms
                    uniq_atoms.add(str(access))
                    # count groups
                    if lhs not in graph:
                        graph[lhs] = set()
                    if access.var not in graph:
                        graph[access.var] = set()
                    graph[lhs].add(access.var)
                    graph[access.var].add(lhs)
            
                si.scalars.append(n_scalars)
                si.arrays.append(n_arrays)
                si.ops.append(count_ops(assignment))

            def dfs(v, visited, acc):
                if v in visited:
                    return
                acc.add(v)
                visited.add(v)
                for c in graph[v]:
                    dfs(c, visited, acc)

            groups = []
            remaining = set(graph.keys())
            while len(remaining) > 0:
                new_group = set()
                var = next(iter(remaining))
                dfs(var, set(), new_group)
                groups.append(new_group)
                for v in new_group:
                    if v in remaining:
                        remaining.remove(v)
            max_group_size = 0
            for g in groups:
                if len(g) > max_group_size:
                    max_group_size = len(g)

            fullness = n_atoms/3
            si.extra_columns.append('recurrence')
            si.extra_columns.append(order)
            si.extra_columns.append(n_atoms) # number of atoms
            si.extra_columns.append(len(uniq_atoms)) # number of unique atoms
            si.extra_columns.append(max_group_size)
            si.extra_columns.append(f'{fullness:.2f}')
            source_infos.append(si)

generate_batch_summary(application, batch, source_infos, ['computation', 'order', '# atoms', '# uniq atoms', 'group size', 'fullness'])
