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

int core(double A[restrict 420][420], double B[restrict 420][420], double C[restrict 420][420], double D[restrict 420][420]) {
  for (int i = 0; i <= n; ++i) {
    for (int j = 0; j <= n; ++j) {
      C[i][j] = (A[i][j] * 1.5) * B[i][j];
      A[i][j] = (D[i][j] + D[i][j]) + C[i][j];
    }
  }
  return 0;
}
