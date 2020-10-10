declare MV[][][][];
declare modemap[][];

for [i] {
  for [k] {
      MV[0][k][i][0] = 0;
      MV[1][k][i][0] = 0;
      MV[0][k][i][mb_width + 1] = 0;
      MV[1][k][i][mb_width + 1] = 0;
  }
  modemap[i][0] = 3;
  modemap[i][mb_width + 1] = 3;
}
