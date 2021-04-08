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

int core(double A[restrict 850][850], double B[restrict 850][850], double C[restrict 850][850], double D[restrict 850][850]) {
  for (int i = 0; i <= n; ++i) {
    for (int j = 0; j <= n; ++j) {
      A[i][j] = (B[i][j] + A[i][j]) + C[i][j];
      C[i][j] = D[i][j] * b + A[i][j];
    }
  }
  return 0;
}
