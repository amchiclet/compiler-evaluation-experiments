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

int core(double A[restrict 850][850], double B[restrict 1][1], double C[restrict 850][850], double D[restrict 1][1], double E[restrict 1][1], double a, double b, double c) {
  for (int i = 0; i <= 849; i+=1) {
    for (int j = 0; j <= 849; j+=1) {
        A[i][j] = (c + 1.5) + 1.5;
        A[i][j] = (1.5 + C[i][j]) + c;
    }
  }
  return 0;
}

