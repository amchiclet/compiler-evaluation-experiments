declare a[];
for [(j, >=0, <=n), (i, >=0, <=j)] {
  a[i+j*n] = a[j+i*n];
}

