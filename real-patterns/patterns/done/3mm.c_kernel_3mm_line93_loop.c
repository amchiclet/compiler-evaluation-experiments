declare F[][];
declare C[][];
declare D[][];

for [i, j] {
  F[i][j] = 0.0;
  for [k] {
      F[i][j] = F[i][j] + C[i][k] * D[k][j];
  }
}
