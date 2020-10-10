declare rhs[][][][];
declare dssp;
declare u[][][][];

for [i, k, m] {
  rhs[i][j][k][m] = rhs[i][j][k][m] - dssp *(u[i][j - 2][k][m] - 4.0 * u[i][j - 1][k][m] + 5.0 * u[i][j][k][m]);
}
