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

int core(double A[restrict 2550], double B[restrict 2550], double C[restrict 2550], double S[restrict 1], double a, double b, double c) {
  for (int i = 0; i <= 2549; i+=1) {
      B[i] = (B[i] * A[i]) * C[i];
  }
  return 0;
}

