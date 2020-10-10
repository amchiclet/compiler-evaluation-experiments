declare c[][];
declare counts[];
declare c1[][];

for [i, j] {
  c[i][j] = counts[i] ? c1[i][j] / counts[i] : c1[i][j];
}
