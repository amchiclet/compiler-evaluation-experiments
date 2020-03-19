from lark import Lark, Transformer

grammar = '''
    start: abstract_loop+

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

from abstract_ast import Assignment, AbstractIndex, Access, AbstractLoop, BinOp, Program, get_accesses

class TreeSimplifier(Transformer):
    def __init__(self, start_node_id=0):
        self.current_node_id = start_node_id
    def next_node_id(self):
        self.current_node_id += 1
        return self.current_node_id
    def array(self, args):
        return args[0]
    def scalar(self, args):
        return args[0]
    def index(self, args):
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
        return BinOp(args[0], args[1], self.next_node_id())
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
            print('setting parent statement')
            access.parent_stmt = stmt
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
        return Program(args, self.next_node_id())

def parse_str(code):
    parser = Lark(grammar)
    lark_ast = parser.parse(code)
    tree_simplifier = TreeSimplifier()
    abstract_ast = tree_simplifier.transform(lark_ast)
    print(abstract_ast.pprint())
    return abstract_ast, tree_simplifier.next_node_id()

def parse_file(path):
    with open(path) as f:
        return parse_str(f.read())

# TODO write dependence analysis to get dependence matrix
