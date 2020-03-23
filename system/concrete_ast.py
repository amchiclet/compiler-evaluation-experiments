from abstract_ast import Node, Assignment, Access, AbstractLoop, BinOp, Program

class CNode(Node):
    pass

class CAssignment(Assignment):
    def clone(self):
        cloned = CAssignment(self.lhs.clone(), self.rhs.clone(), self.node_id)
        for access in get_accesses(cloned):
            access.parent_stmt = cloned
        return cloned

class CLiteral(CNode):
    def __init__(self, lit, node_id=0):
        self.lit = lit
    def clone(self):
        return CLiteral(self.lit, self.node_id)
    def pprint(self, indent=0):
        return f'{self.lit}'

class CScalar(CNode):
    def __init__(self, var, node_id=0):
        self.var = var
    def clone(self):
        return CScalar(self.var, self.node_id)
    def pprint(self, indent=0):
        return f'{self.var}'

class CAccess(Access):
    def clone(self):
        cloned_indices = [i.clone() for i in self.indices]
        cloned = CAccess(self.var, cloned_indices, self.node_id)
        cloned.is_write = self.is_write
        return cloned

class CLoop(AbstractLoop):
    def clone(self):
        cloned_loop_vars = list(self.loop_vars)
        cloned_body = [stmt.clone() for stmt in self.body]
        cloned_loop = CLoop(cloned_loop_vars, cloned_body, self.node_id)
        for stmt in cloned_body:
            stmt.surrounding_loop = cloned_loop
        return cloned_loop

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

class CProgram(Program):
    def clone(self):
        cloned_loops = [loop.clone() for loop in self.loops]
        return CProgram(cloned_loops, self.node_id)

def rename(node):
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
    else:
        raise RuntimeError('Unhandled type of node ' + str(type(node)))
