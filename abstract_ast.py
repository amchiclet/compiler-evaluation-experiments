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
    # def cprint(self, var_map, indent=0):
    #     pass
    def clone(self):
        return Declaration(self.name, self.node_id)
    def is_syntactically_equal(self, other):
        return self.name == other.name

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
    # def cprint(self, var_map, indent=0):
    #     pass
    def clone(self):
        return Declaration(self.name, self.n_dimensions, self.node_id)
    def is_syntactically_equal(self, other):
        return self.name == other.name and self.n_dimensions == other.n_dimensions

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
        pass
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
        i.replace(replacer)
        return i

def replace_each(l, replacer):
    return [replace(i, replacer) for i in l]

class AffineIndex(Node):
    def __init__(self, var, coeff, offset, node_id=0):
        self.node_id = node_id
        self.var = var
        self.coeff = coeff
        self.offset = offset
        self.array = None
        self.dimension = None
        self.parent_stmt = None
    def cprint(self, var_map, indent=0):
        if self.var:
            linear = f'{self.var}' if self.coeff == 1 else f'{self.coeff}*{self.var}'
            if self.offset > 0:
                return f'{linear}+{self.offset}'
            elif self.offset < 0:
                return f'{linear}{self.offset}'
            else:
                return f'{linear}'
        else:
            return f'{self.offset}'

    def pprint(self, indent=0):
        if self.var:
            linear = f'{self.var}' if self.coeff == 1 else f'{self.coeff}*{self.var}'
            if self.offset > 0:
                return f'{linear}+{self.offset}'
            elif self.offset < 0:
                return f'{linear}{self.offset}'
            else:
                return f'{linear}'
        else:
            return f'{self.offset}'
    def clone(self):
        cloned = AffineIndex(self.var, self.coeff, self.offset, self.node_id)
        cloned.array = self.array
        cloned.dimension = self.dimension
        return cloned
    def is_syntactically_equal(self, other):
        return self.var == other.var and \
            self.coeff == other.coeff and \
            self.offset == other.offset

# TODO: create expr class
from termcolor import colored

class Access(Node):
    def __init__(self, var, indices=None, node_id=0):
        self.node_id = node_id
        self.var = var
        self.indices = indices if indices else []
        for dimension, index in enumerate(self.indices):
            index.array = var
            index.dimension = dimension
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
        for dimension, index in enumerate(cloned_indices):
            index.array = self.var
            index.dimension = dimension
        cloned.is_write = self.is_write
        return cloned
    def is_syntactically_equal(self, other):
        return self.var == other.var and \
            is_list_syntactically_equal(self.indices, other.indices)
    def replace(self, replacer):
        pass

class AbstractLoop(Node):
    def __init__(self, loop_vars, body, node_id=0):
        self.node_id = node_id
        self.loop_vars = loop_vars
        self.body = body
        self.surrounding_loop = None
        for stmt in body:
            stmt.surrounding_loop = self

        # To be used for strip mining
        self.partial_loop_order = []

    def cprint_recursive(self, depth, var_map, indent=0):
        if depth == len(self.loop_vars):
            lines = []
            for stmt in self.body:
                lines.append(stmt.cprint(var_map, indent+1))
            return '\n'.join(lines)

        ws = '  ' * indent
        loop_var = self.loop_vars[depth]
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
        header = f'{ws}for [{", ".join(self.loop_vars)}] {{'
        body = [f'{stmt.pprint(indent+1)}' for stmt in self.body]
        end = f'{ws}}}'
        return '\n'.join([header] + body + [end])
    def clone(self):
        cloned_loop_vars = list(self.loop_vars)
        cloned_body = [stmt.clone() for stmt in self.body]
        cloned_loop = AbstractLoop(cloned_loop_vars, cloned_body, self.node_id)
        return cloned_loop
    def is_syntactically_equal(self, other):
        if self.loop_vars != other.loop_vars:
            return False
        return is_list_syntactically_equal(self.body, other.body)
    def replace(self, replacer):
        self.body = replace_each(self.body, replacer)
        for stmt in self.body:
            stmt.surrounding_loop = self

class BinOp(Node):
    def __init__(self, op, left, right, node_id=0):
        self.node_id = node_id
        self.op = op
        self.left = left
        self.right = right
    def cprint(self, var_map, indent=0):
        return f'{self.left.cprint(var_map)} {self.op} {self.right.cprint(var_map)}'
    def pprint(self, indent=0):
        left_str = self.left.pprint()
        if self.precedence() >= self.left.precedence():
            left_str = f'({left_str})'
        right_str = self.right.pprint()
        if self.precedence() >= self.right.precedence():
            right_str = f'({right_str})'
        return f'{left_str} {self.op} {right_str}'
    def dep_print(self, refs):
        return f'{self.left.dep_print(refs)} {self.op} {self.right.dep_print(refs)}'
    def clone(self):
        return BinOp(self.op, self.left.clone(), self.right.clone(), self.node_id)
    def is_syntactically_equal(self, other):
        return self.left.op == self.right.op and \
            self.left.is_syntactically_equal(other.left) and \
            self.right.is_syntactically_equal(other.right)
    def precedence(self):
        return get_precedence(self.op)
    def replace(self, replacer):
        self.left, self.right = replace_each([self.left, self.right], replacer)

