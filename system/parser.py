from lark import Lark, Transformer

grammar = '''
    start: abstract_loop

    abstract_loop: "for" "[" loop_vars "]" "{" statement+ "}"
    loop_vars: scalar ("," scalar)*

    statement: assignment
    assignment: access "=" expr ";"

    expr: binop | access
    binop: expr "*" expr

    access: scalar_access | array_access
    scalar_access: scalar
    array_access: array ("[" index "]")+
    index: scalar | greater_than | less_than
    greater_than: ">" index
    less_than: "<" index

    scalar: LCASE_LETTER+
    array: UCASE_LETTER+

    %import common.WS
    %import common.LCASE_LETTER
    %import common.UCASE_LETTER
    %ignore WS
'''

from abstract_ast import Assignment, Index, Access, AbstractLoop, BinOp

class TreeSimplifier(Transformer):
    def array(self, args):
        return args[0]
    def scalar(self, args):
        return args[0]
    def index(self, args):
        if isinstance(args[0], Index):
            return args[0]
        else:
            return Index(args[0])
    def greater_than(self, args):
        index = args[0]
        return Index(index.var, index.relationship + 1)
    def less_than(self, args):
        index = args[0]
        return Index(index.var, index.relationship - 1)
    def scalar_access(self, args):
        return Access(args[0])
    def array_access(self, args):
        return Access(args[0], args[1:])
    def access(self, args):
        return args[0]
    def binop(self, args):
        return BinOp(args[0], args[1])
    def expr(self, args):
        return args[0]
    def assignment(self, args):
        return Assignment(args[0], args[1])
    def statement(self, args):
        return args[0]
    def loop_vars(self, args):
        return args
    def abstract_loop(self, args):
        return AbstractLoop(args[0], args[1:])
    def start(self, args):
        return args[0]

def parse_str(code):
    parser = Lark(grammar)
    lark_ast = parser.parse(code)
    abstract_ast = TreeSimplifier().transform(lark_ast)
    print(abstract_ast.pprint())
    return abstract_ast

def parse_file(path):
    with open(path) as f:
        return parse_str(f.read())

# TODO write dependence analysis to get dependence matrix
