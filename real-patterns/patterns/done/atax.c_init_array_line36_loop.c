declare A[][];

for [(i, <=m), (j, <=n)] {
  A[i][j] = ((i + j) % (n - 1)) / (5 * (m-1));
}
