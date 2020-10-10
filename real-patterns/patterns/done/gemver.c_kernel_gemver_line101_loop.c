declare A[][];
declare u1[];
declare v1[];
declare u2[];
declare v2[];

for [i, j] {
  A[i][j] = A[i][j] + u1[i] * v1[j] + u2[i] * v2[j];
}
