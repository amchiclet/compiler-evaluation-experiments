#include <x86intrin.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>
#include <assert.h>
#include <limits.h>
#include <math.h>
#include <string.h>

extern double add;

int core(int grid_points[restrict 3], double rhs[restrict (64 / 2) * 2 + 1][(64 / 2) * 2 + 1][(64 / 2) * 2 + 1][7], double rms[restrict 7]) {

for (int i = 1; i <= grid_points[0] - 2; ++i) {
  for (int j = 1; j <= 1; ++j) {
    for (int k = 1; k <= grid_points[2] - 2; ++k) {
      for (int m = 0; m <= 7 - 1; ++m) {
        add = rhs[i][j][k][m];
        rms[m] = rms[m] + add * add;
      }
    }
  }
}
  return 0;
}
