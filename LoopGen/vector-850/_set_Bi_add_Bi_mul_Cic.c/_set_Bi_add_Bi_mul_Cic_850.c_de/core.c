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

int core(double A[restrict 1], double B[restrict 850], double C[restrict 850], double S[restrict 1], double a, double b, double c) {
  for (int i = 0; i <= 849; i+=1) {
      B[i] = B[i] + C[i] * c;
  }
  return 0;
}

