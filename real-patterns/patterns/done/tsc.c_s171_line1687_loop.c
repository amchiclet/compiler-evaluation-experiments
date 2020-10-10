declare a[];
declare b[];

for [i] {
  a[i * stride] = a[i * stride] + b[i];
}
