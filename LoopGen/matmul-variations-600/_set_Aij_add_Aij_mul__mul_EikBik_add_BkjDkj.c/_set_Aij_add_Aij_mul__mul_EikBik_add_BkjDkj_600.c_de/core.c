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

int core(double A[restrict 600][600], double B[restrict 600][600], double C[restrict 1][1], double D[restrict 600][600], double E[restrict 600][600]) {
  for (int i = 0; i <= 599; i+=1) {
    for (int j = 0; j <= 599; j+=1) {
      for (int k = 0; k <= 599; k+=1) {
          A[i][j] = A[i][j] + (E[i][k] * B[i][k]) * (B[k][j] + D[k][j]);
      }
    }
  }
  return 0;
}

