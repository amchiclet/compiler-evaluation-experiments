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

int core(double A[restrict 1][1], double B[restrict 420][420], double C[restrict 420][420], double D[restrict 420][420], float E[restrict 1][1]) {
  for (int i = 0; i <= n; ++i) {
    for (int j = 0; j <= n; ++j) {
      D[i][j] = ((B[i][j] + C[i][j]) + 1.5) + D[i][j];
    }
  }
  return 0;
}
