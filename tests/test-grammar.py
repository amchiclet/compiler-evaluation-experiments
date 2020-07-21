from lark import Lark, Transformer

grammar = '''
    start: expr
    expr: conditional
    conditional: logical_or "?" logical_or ":" conditional | logical_or
    logical_or: logical_or "||" logical_and | logical_and
    logical_and: logical_and "&&" equality | equality
    equality: equality EQUAL relational | relational
    relational: relational RELATION additive | additive
    additive: additive ADDITIVE multiplicative | multiplicative
    multiplicative: multiplicative MULTIPLICATIVE unary | unary
    unary: UNARY unary | atom
    atom: int_literal | "(" expr ")"
    int_literal: INT

    EQUAL: "==" | "!="
    RELATION: "<=" | ">=" | "<" | ">"
    ADDITIVE: "+" | "-"
    MULTIPLICATIVE: "*" | "/"
    UNARY: "+" | "-" | "!"
    %import common.WS
    %import common.INT
    %ignore WS

'''

class TreeSimplifier(Transformer):
    def __init__(self, start_node_id=0):
        self.current_node_id = start_node_id
    def start(self, args):
        return args[0]
    def expr(self, args):
        return args[0]
    def conditional(self, args):
        if len(args) == 1:
            return args[0]
        return Op('?:', args)
    def logical_or(self, args):
        if len(args) == 1:
            return args[0]
        return Op('||', args)
    def logical_and(self, args):
        if len(args) == 1:
            return args[0]
        return Op('&&', args)
    def equality(self, args):
        if len(args) == 1:
            return args[0]
        return Op(args[1], [args[0], args[2]])
    def relational(self, args):
        if len(args) == 1:
            return args[0]
        return Op(args[1], [args[0], args[2]])
    def additive(self, args):
        if len(args) == 1:
            return args[0]
        return Op(args[1], [args[0], args[2]])
    def multiplicative(self, args):
        if len(args) == 1:
            return args[0]
        return Op(args[1], [args[0], args[2]])
    def unary(self, args):
        if len(args) == 1:
            return args[0]
        return Op(args[0], [args[1]])
    def atom(self, args):
        return args[0]
    def int_literal(self, args):
        return I(args[0])

class I:
    def __init__(self, i):
        self.i = i
    def precedence(self):
        return 200
    def pprint(self):
        return str(self.i)
class Op:
    def __init__(self, op, args):
        self.op = op
        self.args = args
        self.precedence
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
    def arg_strs(self):
        strs = []
        for arg in self.args:
            arg_str = arg.pprint()
            if self.precedence() >= arg.precedence():
                arg_str = f'({arg_str})'
            strs.append(arg_str)
        return strs
    def pprint(self):
        if len(self.args) == 1:
            args = self.arg_strs()
            return f'{self.op}{args[0]}'
        elif len(self.args) == 2:
            args = self.arg_strs()
            return f'{args[0]} {self.op} {args[1]}'
        elif len(self.args) == 3:
            assert(self.op == '?:')
            args = self.arg_strs()
            return f'{args[0]} ? {args[1]} : {args[2]}'
        raise RuntimeError('Unsuppored argument length: {self.args}')

code = """
3&&(3||3)&&3
"""
parser = Lark(grammar)
lark_ast = parser.parse(code)
node_id = 0
tree_simplifier = TreeSimplifier(node_id)
abstract_ast = tree_simplifier.transform(lark_ast)
print(abstract_ast.pprint())

# def parse_file(path, node_id=0):
#     with open(path) as f:
#         return parse_str(f.read(), node_id)

