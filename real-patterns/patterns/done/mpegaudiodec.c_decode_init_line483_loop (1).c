declare mdct_win[][];

for [(j, <=3), (i, +=2)] {
  mdct_win[j + 4][i] = mdct_win[j][i];
  mdct_win[j + 4][i + 1] = -mdct_win[j][i + 1];
}
