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

int core(double A[restrict 2550][2550], double B[restrict 2550][2550], double C[restrict 2550][2550], double D[restrict 1][1], double E[restrict 2550][2550]) {
  for (int i = 0; i <= 2549; i+=1) {
    for (int j = 0; j <= 2549; j+=1) {
      for (int k = 0; k <= 2549; k+=1) {
          A[i][j] = A[i][j] + (B[i][k] + E[i][k]) * (E[k][j] + C[k][j]);
      }
    }
  }
  return 0;
}

