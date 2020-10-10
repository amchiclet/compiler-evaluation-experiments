declare x;
declare a[];
declare b[];
declare c[];

for [i] {
  x = a[32000 - i - 1] + b[i] * c[i];
  a[i] = x -((float )1.);
  b[i] = x;
}
