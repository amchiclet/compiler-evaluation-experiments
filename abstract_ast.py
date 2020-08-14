from loguru import logger

space_per_indent = 2

def get_precedence(op=None):
    if op in ['+', '-']:
        return 3
    elif op in ['*', '/']:
        return 4
    else:
        return 5

def is_list_syntactically_equal(list1, list2):
    if len(list1) != len(list2):
        return False
    for i1, i2 in zip(list1, list2):
        if not i1.is_syntactically_equal(i2):
            return False
    return True

class Replacer:
    def should_replace(self, node):
        raise NotImplementedError(type(self))
    def replace(self, node):
        raise NotImplementedError(type(self))

class Node:
    # clone the node including the node ids
    def clone(self):
        raise NotImplementedError(type(self))
    def is_syntactically_equal(self, other):
        raise NotImplementedError(type(self))
    def precedence(self):
        return get_precedence()
    def replace(self, replacer):
        raise NotImplementedError(type(self))

class Const(Node):
    def __init__(self, name, node_id=0):
        self.name = name
        self.node_id = node_id
        # self.surrounding_loop = None
    def cprint(self, var_map, indent=0):
        raise RuntimeError('This function should not be called')
    def pprint(self, indent=0):
        ws = space_per_indent * indent * ' '
        return f'{ws}const {self.name};'
    def clone(self):
        return Const(self.name, self.node_id)
    def is_syntactically_equal(self, other):
        return self.name == other.name
    def replace(self, replacer):
        self.name = replace(self.name, replacer)

class Declaration(Node):
    def __init__(self, name, n_dimensions, node_id=0):
        self.name = name
        self.n_dimensions = n_dimensions
        self.node_id = node_id
        # self.surrounding_loop = None
    def cprint(self, var_map, indent=0):
        raise RuntimeError('This function should not be called')
    def pprint(self, indent=0):
        ws = space_per_indent * indent * ' '
        return f'{ws}declare {self.name}{"[]"*self.n_dimensions};'
    def clone(self):
        return Declaration(self.name, self.n_dimensions, self.node_id)
    def is_syntactically_equal(self, other):
        return self.name == other.name and self.n_dimensions == other.n_dimensions
    def replace(self, replacer):
        self.name = replace(self.name, replacer)

class Literal(Node):
    def __init__(self, ty, val, node_id=0):
        self.ty = ty
        self.val = val
        self.node_id = node_id
    def cprint(self, var_map, indent=0):
        return f'{self.val}'
    def pprint(self, indent=0):
        return f'{self.val}'
    def clone(self):
        return Literal(self.ty, self.val, self.node_id)
    def is_syntactically_equal(self, other):
        return self.ty == other.ty and self.val == other.val
    def replace(self, replacer):
        self.ty = replace(self.ty, replacer)
        self.val = replace(self.val, replacer)
    def dep_print(self, refs):
        return f'{self.val}'

class Assignment(Node):
    def __init__(self, lhs, rhs, node_id=0):
        self.node_id = node_id
        self.lhs = lhs
        self.rhs = rhs
        self.surrounding_loop = None
        for access in get_accesses(self):
            access.parent_stmt = self
            for index in access.indices:
                index.parent_stmt = self
    def cprint(self, var_map, indent=0):
        ws = space_per_indent * indent * ' '
        return f'{ws}{self.lhs.cprint(var_map)} = {self.rhs.cprint(var_map)};'

    def pprint(self, indent=0):
        ws = space_per_indent * indent * ' '
        return f'{ws}{self.lhs.pprint()} = {self.rhs.pprint()};'
    def dep_print(self, refs):
        return f'{self.lhs.dep_print(refs)} = {self.rhs.dep_print(refs)};'
    def clone(self):
        cloned = Assignment(self.lhs.clone(), self.rhs.clone(), self.node_id)
        return cloned
    def is_syntactically_equal(self, other):
        return self.lhs.is_syntactically_equal(other.lhs) and \
            self.rhs.is_syntactically_equal(other.rhs)
    def replace(self, replacer):
        self.lhs, self.rhs = replace_each([self.lhs, self.rhs], replacer)
        for access in get_accesses(self):
            access.parent_stmt = self
            for index in access.indices:
                index.parent_stmt = self

def replace(i, replacer):
    if replacer.should_replace(i):
        return replacer.replace(i)
    else:
        if isinstance(i, Node):
            i.replace(replacer)
        return i

def replace_each(l, replacer):
    return [replace(i, replacer) for i in l]