class Program:
    def __init__(self, decls, loops, consts, node_id=0):
        self.node_id = node_id
        self.decls = decls
        self.loops = loops
        self.consts = consts
        self.surrounding_loop = None
        self.loop_vars = []
        for loop in loops:
            loop.surrounding_loop = self

    def cprint(self, var_map, indent=0):
        lines = []
        for loop in self.loops:
            lines.append(loop.cprint(var_map, indent))
        return '\n'.join(lines)

    def pprint(self, indent=0):
        body = []
        body += [f'{decl.pprint(indent)}' for decl in self.decls]
        body += [f'{const.pprint(indent)}' for const in self.consts]
        body += [f'{loop.pprint(indent)}' for loop in self.loops]
        return '\n'.join(body)
    def clone(self):
        cloned_decls = [decl.clone() for decl in self.decls]
        cloned_loops = [loop.clone() for loop in self.loops]
        cloned_consts = [const.clone() for const in self.consts]
        return Program(cloned_decls, cloned_loops, cloned_consts, self.node_id)
    def is_syntactically_equal(self, other):
        return is_list_syntactically_equal(self.decls, other.decls) and \
            is_list_syntactically_equal(self.loops, other.loops) and \
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
                    print('Cannot use this program')
                    return
        # merge declarations
        for decl in cloned.decls:
            if decl.name not in var_shapes:
                self.decls.append(decl)
        # merge constants
        for const in cloned.consts:
            if const.name not in consts:
                self.consts.append(const)
        # merge loops
        self.loops += cloned.loops
        for loop in cloned.loops:
            loop.surrounding_loop = self
    def replace(self, replacer):
        self.loops = replace_each(self.loops, replacer)
        for loop in self.loops:
            loop.surrounding_loop = self

def get_accesses(node):
    accesses = set()
    if isinstance(node, Assignment):
        accesses.update(get_accesses(node.lhs))
        accesses.update(get_accesses(node.rhs))
        return accesses
    elif isinstance(node, Access):
        accesses.add(node)
        return accesses
    elif isinstance(node, BinOp):
        accesses.update(get_accesses(node.left))
        accesses.update(get_accesses(node.right))
        return accesses
    elif isinstance(node, AbstractLoop):
        for stmt in node.body:
            accesses.update(get_accesses(stmt))
        return accesses
    elif isinstance(node, Program):
        for loop in node.loops:
            accesses.update(get_accesses(loop))
        return accesses
    elif isinstance(node, Literal):
        return accesses
    else:
        print(node)
        raise RuntimeError('Unhandled type of node ' + str(type(node)))

def get_loops(node):
    if isinstance(node, AbstractLoop):
        loops = {node.node_id:node}
        for stmt in node.body:
            loops.update(get_loops(stmt))
        return loops
    elif isinstance(node, Program):
        loops = {}
        for loop in node.loops:
            loops.update(get_loops(loop))
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
    
# gather array dimensions and loop accesses
def get_program_info(program):
    # maps array name to [loop var name]
    arrays = {}
    # maps loop var name to (lower, upper)
    loop_vars = {}
    for access in get_accesses(program):
        array_name = access.var
        n_dimensions = len(access.indices)
        if n_dimensions == 0:
            continue
        if not array_name in arrays:
            arrays[array_name] = [None] * n_dimensions
        for i, abstract_index in enumerate(access.indices):
            loop_var = abstract_index.var

            # update arrays
            if not arrays[array_name][i]:
                arrays[array_name][i] = loop_var
            else:
                assert(arrays[array_name][i] == loop_var)

            # update loop_vars
            if not loop_var in loop_vars:
                loop_vars[loop_var] = [0, 0]
            loop_vars[loop_var][0] = min(loop_vars[loop_var][0],
                                         abstract_index.relationship)
            loop_vars[loop_var][1] = max(loop_vars[loop_var][1],
                                         abstract_index.relationship)
    return arrays, loop_vars

def is_same_memory(access1, access2):
    return access1.var == access2.var

def is_in_same_loop(stmt1, stmt2):
    return stmt1.surrounding_loop.node_id == stmt2.surrounding_loop.node_id

def all_pairs(s):
    l = list(s)
    for index, e1 in enumerate(l[:-1]):
        for e2 in l[index+1:]:
            yield (e1, e2)

def get_all_access_pairs(node):
    return all_pairs(get_accesses(node))

