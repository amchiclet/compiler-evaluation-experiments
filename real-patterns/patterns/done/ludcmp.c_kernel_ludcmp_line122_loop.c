declare w;
declare A[][];
declare b[];
declare y[];

for [i] {
  w = b[i];
  for [(j, <=i)] {
    w = w - A[i+1][j] * y[j];
  }
  y[i] = w;
}
