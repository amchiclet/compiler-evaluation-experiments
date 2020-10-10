declare x;
declare b[];
declare c[];
declare a[];
declare d[];
declare e[];

for [i] {
  x = b[i] * c[i] + a[i] * d[i] + e[i];
  a[i] = x - 1.;
  b[i] = x;
}
