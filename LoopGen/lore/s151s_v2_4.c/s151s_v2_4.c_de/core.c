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

int core(double a[restrict 1][32000], double b[restrict 1][32000], double e[restrict 1][4][32000]) {

  for (int i = 0; i <= 31998; ++i) {
    a[0][i] = (((((((((a[0][i + m] + b[0][i]) + e[0][0][i]) + e[0][1][i]) + e[0][2][i]) + e[0][3][i]) + 0) + 0) + 0) + 0) + 0;
    ;
    ;
    ;
  }
  return 0;
}
