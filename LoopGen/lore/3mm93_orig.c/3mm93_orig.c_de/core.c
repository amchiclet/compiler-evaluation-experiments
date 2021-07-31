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

extern int nj;
extern int nl;
extern int nm;

int core(double C[restrict 900][1200], double D[restrict 1200][1100], double F[restrict 900][1100]) {

  for (int i = 0; i <= nj - 1; ++i) {
    for (int j = 0; j <= nl - 1; ++j) {
      F[i][j] = 0.0;
      for (int k = 0; k <= nm - 1; ++k) {
        F[i][j] = F[i][j] + C[i][k] * D[k][j];
      }
    }
  }
  return 0;
}
