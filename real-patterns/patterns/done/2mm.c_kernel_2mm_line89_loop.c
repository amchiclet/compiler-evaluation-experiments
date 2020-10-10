declare tmp[][];
declare A[][];
declare B[][];
declare alpha;

for [i, j] {
  tmp[i][j] = 0.0;
  for [k] {
    tmp[i][j] = tmp[i][j] + alpha * A[i][k] * B[k][j];
  }
}
