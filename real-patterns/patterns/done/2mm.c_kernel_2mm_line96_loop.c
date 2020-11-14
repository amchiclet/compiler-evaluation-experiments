declare D[][];
declare tmp[][];
declare C[][];

for [i, j] {
  D[i][j] = D[i][j] * beta;
  for [k] {
    D[i][j] = D[i][j] + tmp[i][k] * C[k][j];
  }
}