from termcolor import colored

class Access(Node):
    def __init__(self, var, indices=None, node_id=0):
        self.node_id = node_id
        self.var = var
        self.indices = indices if indices else []
        # for dimension, index in enumerate(self.indices):
        #     index.array = var
        #     index.dimension = dimension
        self.is_write = False
        self.parent_stmt = None
    def is_scalar(self):
        return len(self.indices) == 0
    def cprint(self, var_map, indent=0):
        list_of_pprint = [f'[{index.cprint(var_map)}]' for index in self.indices]
        return f'{self.var}{"".join(list_of_pprint)}'

    def pprint(self, indent=0):
        list_of_pprint = [f'[{index.pprint()}]' for index in self.indices]
        return f'{self.var}{"".join(list_of_pprint)}'
    def dep_print(self, refs):
        if self in refs:
            return colored(f'{self.pprint()}', 'green')
        else:
            return self.pprint()
    def clone(self):
        cloned_indices = [i.clone() for i in self.indices]
        cloned = Access(self.var, cloned_indices, self.node_id)
        cloned.is_write = self.is_write
        return cloned
    def is_syntactically_equal(self, other):
        return self.var == other.var and \
            is_list_syntactically_equal(self.indices, other.indices)
    def replace(self, replacer):
        self.var = replace(self.var, replacer)
        self.indices = replace_each(self.indices, replacer)

class LoopShapeBuilder:
    def __init__(self):
        self.loop_var = None
        self.greater_eq = None
        self.less_eq = None
        self.step = None
    def set_shape_part(self, expr, prefix=None):
        if prefix is None:
            self.loop_var = expr
        elif prefix == '>=':
            self.greater_eq = expr
        elif prefix == '<=':
            self.less_eq = expr
        elif prefix == '+=':
            self.step = expr
        else:
            raise RuntimeError(f'Unsupported prefix ({prefix})')
    def merge(self, other):
        if other.loop_var is not None:
            assert(self.loop_var is None)
            self.loop_var = other.loop_var
        if other.less_eq is not None:
            assert(self.less_eq is None)
            self.less_eq = other.less_eq
        if other.greater_eq is not None:
            assert(self.greater_eq is None)
            self.greater_eq = other.greater_eq
        if other.step is not None:
            assert(self.step is None)
            self.step = other.step
    def build(self, default_greater_eq, default_less_eq, default_step, node_id):
        assert(self.loop_var is not None)
        loop_var = self.loop_var
        greater_eq = self.greater_eq if self.greater_eq is not None else default_greater_eq
        less_eq = self.less_eq if self.less_eq is not None else default_less_eq
        step = self.step if self.step is not None else default_step
        return LoopShape(loop_var, greater_eq, less_eq, step, node_id)

class LoopShape(Node):
    def __init__(self, loop_var, greater_eq, less_eq, step, node_id=0):
        self.node_id = node_id
        self.loop_var = loop_var
        self.greater_eq = greater_eq
        self.less_eq = less_eq
        self.step = step
    def clone(self):
        return LoopShape(self.loop_var.clone(),
                         self.greater_eq.clone(),
                         self.less_eq.clone(),
                         self.step.clone(),
                         self.node_id)
    def pprint(self):
        return ('('
                f'{self.loop_var.pprint()}, '
                f'>={self.greater_eq.pprint()}, '
                f'<={self.less_eq.pprint()}, '
                f'+={self.step.pprint()}'
                ')')

    def is_syntactically_equal(self, other):
        return all(self.loop_var.is_syntactically_equal(other.loop_var),
                   self.greater_eq.is_syntactically_equal(other.greater_eq),
                   self.less_eq.is_syntactically_equal(other.less_eq),
                   self.step.is_syntactically_equal(other.step))
    def replace(self, replacer):
        self.loop_var = replace(self.loop_var, replacer)
        self.greater_eq = replace(self.greater_eq, replacer)
        self.less_eq = replace(self.less_eq, replacer)
        self.step = replace(self.step, replacer)

