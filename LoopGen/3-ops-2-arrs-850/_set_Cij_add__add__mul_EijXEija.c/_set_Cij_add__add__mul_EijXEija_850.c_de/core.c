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

int core(double A[restrict 1][1], double B[restrict 1][1], double C[restrict 850][850], double D[restrict 1][1], double E[restrict 850][850]) {
  for (int i = 0; i <= n; ++i) {
    for (int j = 0; j <= n; ++j) {
      C[i][j] = (E[i][j] * 1.5 + E[i][j]) + a;
    }
  }
  return 0;
}
