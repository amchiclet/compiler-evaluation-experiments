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

int core(double A[restrict 2550], double B[restrict 1], double C[restrict 1], double S[restrict 1], double a, double b, double c) {
  for (int i = 0; i <= 2549; i+=1) {
      S[0] = (S[0] * c) * A[i];
  }
  return 0;
}

