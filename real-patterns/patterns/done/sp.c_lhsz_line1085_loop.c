declare ru1;
declare c3c4;
declare rho_i[][][];
declare  cv[];
declare  ws[][][];
declare  rhos[];
declare dz4;
declare con43;
declare dz5;
declare c1c5;
declare dzmax;
declare dz1;
declare  lhs[][][][];
declare dttz2;
declare dttz1;
declare c2dttz1;

for [i, j] {
  for [(k, <=grid_points-1)] {
      ru1 = c3c4 * rho_i[i][j][k];
      cv[k] = ws[i][j][k];
      rhos[k] =(dz4 + con43 * ru1 >((dz5 + c1c5 * ru1 >((dzmax + ru1 > dz1?dzmax + ru1 : dz1))?dz5 + c1c5 * ru1 :((dzmax + ru1 > dz1?dzmax + ru1 : dz1))))?dz4 + con43 * ru1 :((dz5 + c1c5 * ru1 >((dzmax + ru1 > dz1?dzmax + ru1 : dz1))?dz5 + c1c5 * ru1 :((dzmax + ru1 > dz1?dzmax + ru1 : dz1)))));
  }
  for [(k, <=grid_points-2)] {
      lhs[0][i][j][k] = 0.0;
      lhs[1][i][j][k] = -dttz2 * cv[k - 1] - dttz1 * rhos[k - 1];
      lhs[2][i][j][k] = 1.0 + c2dttz1 * rhos[k];
      lhs[3][i][j][k] = dttz2 * cv[k + 1] - dttz1 * rhos[k + 1];
      lhs[4][i][j][k] = 0.0;
  }
}
