declare A[][];

for [(i, <=n), (j, <=m)] {
  A[i][j] = (i * j % (n-1)) / (n-1);
}
