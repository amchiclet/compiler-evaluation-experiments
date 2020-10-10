declare a[];
declare b[];
declare c[];
declare d[];
declare e[];

for [i] {
  a[i] = b[i - 1] + c[i] * d[i];
  b[i] = a[i] + c[i] * e[i];
}
