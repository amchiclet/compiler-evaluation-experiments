from lark import Lark, Transformer

grammar = '''
    start: (declaration | const)+ statement+

    declaration: "declare" array (dimension)* ";"
    const: "const" scalar ";"
    dimension: "[" "]"
    size: affine_index
    abstract_loop: "for" "[" loop_vars "]" "{" statement+ "}"
    loop_vars: scalar ("," scalar)*

    statement: assignment | abstract_loop
    assignment: access "=" expr ";"

    expr: expr ADDSUB term | term
    term: term MULDIV factor | factor
    factor: access | "(" expr ")" | "-" factor
    binop: expr BIN_OP expr

    access: scalar_access | array_access | literal
    scalar_access: scalar
    array_access: array ("[" expr "]")+
    literal: float_literal | int_literal
    float_literal: FLOAT
    int_literal: INT

    index: affine_index
    affine_index: simple_affine | var | linear | constant | offset
    simple_affine: INT "*" scalar AFFINE_OP INT
    linear: INT "*" scalar
    constant: INT
    var: scalar
    single: scalar | INT
    offset: scalar AFFINE_OP INT

    scalar: CNAME
    array: CNAME
    AFFINE_OP: "+" | "-"
    BIN_OP: "*" | "+" | "-"
    ADDSUB: "+" | "-"
    MULDIV: "*" | "/"
    %import common.WS
    %import common.LCASE_LETTER
    %import common.UCASE_LETTER
    %import common.CNAME
    %import common.INT
    %import common.FLOAT
    %ignore WS

'''

from abstract_ast import Assignment, Access, AbstractLoop, BinOp, Program, get_accesses, AffineIndex, Declaration, Const, Literal
from loguru import logger

class TreeSimplifier(Transformer):
    def __init__(self, start_node_id=0):
        self.current_node_id = start_node_id
    def next_node_id(self):
        self.current_node_id += 1
        return self.current_node_id
    def declaration(self, args):
        n_dimensions = len(args) - 1
        return Declaration(args[0], n_dimensions, self.next_node_id())
    def size(self, args):
        return args[0]
    def array(self, args):
        return ''.join(args)
    def const(self, args):
        return Const(args[0], self.next_node_id())
    def scalar(self, args):
        return ''.join(args)
    def index(self, args):
        return args[0]
    def affine_index(self, args):
        return args[0]
    def constant(self, args):
        return AffineIndex(None, 0, int(args[0]), self.next_node_id())
    def offset(self, args):
        var = args[0]
        offset = int(args[2]) if args[1] == '+' else -int(args[2])
        return AffineIndex(var, 1, offset, self.next_node_id())
    def var(self, args):
        return AffineIndex(args[0], 1, 0, self.next_node_id())
    def linear(self, args):
        var = args[1]
        coeff = int(args[0])
        return AffineIndex(var, coeff, 0, self.next_node_id())
    def simple_affine(self, args):
        coeff = int(args[0])
        var = args[1]
        offset = int(args[3]) if args[2] == '+' else -int(args[3])
        return AffineIndex(var, coeff, offset, self.next_node_id())
    # literal: float_literal | int_literal
    # float_literal: FLOAT
    # int_literal: INT
    def literal(self, args):
        return args[0]
    def float_literal(self, args):
        return Literal(float, float(args[0]), self.next_node_id())
    def int_literal(self, args):
        return Literal(int, int(args[0]), self.next_node_id())
    def scalar_access(self, args):
        logger.info(args)
        return Access(args[0], node_id=self.next_node_id())
    def array_access(self, args):
        return Access(args[0], args[1:], self.next_node_id())
    def access(self, args):
        return args[0]
    def binop(self, args):
        return BinOp(args[1], args[0], args[2], self.next_node_id())
    def expr(self, args):
        if len(args) == 3:
            return BinOp(args[1], args[0], args[2], self.next_node_id())
        else:
            return args[0]
    def term(self, args):
        if len(args) == 3:
            return BinOp(args[1], args[0], args[2], self.next_node_id())
        else:
            return args[0]
    def factor(self, args):
        return args[0]
    def assignment(self, args):
        lhs = args[0]
        assert(isinstance(lhs, Access))
        lhs.is_write = True
        return Assignment(lhs, args[1], self.next_node_id())
    def statement(self, args):
        stmt = args[0]
        return stmt
    def loop_vars(self, args):
        return args
    def abstract_loop(self, args):
        loop_vars = args[0]
        body = args[1:]
        loop = AbstractLoop(loop_vars, body, self.next_node_id())
        return loop
    def start(self, args):
        decls = []
        loops = []
        consts = []
        for arg in args:
            if type(arg) == Declaration:
                decls.append(arg)
            elif type(arg) == AbstractLoop:
                loops.append(arg)
            elif type(arg) == Const:
                consts.append(arg)
            else:
                raise RuntimeError('Unsupported syntax in main program')
        return Program(decls, loops, consts, self.next_node_id())

def parse_str(code, node_id=0):
    parser = Lark(grammar)
    lark_ast = parser.parse(code)
    tree_simplifier = TreeSimplifier(node_id)
    abstract_ast = tree_simplifier.transform(lark_ast)
    return abstract_ast, tree_simplifier.next_node_id()

def parse_file(path, node_id=0):
    with open(path) as f:
        return parse_str(f.read(), node_id)

# TODO write dependence analysis to get dependence matrix
