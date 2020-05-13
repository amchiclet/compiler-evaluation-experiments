from lark import Lark, Transformer

grammar = '''
    start: declaration+ abstract_loop+

    declaration: "declare" array ("[" size "]")* ";"
    size: affine_index
    abstract_loop: "for" "[" loop_vars "]" "{" statement+ "}"
    loop_vars: scalar ("," scalar)*

    statement: assignment
    assignment: access "=" expr ";"

    expr: binop | access
    binop: expr BIN_OP expr

    access: scalar_access | array_access
    scalar_access: scalar
    array_access: array ("[" index "]")+
    index: abstract_index | affine_index
    abstract_index: greater_than | less_than
    greater_than: ">" index
    less_than: "<" index
    affine_index: simple_affine | var | linear | constant | offset
    simple_affine: INT "*" scalar AFFINE_OP INT
    linear: INT "*" scalar
    constant: INT
    var: scalar
    offset: scalar AFFINE_OP INT

    scalar: CNAME
    array: UCASE_LETTER+
    AFFINE_OP: "+" | "-"
    BIN_OP: "*" | "+" | "-"
    %import common.WS
    %import common.LCASE_LETTER
    %import common.UCASE_LETTER
    %import common.CNAME
    %import common.INT
    %ignore WS

'''

from abstract_ast import Assignment, AbstractIndex, Access, AbstractLoop, BinOp, Program, get_accesses, AffineIndex, Declaration

class TreeSimplifier(Transformer):
    def __init__(self, start_node_id=0):
        self.current_node_id = start_node_id
    def next_node_id(self):
        self.current_node_id += 1
        return self.current_node_id
    def declaration(self, args):
        return Declaration(args[0], args[1:])
    def size(self, args):
        return args[0]
    def array(self, args):
        return ''.join(args)
    def scalar(self, args):
        return ''.join(args)
    def index(self, args):
        return args[0]
    def affine_index(self, args):
        return args[0]
    def constant(self, args):
        return AffineIndex(None, 0, int(args[0]))
    def offset(self, args):
        var = args[0]
        offset = int(args[2]) if args[1] == '+' else -int(args[2])
        return AffineIndex(var, 1, offset)
    def var(self, args):
        return AffineIndex(args[0], 1, 0)
    def linear(self, args):
        var = args[1]
        coeff = int(args[0])
        return AffineIndex(var, coeff, 0)
    def simple_affine(self, args):
        coeff = int(args[0])
        var = args[1]
        offset = int(args[3]) if args[2] == '+' else -int(args[3])
        return AffineIndex(var, coeff, offset)
    def abstract_index(self, args):
        if isinstance(args[0], AbstractIndex):
            return args[0]
        else:
            return AbstractIndex(args[0], 0, self.next_node_id())
    def greater_than(self, args):
        index = args[0]
        return AbstractIndex(index.var, index.relationship + 1, self.next_node_id())
    def less_than(self, args):
        index = args[0]
        return AbstractIndex(index.var, index.relationship - 1, self.next_node_id())
    def scalar_access(self, args):
        return Access(args[0], self.next_node_id())
    def array_access(self, args):
        return Access(args[0], args[1:], self.next_node_id())
    def access(self, args):
        return args[0]
    def binop(self, args):
        return BinOp(args[1], args[0], args[2], self.next_node_id())
    def expr(self, args):
        return args[0]
    def assignment(self, args):
        lhs = args[0]
        assert(isinstance(lhs, Access))
        lhs.is_write = True
        return Assignment(lhs, args[1], self.next_node_id())
    def statement(self, args):
        stmt = args[0]
        for access in get_accesses(stmt):
            access.parent_stmt = stmt
            for index in access.indices:
                index.parent_stmt = stmt
        return stmt
    def loop_vars(self, args):
        return args
    def abstract_loop(self, args):
        loop_vars = args[0]
        body = args[1:]
        loop = AbstractLoop(loop_vars, body, self.next_node_id())
        for stmt in body:
            assert(isinstance(stmt, Assignment))
            stmt.surrounding_loop = loop
        return loop
    def start(self, args):
        decls = []
        loops = []
        for arg in args:
            if type(arg) == Declaration:
                decls.append(arg)
            elif type(arg) == AbstractLoop:
                loops.append(arg)
            else:
                raise RuntimeError('Unsupported syntax in main program')
        if len(loops) > 1:
            raise RuntimeError('Only single loops are supported now.')
        return Program(decls, loops, self.next_node_id())

def parse_str(code):
    parser = Lark(grammar)
    lark_ast = parser.parse(code)
    tree_simplifier = TreeSimplifier()
    abstract_ast = tree_simplifier.transform(lark_ast)
    return abstract_ast, tree_simplifier.next_node_id()

def parse_file(path):
    with open(path) as f:
        return parse_str(f.read())

# TODO write dependence analysis to get dependence matrix
