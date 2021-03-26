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

int core(double A[restrict 2550][2550], double B[restrict 2550][2550], double C[restrict 1][1], double D[restrict 2550][2550], double E[restrict 2550][2550], double a, double b, double c) {
  for (int i = 0; i <= 2549; i+=1) {
    for (int j = 0; j <= 2549; j+=1) {
        E[i][j] = D[i][j] * 1.5 + 1.5;
        E[i][j] = B[i][j] + A[i][j] * B[i][j];
    }
  }
  return 0;
}

