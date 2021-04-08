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

int core(double A[restrict 1][1], double B[restrict 1][1], double C[restrict 850][850], double D[restrict 850][850], float E[restrict 1][1]) {
  for (int i = 0; i <= n; ++i) {
    for (int j = 0; j <= n; ++j) {
      D[i][j] = (C[i][j] + D[i][j]) + 1.5 * b;
    }
  }
  return 0;
}
