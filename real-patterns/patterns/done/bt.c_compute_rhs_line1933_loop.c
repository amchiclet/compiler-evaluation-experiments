declare vijk;
declare vs[][][] ;
declare vp1;
declare vm1;
declare rhs[][][][] ;
declare dy1ty1;
declare u[][][][] ;
declare ty2;
declare dy2ty1;
declare yycon2;
declare us[][][] ;
declare dy3ty1;
declare con43;
declare square[][][] ;
declare c2;
declare dy4ty1;
declare ws[][][] ;
declare dy5ty1;
declare yycon3;
declare qs[][][] ;
declare yycon4;
declare yycon5;
declare rho_i[][][] ;
declare c1;

for [i, j, k] {
  vijk = vs[i][j][k];
  vp1 = vs[i][j + 1][k];
  vm1 = vs[i][j - 1][k];

  rhs[i][j][k][0] = rhs[i][j][k][0] +
    dy1ty1 *(u[i][j + 1][k][0] - 2.0 * u[i][j][k][0] + u[i][j - 1][k][0]) -
    ty2 *(u[i][j + 1][k][2] - u[i][j - 1][k][2]);
  rhs[i][j][k][1] = rhs[i][j][k][1] +
    dy2ty1 *(u[i][j + 1][k][1] - 2.0 * u[i][j][k][1] + u[i][j - 1][k][1]) +
    yycon2 *(us[i][j + 1][k] - 2.0 * us[i][j][k] + us[i][j - 1][k]) -
    ty2 *(u[i][j + 1][k][1] * vp1 - u[i][j - 1][k][1] * vm1);
  rhs[i][j][k][2] = rhs[i][j][k][2] +
    dy3ty1 *(u[i][j + 1][k][2] - 2.0 * u[i][j][k][2] + u[i][j - 1][k][2]) +
    yycon2 * con43 *(vp1 - 2.0 * vijk + vm1) -
    ty2 *(u[i][j + 1][k][2] * vp1 - u[i][j - 1][k][2] * vm1 +(u[i][j + 1][k][4] - square[i][j + 1][k] - u[i][j - 1][k][4] + square[i][j - 1][k]) * c2);
  rhs[i][j][k][3] = rhs[i][j][k][3] +
    dy4ty1 *(u[i][j + 1][k][3] - 2.0 * u[i][j][k][3] + u[i][j - 1][k][3]) +
    yycon2 *(ws[i][j + 1][k] - 2.0 * ws[i][j][k] + ws[i][j - 1][k]) -
    ty2 *(u[i][j + 1][k][3] * vp1 - u[i][j - 1][k][3] * vm1);
  rhs[i][j][k][4] = rhs[i][j][k][4] +
    dy5ty1 *(u[i][j + 1][k][4] - 2.0 * u[i][j][k][4] + u[i][j - 1][k][4]) +
    yycon3 *(qs[i][j + 1][k] - 2.0 * qs[i][j][k] + qs[i][j - 1][k]) +
    yycon4 *(vp1 * vp1 - 2.0 * vijk * vijk + vm1 * vm1) +
    yycon5 *(u[i][j + 1][k][4] * rho_i[i][j + 1][k] - 2.0 * u[i][j][k][4] * rho_i[i][j][k] + u[i][j - 1][k][4] * rho_i[i][j - 1][k]) -
    ty2 *((c1 * u[i][j + 1][k][4] - c2 * square[i][j + 1][k]) * vp1 -(c1 * u[i][j - 1][k][4] - c2 * square[i][j - 1][k]) * vm1);
}

