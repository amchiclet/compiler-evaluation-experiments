from parser import parse_str
from loguru import logger
from transformers.loop_unroll import LoopUnroll
from variable_map import VariableMap, create_instance
from itertools import islice, zip_longest
code = """
declare A[][][];
for [i, j, k] {
    A[i][j][k] = 0;
}
"""

def enumerate_g(limit, g):
    yield from zip_longest(range(limit), islice(g, limit))

program, _ = parse_str(code)
print(program.pprint())
var_map = VariableMap()
instance = create_instance(program, var_map)
loop_unroll = LoopUnroll()

g = loop_unroll.transform(instance)
for m in range(2):
    mutation = next(g)
    print(m)
    print(mutation.pprint())
