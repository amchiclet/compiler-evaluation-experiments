program = """
    for [i, j, k]  {
      A[>i][>j][>k] = B[i][j][k] * C[i][<j][<k];
      A[>i][>j][>k] = B[i][j][k] * C[i][<j][<k];
    }
"""

from parser import parse_str, parse_file
parse_str(program)
parse_file('test.loop')
