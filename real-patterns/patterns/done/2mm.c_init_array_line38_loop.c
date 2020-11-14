declare A[][];

for [(i, <=ni), j] {
  A[i][j] = (i*j % (ni+1)) / (ni+1);
}
