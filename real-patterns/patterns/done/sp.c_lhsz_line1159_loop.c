declare lhs[][][][];
declare dttz2;
declare speed[][][];

for [i, j, k] {
  lhs[0 + 5][i][j][k] = lhs[0][i][j][k];
  lhs[1 + 5][i][j][k] = lhs[1][i][j][k] - dttz2 * speed[i][j][k - 1];
  lhs[2 + 5][i][j][k] = lhs[2][i][j][k];
  lhs[3 + 5][i][j][k] = lhs[3][i][j][k] + dttz2 * speed[i][j][k + 1];
  lhs[4 + 5][i][j][k] = lhs[4][i][j][k];
  lhs[0 + 10][i][j][k] = lhs[0][i][j][k];
  lhs[1 + 10][i][j][k] = lhs[1][i][j][k] + dttz2 * speed[i][j][k - 1];
  lhs[2 + 10][i][j][k] = lhs[2][i][j][k];
  lhs[3 + 10][i][j][k] = lhs[3][i][j][k] - dttz2 * speed[i][j][k + 1];
  lhs[4 + 10][i][j][k] = lhs[4][i][j][k];
}

