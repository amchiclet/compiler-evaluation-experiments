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

extern int n;
extern double x;

int core(double A[restrict n], double B[restrict n]) {

for (int i = 0; i <= n - 1; ++i) {
  A[i] = (B[i] + x) * 0.5;
  x = B[i];
}
  return 0;
}
