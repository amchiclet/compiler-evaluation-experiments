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

extern int m;

int core(double a[restrict 2][32000], double b[restrict 2][32000], double e[restrict 2][6][32000]) {

  for (int i = 0; i <= 31998; ++i) {
    a[0][i] = (((((((((a[0][i + m] + b[0][i]) + e[0][0][i]) + 0) + 0) + 0) + 0) + 0) + 0) + 0) + 0;
    a[1][i] = (((((((((a[1][i + m] + b[1][i]) + e[1][0][i]) + e[1][1][i]) + e[1][2][i]) + e[1][3][i]) + e[1][4][i]) + e[1][5][i]) + 0) + 0) + 0;
    ;
    ;
  }
  return 0;
}
