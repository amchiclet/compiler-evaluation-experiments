from abstract_ast import Op, Access, Declaration, Assignment, AbstractLoop, Const, Program, ConstReplacer, get_loops, VarRenamer
from parser import parse_file
import random

class IdGenerator:
    def __init__(self, current=0):
        self.current = current
    def next_id(self):
        r = self.current
        self.current += 1
        return r

class Generator:
    def __init__(self, next_id=None):
        if next_id is None:
            self.next_id = IdGenerator().next_id
        else:
            self.next_id = next_id

class IndexGenerator:
    def __init__(self, mul_consts, add_consts, next_id=None):
        self.mul_consts = mul_consts
        self.add_consts = add_consts
        if next_id is None:
            self.next_id = IdGenerator().next_id
        else:
            self.next_id = next_id
    def generate(self, loop_vars):
        a_str = random.choice(self.mul_consts)
        x_str = random.choice(loop_vars)
        b_str = random.choice(self.add_consts)
        a = Access(a_str, node_id=self.next_id())
        x = Access(x_str, node_id=self.next_id())
        b = Access(b_str, node_id=self.next_id())
        ax = Op('*', [a, x], node_id=self.next_id())
        additive = random.choice(['+', '-'])
        return Op(additive, [ax, b], node_id=self.next_id())

class AccessGenerator(Generator):
    def __init__(self, decls, float_consts, index_gen, next_id=None):
        super(AccessGenerator, self).__init__(next_id)
        self.decls = decls
        self.float_consts = float_consts
        self.index_gen = index_gen
    def generate(self, loop_vars):
        pool = self.decls + self.float_consts
        choice = random.choice(pool)
        if type(choice) == Declaration:
            indices = []
            for _ in range(choice.n_dimensions):
                indices.append(self.index_gen.generate(loop_vars))
            return Access(choice.name, indices, node_id=self.next_id())
        elif type(choice) == str:
            return Access(choice, node_id=self.next_id())
        else:
            raise RuntimeError(f'Node type not supported {type(choice)}')

class OpGenerator(Generator):
    def __init__(self, ops, access_gen, next_id=None):
        super(OpGenerator, self).__init__(next_id)
        self.ops = ops
        self.access_gen = access_gen
    def generate(self, n_ops, loop_vars):
        if n_ops == 0:
            return self.access_gen.generate(loop_vars)

        nodes = [None] * n_ops
        for next_op in random.choices(self.ops, k=n_ops):
            blanks = []
            for i, node in enumerate(nodes):
                if node is None:
                    blanks.append(i)
            which = random.choice(blanks)
            delete_left = False
            if which-1 < 0 or nodes[which-1] is None:
                left = self.access_gen.generate(loop_vars)
            else:
                left = nodes[which-1]
                delete_left = True
            delete_right = False
            if which+1 >= len(nodes) or nodes[which+1] is None:
                right = self.access_gen.generate(loop_vars)
            else:
                right = nodes[which+1]
                delete_right = True
            new_node = Op(next_op, [left, right], self.next_id())
            nodes[which] = new_node
            if delete_right:
                del nodes[which+1]
            if delete_left:
                del nodes[which-1]
        assert(len(nodes) == 1)
        return nodes[0]

class AssignmentGenerator(Generator):
    def __init__(self, access_gen, op_gen, next_id=None):
        super(AssignmentGenerator, self).__init__(next_id)
        self.access_gen = access_gen
        self.op_gen = op_gen
    def generate(self, n_ops, loop_vars):
        lhs = self.access_gen.generate(loop_vars)
        rhs = self.op_gen.generate(n_ops, loop_vars)
        return Assignment(lhs, rhs, self.next_id())
        
class LoopGenerator(Generator):
    def __init__(self, assignment_gen, next_id=None):
        super(LoopGenerator, self).__init__(next_id)
        self.assignment_gen = assignment_gen
    def generate(self, n_depth, n_stmts, n_ops, loop_vars):
        assert(len(loop_vars) > n_depth)
        chosen_loop_vars = random.sample(loop_vars, k=n_depth)
        body = []
        for _ in range(n_stmts):
            stmt = self.assignment_gen.generate(n_ops, chosen_loop_vars)
            body.append(stmt)
        return AbstractLoop(chosen_loop_vars, body, self.next_id())

