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

int core(double a[restrict 3][32000], double b[restrict 3][32000], double e[restrict 3][7][32000]) {

  for (int i = 0; i <= 31998; ++i) {
    a[0][i] = (((((((((a[0][i + m] + b[0][i]) + e[0][0][i]) + e[0][1][i]) + e[0][2][i]) + e[0][3][i]) + e[0][4][i]) + e[0][5][i]) + e[0][6][i]) + 0) + 0;
    a[1][i] = (((((((((a[1][i + m] + b[1][i]) + e[1][0][i]) + e[1][1][i]) + e[1][2][i]) + 0) + 0) + 0) + 0) + 0) + 0;
    a[2][i] = (((((((((a[2][i + m] + b[2][i]) + e[2][0][i]) + 0) + 0) + 0) + 0) + 0) + 0) + 0) + 0;
    ;
  }
  return 0;
}
