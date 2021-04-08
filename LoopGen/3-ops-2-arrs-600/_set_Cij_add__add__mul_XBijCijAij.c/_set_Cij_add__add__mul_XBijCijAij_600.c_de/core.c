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

extern double a;
extern double b;
extern int n;

int core(double A[restrict 600][600], double B[restrict 600][600], double C[restrict 600][600], double D[restrict 1][1], double E[restrict 1][1]) {
  for (int i = 0; i <= n; ++i) {
    for (int j = 0; j <= n; ++j) {
      C[i][j] = (1.5 * B[i][j] + C[i][j]) + A[i][j];
    }
  }
  return 0;
}
