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

int core(double C[restrict 900][1200], double C2[restrict 900][1200], double C3[restrict 900][1200], double C4[restrict 900][1200], double C5[restrict 900][1200], double C6[restrict 900][1200], double C7[restrict 900][1200], double C8[restrict 1][1], double D[restrict 1200][1100], double D2[restrict 1200][1100], double D3[restrict 1200][1100], double D4[restrict 1200][1100], double D5[restrict 1200][1100], double D6[restrict 1200][1100], double D7[restrict 1200][1100], double D8[restrict 1][1], double F[restrict 900][1100], double F2[restrict 900][1100], double F3[restrict 900][1100], double F4[restrict 900][1100], double F5[restrict 900][1100], double F6[restrict 900][1100], double F7[restrict 900][1100], double F8[restrict 1][1]) {

  for (int i = 0; i <= nj - 1; ++i) {
    for (int j = 0; j <= nl - 1; ++j) {
      F[i][j] = 0.0;
      F2[i][j] = 0.0;
      F3[i][j] = 0.0;
      ;
      ;
      ;
      ;
      ;
      for (int k = 0; k <= nm - 1; ++k) {
        F[i][j] = F[i][j] + C[i][k] * D[k][j];
        F2[i][j] = F2[i][j] + C2[i][k] * D2[k][j];
        F3[i][j] = F3[i][j] + C3[i][k] * D3[k][j];
        F4[i][j] = F4[i][j] + C4[i][k] * D4[k][j];
        F5[i][j] = F5[i][j] + C5[i][k] * D5[k][j];
        F6[i][j] = F6[i][j] + C6[i][k] * D6[k][j];
        F7[i][j] = F7[i][j] + C7[i][k] * D7[k][j];
        ;
      }
    }
  }
  return 0;
}
