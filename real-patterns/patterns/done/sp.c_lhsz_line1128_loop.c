declare lhs[][][][];
declare comz1;
declare comz4;
declare comz6;

for [i, j, k] {
  lhs[0][i][j][k] = lhs[0][i][j][k] + comz1;
  lhs[1][i][j][k] = lhs[1][i][j][k] - comz4;
  lhs[2][i][j][k] = lhs[2][i][j][k] + comz6;
  lhs[3][i][j][k] = lhs[3][i][j][k] - comz4;
  lhs[4][i][j][k] = lhs[4][i][j][k] + comz1;
}
