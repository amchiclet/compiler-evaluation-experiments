from parser import parse_file, parse_str
from loguru import logger
from transformers.loop_interchange import LoopInterchange
from variable_map import VariableMap, restrict_var_map, calculate_array_sizes
from simple_formatter import SimpleFormatter

nested = """
declare A[I];
declare B[J];

for [i] {
  A[i] = A[i+1] * B[i];
  for [j] {
    A[j] = A[j-2] * B[j];
  }
  for [j] {
    A[j-3] = A[j-4] * B[j];
  }
}
"""


multi = """
declare A[I];
declare B[J];

for [i] {
  A[i] = A[i+1] * B[i];
}
for [j] {
  A[j] = A[j-2] * B[j];
}
"""

program, _ = parse_str(multi)
print(program.pprint())

from dependence_analysis import analyze_dependence
var_map = VariableMap()
dependence_graph = analyze_dependence(program, var_map)
dependence_graph.debug()
