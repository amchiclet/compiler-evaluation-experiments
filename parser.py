from lark import Lark, Transformer

# Note:
# Operator precedence is based on
# https://docs.microsoft.com/en-us/cpp/c-language/precedence-and-order-of-evaluation?view=vs-2019

grammar = '''
    start: (declaration | const)+ statement+

    declaration: "declare" array (dimension)* ";"
    const: "const" scalar ";"
    dimension: "[" "]"
    abstract_loop: "for" "[" loop_vars "]" "{" statement+ "}"
    loop_vars: scalar ("," scalar)*

    statement: assignment | abstract_loop
    assignment: access "=" expr ";"

    expr: conditional
    conditional: logical_or "?" logical_or ":" conditional | logical_or
    logical_or: logical_or "||" logical_and | logical_and
    logical_and: logical_and "&&" equality | equality
    equality: equality EQUAL relational | relational
    relational: relational RELATION additive | additive
    additive: additive ADDITIVE multiplicative | multiplicative
    multiplicative: multiplicative MULTIPLICATIVE unary | unary
    unary: UNARY unary | atom
    atom: access | "(" expr ")"

    access: scalar_access | array_access | literal
    scalar_access: scalar
    array_access: array ("[" expr "]")+
    literal: float_literal | int_literal
    float_literal: FLOAT
    int_literal: INT

    scalar: CNAME
    array: CNAME

    EQUAL: "==" | "!="
    RELATION: "<=" | ">=" | "<" | ">"
    ADDITIVE: "+" | "-"
    MULTIPLICATIVE: "*" | "/"
    UNARY: "+" | "-" | "!"

    %import common.WS
    %import common.LCASE_LETTER
    %import common.UCASE_LETTER
    %import common.CNAME
    %import common.INT
    %import common.FLOAT
    %ignore WS

'''

from abstract_ast import Assignment, Access, AbstractLoop, Program, get_accesses, Declaration, Const, Literal, Op
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
    def array(self, args):
        return ''.join(args)
    def const(self, args):
        return Const(args[0], self.next_node_id())
    def scalar(self, args):
        return ''.join(args)
    def index(self, args):
        return args[0]
    def literal(self, args):
        return args[0]
    def float_literal(self, args):
        return Literal(float, float(args[0]), self.next_node_id())
    def int_literal(self, args):
        return Literal(int, int(args[0]), self.next_node_id())
    def scalar_access(self, args):
        return Access(args[0], node_id=self.next_node_id())
    def array_access(self, args):
        return Access(args[0], args[1:], self.next_node_id())
    def access(self, args):
        return args[0]

    def expr(self, args):
        return args[0]
    def conditional(self, args):
        if len(args) == 1:
            return args[0]
        return Op('?:', args, self.next_node_id())
    def logical_or(self, args):
        if len(args) == 1:
            return args[0]
        return Op('||', args, self.next_node_id())
    def logical_and(self, args):
        if len(args) == 1:
            return args[0]
        return Op('&&', args, self.next_node_id())
    def equality(self, args):
        if len(args) == 1:
            return args[0]
        return Op(args[1], [args[0], args[2]], self.next_node_id())
    def relational(self, args):
        if len(args) == 1:
            return args[0]
        return Op(args[1], [args[0], args[2]], self.next_node_id())
    def additive(self, args):
        if len(args) == 1:
            return args[0]
        return Op(args[1], [args[0], args[2]], self.next_node_id())
    def multiplicative(self, args):
        if len(args) == 1:
            return args[0]
        return Op(args[1], [args[0], args[2]], self.next_node_id())
    def unary(self, args):
        if len(args) == 1:
            return args[0]
        return Op(args[0], [args[1]], self.next_node_id())
    def atom(self, args):
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
        body = []
        consts = []
        for arg in args:
            if type(arg) == Declaration:
                decls.append(arg)
            elif type(arg) in [AbstractLoop, Assignment]:
                body.append(arg)
            elif type(arg) == Const:
                consts.append(arg)
            else:
                raise RuntimeError('Unsupported syntax in main program')
        return Program(decls, body, consts, self.next_node_id())

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
