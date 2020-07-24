from abstract_ast import Op, Access, Declaration, Assignment, AbstractLoop, Const, Program, ConstReplacer, get_loops, VarRenamer
from pattern_normalizer import normalize_pattern
import random
from loguru import logger

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
    def generate(self, n_loops, n_depth, loop_vars, n_stmts, n_ops):
        all_consts = set()

        access_gen = self.loop_gen.assignment_gen.op_gen.access_gen
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
        return program

class PatternInfo:
    def __init__(self, decls=None, mul_consts=None, add_consts=None,
                 data_consts=None, ops=None, loop_vars=None,
                 n_loops=0, n_depth=0, n_stmts=0, n_ops=0):
        self.decls = decls if decls else []
        self.mul_consts = mul_consts if mul_consts else []
        self.add_consts = add_consts if add_consts else []
        self.data_consts = data_consts if data_consts else []
        self.loop_vars = loop_vars if loop_vars else []
        self.ops = ops if ops else []
        self.n_loops = n_loops
        self.n_depth = n_depth
        self.n_stmts = n_stmts
        self.n_ops = n_ops
    def pprint(self):
        from pprint import PrettyPrinter
        pp = PrettyPrinter(indent=2)
        lines = []
        decl_pairs = [(decl.name, decl.n_dimensions) for decl in self.decls]
        lines.append(f'decls = {pp.pformat(decl_pairs)}')
        lines.append(f'mul_consts = {pp.pformat(self.mul_consts)}')
        lines.append(f'add_consts = {pp.pformat(self.add_consts)}')
        lines.append(f'data_consts = {pp.pformat(self.data_consts)}')
        lines.append(f'loop_vars = {pp.pformat(self.loop_vars)}')
        lines.append(f'n_loops = {self.n_loops}')
        lines.append(f'n_depth = {self.n_depth}')
        lines.append(f'n_stmts = {self.n_stmts}')
        lines.append(f'n_ops = {self.n_ops}')
        return '\n'.join(lines)

def generate(pattern_info):
    id_gen = IdGenerator()
    index_gen = IndexGenerator(pattern_info.mul_consts,
                               pattern_info.add_consts, id_gen.next_id)
    access_gen = AccessGenerator(pattern_info.decls,
                                 pattern_info.data_consts, index_gen,
                                 id_gen.next_id)
    op_gen = OpGenerator(pattern_info.ops, access_gen, id_gen.next_id)
    access_gen_lhs = AccessGenerator(pattern_info.decls, [],
                                     index_gen, id_gen.next_id)
    assign_gen = AssignmentGenerator(access_gen_lhs, op_gen,
                                     id_gen.next_id)
    loop_gen = LoopGenerator(assign_gen, id_gen.next_id)
    program_gen = ProgramGenerator(loop_gen, id_gen.next_id)
    node = program_gen.generate(pattern_info.n_loops,
                                pattern_info.n_depth,
                                pattern_info.loop_vars,
                                pattern_info.n_stmts,
                                pattern_info.n_ops)
    normalize_pattern(node, pattern_info.decls,
                      pattern_info.mul_consts,
                      pattern_info.add_consts,
                      pattern_info.data_consts,
                      pattern_info.loop_vars)
    return node, id_gen.current

# import os
# n_patterns = 10
# for pattern_id in range(n_patterns):
#     program = generate()
#     pattern_filename = f'p{pattern_id:04d}.pattern'
#     output_path = os.path.join(output_dir, pattern_filename)
#     with open(output_path, 'w') as f:
#         f.write(program.pprint())

# replace_map = {}
# for c in constants:
#     replace_map[c] = random.randint(0, 2)
# replacer = ConstReplacer(replace_map)
# program.replace(replacer)
# print(program.pprint())
