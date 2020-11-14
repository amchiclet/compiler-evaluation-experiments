declare A[][];
declare B[][];

for [(i, <=n), (j, <=m)] {
  A[i][j] = (i*j % (n+1)) / (n+1);
  B[i][j] = (i*j % (m+1)) / (m+1);
}