class AbstractLoop(Node):
    def __init__(self, loop_shapes, body, node_id=0):
        self.node_id = node_id
        self.loop_shapes = loop_shapes
        self.body = body
        self.surrounding_loop = None
        for stmt in body:
            stmt.surrounding_loop = self

        # To be used for strip mining
        self.partial_loop_order = []

    def cprint_recursive(self, depth, var_map, indent=0):
        if depth == len(self.loop_shapes):
            lines = []
            for stmt in self.body:
                lines.append(stmt.cprint(var_map, indent+1))
            return '\n'.join(lines)

        ws = '  ' * indent
        loop_shape = self.loop_shapes[depth]
        loop_var = loop_shape.loop_var
        begin = var_map.get_min(loop_var)
        end = var_map.get_max(loop_var)
        lines = [(f'{ws}for (int {loop_var} = {begin}; '
                  f'{loop_var} <= {end}; '
                  f'{loop_var}+=1) {{')]
        lines.append(self.cprint_recursive(depth+1, var_map, indent+1))
        lines.append(f'{ws}}}')
        return '\n'.join(lines)

    def cprint(self, var_map, indent=0):
        return self.cprint_recursive(0, var_map, indent)

    def pprint(self, indent=0):
        ws = space_per_indent * indent * ' '
        loop_vars = []
        # for shape in self.loop_shapes:
        #     assert(type(shape.loop_var) == Access)
        #     loop_vars.append(shape.loop_var.var)
        shapes = [shape.pprint() for shape in self.loop_shapes]
        header = f'{ws}for [{", ".join(shapes)}] {{'
        body = [f'{stmt.pprint(indent+1)}' for stmt in self.body]
        end = f'{ws}}}'
        return '\n'.join([header] + body + [end])
    def clone(self):
        cloned_loop_shapes = [shape.clone() for shape in self.loop_shapes]
        cloned_body = [stmt.clone() for stmt in self.body]
        cloned_loop = AbstractLoop(cloned_loop_shapes, cloned_body, self.node_id)
        return cloned_loop
    def is_syntactically_equal(self, other):
        return all(is_list_syntactically_equal(self.loop_shapes, other.loop_shapes),
                   is_list_syntactically_equal(self.body, other.body))
    def replace(self, replacer):
        self.loop_shapes = replace_each(self.loop_shapes, replacer)
        self.body = replace_each(self.body, replacer)
        for stmt in self.body:
            stmt.surrounding_loop = self

class Op(Node):
    def __init__(self, op, args, node_id=0):
        self.op = op
        self.args = args
        self.node_id = 0
    def precedence(self):
        if len(self.args) == 1:
            return 100
        if self.op in ['*', '/']:
            return 99
        if self.op in ['+', '-']:
            return 98
        if self.op in ['<', '>', '<=', '>=']:
            return 97
        if self.op in ['==', '!=']:
            return 96
        if self.op == '&&':
            return 95
        if self.op == '||':
            return 94
        if self.op == '?:':
            return 93
        raise RuntimeError(f'Unsupported op {self.op}')
    def generic_print(self, formatter):
        args = []
        for arg in self.args:
            arg_str = formatter(arg)
            is_atom = type(arg) in [Access, Literal]
            if not is_atom and self.precedence() >= arg.precedence():
                arg_str = f'({arg_str})'
            args.append(arg_str)
        if len(args) == 1:
            return f'{self.op}{args[0]}'
        elif len(args) == 2:
            return f'{args[0]} {self.op} {args[1]}'
        elif len(args) == 3:
            assert(self.op == '?:')
            return f'{args[0]} ? {args[1]} : {args[2]}'
        raise RuntimeError('Unsuppored argument length: {args}')

    def pprint(self, indent=0):
        def formatter(arg):
            return arg.pprint(indent)
        return self.generic_print(formatter)

    # TODO: refactor pprint and cprint
    def cprint(self, var_map, indent=0):
        def formatter(arg):
            return arg.cprint(var_map, indent)
        return self.generic_print(formatter)
    def dep_print(self, refs):
        def formatter(arg):
            return arg.dep_print(refs)
        return self.generic_print(formatter)
    def clone(self):
        cloned_args = [arg.clone() for arg in self.args]
        return Op(self.op, cloned_args, self.node_id)
    def is_syntactically_equal(self, other):
        if self.op != other.op:
            return False
        if len(self.args) != len(other.args):
            return False
        for arg, other_arg in zip(self.args, other.args):
            if not arg.is_syntactically_equal(other_arg):
                return False
        return True
    def replace(self, replacer):
        self.args = replace_each(self.args, replacer)

