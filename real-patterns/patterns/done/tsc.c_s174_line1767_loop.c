declare a[];
declare b[];

for [(i, <=M)] {
  a[i + M+1] = a[i] + b[i];
}
