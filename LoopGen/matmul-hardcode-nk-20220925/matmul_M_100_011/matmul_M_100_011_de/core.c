#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>
#include <assert.h>
#include <limits.h>
#include <math.h>
#include <string.h>

extern int M;
extern int n_arrs;
extern int size;

int core(double (*restrict a)[10000][11], double (*restrict b)[11][100], double (*restrict c)[10000][100], double (*restrict d)[10000][100][11]) {

  for (int m = 0; m <= M - 1; m += 1) {
    for (int n = 0; n <= 100 - 1; n += 1) {
      for (int k = 0; k <= 11 - 1; k += 1) {
        (*c)[m][n] = ((*c)[m][n] + (*a)[m][k] * (*b)[k][n]) / (*d)[m][n][k];
      }
    }
  }
  return 0;
}