class Program:
    def __init__(self, decls, body, consts, node_id=0):
        self.node_id = node_id
        self.decls = decls
        self.body = body
        self.consts = consts

        # These fields are defined so dependence analysis
        # can proceed in a uniform way with loops
        self.surrounding_loop = None
        self.loop_shapes = []
        for stmt in body:
            stmt.surrounding_loop = self

    def cprint(self, var_map, indent=0):
        lines = []
        for stmt in self.body:
            lines.append(stmt.cprint(var_map, indent))
        return '\n'.join(lines)

    def pprint(self, indent=0):
        body = []
        body += [f'{decl.pprint(indent)}' for decl in self.decls]
        body += [f'{const.pprint(indent)}' for const in self.consts]
        body += [f'{stmt.pprint(indent)}' for stmt in self.body]
        return '\n'.join(body)
    def clone(self):
        cloned_decls = [decl.clone() for decl in self.decls]
        cloned_body = [stmt.clone() for stmt in self.body]
        cloned_consts = [const.clone() for const in self.consts]
        return Program(cloned_decls, cloned_body, cloned_consts, self.node_id)
    def is_syntactically_equal(self, other):
        return is_list_syntactically_equal(self.decls, other.decls) and \
            is_list_syntactically_equal(self.body, other.body) and \
            is_list_syntactically_equal(self.consts, other.consts)
    def merge(self, other):
        cloned = other.clone()

        consts = set()
        for const in self.consts:
            consts.add(const.name)

        var_shapes = {}
        for decl in self.decls:
            var_shapes[decl.name] = decl.n_dimensions
        # check array shapes match
        for decl in cloned.decls:
            if decl.name in var_shapes:
                if decl.n_dimensions != var_shapes[decl.name]:
                    return
        # merge declarations
        for decl in cloned.decls:
            if decl.name not in var_shapes:
                self.decls.append(decl)
        # merge constants
        for const in cloned.consts:
            if const.name not in consts:
                self.consts.append(const)
        # merge body
        self.body += cloned.body
        for stmt in cloned.body:
            stmt.surrounding_loop = self
    def replace(self, replacer):
        self.decls = replace_each(self.decls, replacer)
        self.consts = replace_each(self.consts, replacer)
        self.loop_shapes = replace_each(self.loop_shapes, replacer)
        self.body = replace_each(self.body, replacer)
        for stmt in self.body:
            stmt.surrounding_loop = self

def get_accesses(node):
    accesses = set()
    if isinstance(node, Assignment):
        accesses.update(get_accesses(node.lhs))
        accesses.update(get_accesses(node.rhs))
        return accesses
    elif isinstance(node, Access):
        accesses.add(node)
        return accesses
    elif isinstance(node, Op):
        for arg in node.args:
            accesses.update(get_accesses(arg))
        return accesses
    elif isinstance(node, AbstractLoop):
        for shape in node.loop_shapes:
            accesses.update(get_accesses(shape.loop_var))
            accesses.update(get_accesses(shape.greater_eq))
            accesses.update(get_accesses(shape.less_eq))
            accesses.update(get_accesses(shape.step))
        for stmt in node.body:
            accesses.update(get_accesses(stmt))
        return accesses
    elif isinstance(node, Program):
        for stmt in node.body:
            accesses.update(get_accesses(stmt))
        return accesses
    elif isinstance(node, Literal):
        return accesses
    else:
        raise RuntimeError('Unhandled type of node ' + str(type(node)))

def get_loops(node):
    if isinstance(node, AbstractLoop):
        loops = {node.node_id:node}
        for stmt in node.body:
            loops.update(get_loops(stmt))
        return loops
    elif isinstance(node, Program):
        loops = {}
        for stmt in node.body:
            loops.update(get_loops(stmt))
        return loops
    elif isinstance(node, Assignment):
        return {}
    else:
        raise RuntimeError('get_loops: Unhandled type of node ' + str(type(node)))

# returns a map from array name to the number of dimensions for that array
def get_arrays(program):
    arrays = {}
    for access in get_accesses(program):
        array_name = access.var
        n_dimensions = len(access.indices)
        if not array_name in arrays:
            arrays[array_name] = n_dimensions
        else:
            assert(arrays[array_name] == n_dimensions)
    return arrays

class ConstReplacer(Replacer):
    def __init__(self, replace_map):
        self.replace_map = replace_map
    def should_replace(self, node):
        return type(node) == Access and node.var in self.replace_map
    def replace(self, node):
        return Literal(int, self.replace_map[node.var], node.node_id)

class VarRenamer(Replacer):
    def __init__(self, replace_map):
        self.replace_map = replace_map
    def should_replace(self, node):
        return type(node) == str and node in self.replace_map
    def replace(self, node):
        return self.replace_map[node]
