declare A[][];
declare Q[][];

for [i, j] {
  A[i][j] = (i * j % m) / m * 100 + 10;
  Q[i][j] = 0.0;
}
