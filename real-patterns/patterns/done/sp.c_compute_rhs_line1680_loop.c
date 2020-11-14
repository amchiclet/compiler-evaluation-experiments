declare dssp;
declare rhs[][][][];
declare u[][][][];

for [m, i, j] {
  rhs[m][i][j][k] = rhs[m][i][j][k] - dssp *(u[m][i][j][k - 2] - 4.0 * u[m][i][j][k - 1] + 5.0 * u[m][i][j][k]);
}
