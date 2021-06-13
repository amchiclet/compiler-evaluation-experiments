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

int core(int grid_points[restrict 3], double rhs[restrict (64 / 2) * 2 + 1][(64 / 2) * 2 + 1][(64 / 2) * 2 + 1][8], double rms[restrict 8]) {

for (int i = 1; i <= grid_points[0] - 2; ++i) {
  for (int j = 1; j <= grid_points[1] - 2; ++j) {
    for (int k = 1; k <= grid_points[2] - 2; ++k) {
      for (int m = 0; m <= 8 - 1; ++m) {
        add = rhs[i][j][k][m];
        rms[m] = rms[m] + add * add;
      }
    }
  }
}
  return 0;
}
