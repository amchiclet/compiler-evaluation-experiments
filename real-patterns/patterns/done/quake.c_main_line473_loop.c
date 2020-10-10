declare disp[][][];
declare M[][];
declare C[][];
declare dt;

for [i, j] {
  disp[disptplus][i][j] = disp[disptplus][i][j] / (M[i][j] + dt / 2.0 * C[i][j]);
}
