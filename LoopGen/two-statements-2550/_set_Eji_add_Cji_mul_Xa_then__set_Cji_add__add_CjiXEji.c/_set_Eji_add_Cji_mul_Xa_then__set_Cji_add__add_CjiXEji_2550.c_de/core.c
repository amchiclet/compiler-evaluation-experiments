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

int core(double A[restrict 1][1], double B[restrict 1][1], double C[restrict 2550][2550], double D[restrict 1][1], double E[restrict 2550][2550], double a, double b, double c) {
  for (int i = 0; i <= 2549; i+=1) {
    for (int j = 0; j <= 2549; j+=1) {
        E[j][i] = C[j][i] + 1.5 * a;
        C[j][i] = (C[j][i] + 1.5) + E[j][i];
    }
  }
  return 0;
}

