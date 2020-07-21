from parser import parse_str

code = """
declare a[];
for [i] {
  a[0] = 3&&(3||3)&&3;
}
"""
ast, _ = parse_str(code)
print(ast.pprint())