class ProgramGenerator(Generator):
    def __init__(self, loop_gen, next_id=None):
        super(ProgramGenerator, self).__init__(next_id)
        self.loop_gen = loop_gen
    def generate(self, n_loops, n_depth, n_stmts, n_ops, loop_vars):
        all_consts = set()

        access_gen = self.loop_gen.assignment_gen.access_gen
        index_gen = access_gen.index_gen
        all_consts.update(access_gen.float_consts,
                          index_gen.mul_consts,
                          index_gen.add_consts)

        gen_consts = []
        for c in sorted(list(all_consts)):
            gen_consts.append(Const(c, self.next_id()))
        gen_decls = []
        for d in sorted(access_gen.decls, key=lambda d: d.name):
            gen_decls.append(Declaration(d.name, d.n_dimensions, self.next_id()))

        gen_loops = []
        for _ in range(n_loops):
            loop = self.loop_gen.generate(n_depth, n_stmts, n_ops, loop_vars)
            gen_loops.append(loop)
        program = Program(gen_decls, gen_loops, gen_consts, self.next_id())

        ordered_loop_vars = []
        def populate_loop_vars(node):
            if isinstance(node, AbstractLoop):
                for loop_var in node.loop_vars:
                    if loop_var not in ordered_loop_vars:
                        ordered_loop_vars.append(loop_var)
                for stmt in node.body:
                    populate_loop_vars(stmt)
            elif isinstance(node, Program):
                for stmt in node.body:
                    populate_loop_vars(stmt)
            elif isinstance(node, Assignment):
                pass
            else:
                raise RuntimeError('get_loops: Unhandled type of node ' + str(type(node)))
        populate_loop_vars(program)

        replace_map_1 = {}
        for i, loop_var in enumerate(ordered_loop_vars):
            replace_map_1[loop_var] = '__' + str(i)
        renamer_1 = VarRenamer(replace_map_1)
        program.replace(renamer_1)

        replace_map_2 = {}
        sorted_loop_vars = sorted(loop_vars)
        for i, loop_var in enumerate(sorted_loop_vars):
            replace_map_2['__' + str(i)] = loop_var
        renamer_2 = VarRenamer(replace_map_2)
        program.replace(renamer_2)

        return program

def generate():
    id_gen = IdGenerator()
    mul_consts = ['a', 'b']
    add_consts = ['x', 'y']
    float_consts = ['f', 'g']
    loop_vars = ['i', 'j', 'k', 'l', 'm']
    decls = [
        Declaration('A', 1),
        Declaration('B', 1),
        Declaration('C', 1),
    ]
    ops = ['+', '*', '-']
    n_loops = 1
    n_depth = 3
    n_stmts = 3
    n_ops = 0
    # node = generate_program(n_loops, n_depth, n_stmts, n_ops, ops, decls, constants, loop_vars, id_gen.next_id)

    index_gen = IndexGenerator(mul_consts, add_consts, id_gen.next_id)
    access_gen = AccessGenerator(decls, float_consts, index_gen, id_gen.next_id)
    op_gen = OpGenerator(ops, access_gen, id_gen.next_id)
    access_gen_lhs = AccessGenerator(decls, [], index_gen, id_gen.next_id)
    assign_gen = AssignmentGenerator(access_gen_lhs, op_gen, id_gen.next_id)
    loop_gen = LoopGenerator(assign_gen, id_gen.next_id)
    program_gen = ProgramGenerator(loop_gen, id_gen.next_id)
    node = program_gen.generate(n_loops, n_depth, n_stmts, n_ops, loop_vars)
    return node

# print(node.pprint())
from pathlib import Path
output_dir = 'generated-patterns'
Path(output_dir).mkdir(parents=True, exist_ok=True)

import os
n_patterns = 10
for pattern_id in range(n_patterns):
    program = generate()
    pattern_filename = f'p{pattern_id:04d}.pattern'
    output_path = os.path.join(output_dir, pattern_filename)
    with open(output_path, 'w') as f:
        f.write(program.pprint())

# replace_map = {}
# for c in constants:
#     replace_map[c] = random.randint(0, 2)
# replacer = ConstReplacer(replace_map)
# program.replace(replacer)
# print(program.pprint())
