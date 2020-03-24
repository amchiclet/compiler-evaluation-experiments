from abstract_ast import Node, Assignment, Access, AbstractLoop, BinOp, Program

def get_accesses(node):
    accesses = set()
    if isinstance(node, CAssignment):
        accesses.update(get_accesses(node.lhs))
        accesses.update(get_accesses(node.rhs))
        return accesses
    elif isinstance(node, CAccess):
        accesses.add(node)
        return accesses
    elif isinstance(node, CBinOp):
        accesses.update(get_accesses(node.left))
        accesses.update(get_accesses(node.right))
        return accesses
    elif isinstance(node, CLoop):
        for stmt in node.body:
            accesses.update(get_accesses(stmt))
        return accesses
    elif isinstance(node, CProgram):
        for loop in node.loops:
            accesses.update(get_accesses(loop))
        return accesses
    else:
        raise RuntimeError('Unhandled type of node ' + str(type(node)))

class CNode(Node):
    pass

class CAssignment(Assignment):
    def clone(self):
        cloned = CAssignment(self.lhs.clone(), self.rhs.clone(), self.node_id)
        for access in get_accesses(cloned):
            access.parent_stmt = cloned
        return cloned
    def rename(self, rename_map):
        return self.lhs.rename(rename_map) or self.rhs.rename(rename_map)

class CLiteral(CNode):
    def __init__(self, lit, node_id=0):
        self.lit = lit
        self.node_id = node_id
    def clone(self):
        return CLiteral(self.lit, self.node_id)
    def pprint(self, indent=0):
        return f'{self.lit}'
    def rename(self, rename_map):
        return False

class CScalar(CNode):
    def __init__(self, var, node_id=0):
        self.var = var
        self.node_id = node_id
    def clone(self):
        return CScalar(self.var, self.node_id)
    def pprint(self, indent=0):
        return f'{self.var}'
    def rename(self, rename_map):
        if self.var in rename_map:
            self.var = rename_map[self.var]
            return True
        return False

class CAccess(Access):
    def clone(self):
        cloned_indices = [i.clone() for i in self.indices]
        cloned = CAccess(self.var, cloned_indices, self.node_id)
        cloned.is_write = self.is_write
        return cloned
    def rename(self, rename_map):
        if self.var in rename_map:
            self.var = rename_map[self.var]
        # loop variables are not expected to be renamed
        # assuming only loop variables can appear in indices, then we should throw an error
        # if we see them throw an error
        for i in self.indices:
            if i.rename(rename_map):
                raise RuntimeError('Array indices are not expected to be renamed')

class CLoop(AbstractLoop):
    def clone(self):
        cloned_loop_vars = list(self.loop_vars)
        cloned_body = [stmt.clone() for stmt in self.body]
        cloned_loop = CLoop(cloned_loop_vars, cloned_body, self.node_id)
        for stmt in cloned_body:
            stmt.surrounding_loop = cloned_loop
        return cloned_loop
    def rename(self, rename_map):
        # if loop variable name clashes just throw an error
        for rename_var in rename_map:
            if rename_var in self.loop_vars:
                raise RuntimeError(f'Trying to rename {rename_var} which is a loop variable')
        renamed = False
        for stmt in self.body:
            if stmt.rename(rename_map):
                renamed = True
        return renamed

class CBinOp(BinOp):
    def __init__(self, op, left, right, node_id=0):
        self.left = left
        self.right = right
        self.node_id = node_id
        self.op = op
    def clone(self):
        return CBinOp(self.op, self.left.clone(), self.right.clone(), self.node_id)
    def pprint(self, indent=0):
        return f'{self.left.pprint()} {self.op} {self.right.pprint()}'
    def rename(self, rename_map):
        return self.left.rename(rename_map) or self.right.rename(rename_map)

class CProgram(Program):
    def clone(self):
        cloned_loops = [loop.clone() for loop in self.loops]
        return CProgram(cloned_loops, self.node_id)
    def rename(self, rename_map):
        renamed = False
        for loop in self.loops:
            if loop.rename(rename_map):
                renamed = True
        return renamed
