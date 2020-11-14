declare A[][];
declare B[][];

for [(i, <=n), (j, <=n)] {
  A[i][j] = (i * (j+2) + 2) / (n+1);
  B[i][j] = (i * (j+3) + 3) / (n+1);
}
