declare rhs[][][][];
declare u[][][][];
declare dssp;

for [m, i, k] {
  rhs[m][i][j][k] = rhs[m][i][j][k] - dssp *(u[m][i][j - 2][k] - 4.0 * u[m][i][j - 1][k] + 6.0 * u[m][i][j][k] - 4.0 * u[m][i][j + 1][k]);
}
