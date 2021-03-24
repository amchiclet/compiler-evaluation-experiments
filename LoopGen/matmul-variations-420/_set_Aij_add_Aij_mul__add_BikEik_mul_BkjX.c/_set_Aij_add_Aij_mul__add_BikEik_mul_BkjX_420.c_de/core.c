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

int core(double A[restrict 420][420], double B[restrict 420][420], double C[restrict 1][1], double D[restrict 1][1], double E[restrict 420][420]) {
  for (int i = 0; i <= 419; i+=1) {
    for (int j = 0; j <= 419; j+=1) {
      for (int k = 0; k <= 419; k+=1) {
          A[i][j] = A[i][j] + (B[i][k] + E[i][k]) * (B[k][j] * 1.5);
      }
    }
  }
  return 0;
}

