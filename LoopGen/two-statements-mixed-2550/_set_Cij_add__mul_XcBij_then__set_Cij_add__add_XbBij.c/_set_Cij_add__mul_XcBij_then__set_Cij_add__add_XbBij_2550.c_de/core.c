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

int core(double A[restrict 1][1], double B[restrict 2550][2550], double C[restrict 2550][2550], double D[restrict 1][1], double E[restrict 1][1], double a, double b, double c) {
  for (int i = 0; i <= 2549; i+=1) {
    for (int j = 0; j <= 2549; j+=1) {
        C[i][j] = 1.5 * c + B[i][j];
        C[i][j] = (1.5 + b) + B[i][j];
    }
  }
  return 0;
}

