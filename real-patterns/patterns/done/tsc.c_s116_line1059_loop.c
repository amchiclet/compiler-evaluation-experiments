declare a[];

for [(i, +=5)] {
  a[i] = a[i + 1] * a[i];
  a[i + 1] = a[i + 2] * a[i + 1];
  a[i + 2] = a[i + 3] * a[i + 2];
  a[i + 3] = a[i + 4] * a[i + 3];
  a[i + 4] = a[i + 5] * a[i + 4];
}
