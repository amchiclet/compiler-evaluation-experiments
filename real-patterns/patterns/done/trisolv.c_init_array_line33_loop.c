declare x[];
declare b[];
declare L[][];

for [(i, <=n)] {
  x[i] = -999;
  b[i] = i;
  for [(j, <=i)] {
    L[i][j] = (i + n - j + 1) * 2 / n;
  }
}
