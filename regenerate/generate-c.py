from codegen import CodeGen
from patterns import patterns
from build import PathBuilder, iterate_compiler_modes
from parser import parse_file
from variable_map import Instance

codegen = CodeGen('code')
for p, instances in patterns:
    for i, mutations in instances:
        instance, _ = parse_file(f'instances/{p}.{i}.pattern')
        codegen.generate_code(p, i, 'orig', Instance(instance, {}))
        # for m in mutations:
        #     mutation, _ = parse_file(f'mutations/{p}.{i}.{m}.pattern')
        #     codegen.generate_code(p, i, m, Instance(mutation, {}))
