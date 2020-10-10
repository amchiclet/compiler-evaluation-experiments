declare a[];
declare b[];
declare c[];
declare d[];

for [i] {
  a[i] = b[i] + c[i] * d[i];
  b[i] = c[i] + b[i];
  a[i + 1] = b[i] + a[i + 1] * d[i];
}
