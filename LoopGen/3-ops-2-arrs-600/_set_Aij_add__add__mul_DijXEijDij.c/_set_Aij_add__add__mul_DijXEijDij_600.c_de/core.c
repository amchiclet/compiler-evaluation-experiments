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

int core(double A[restrict 600][600], double B[restrict 1][1], double C[restrict 1][1], double D[restrict 600][600], double E[restrict 600][600]) {
  for (int i = 0; i <= n; ++i) {
    for (int j = 0; j <= n; ++j) {
      A[i][j] = (D[i][j] * 1.5 + E[i][j]) + D[i][j];
    }
  }
  return 0;
}
