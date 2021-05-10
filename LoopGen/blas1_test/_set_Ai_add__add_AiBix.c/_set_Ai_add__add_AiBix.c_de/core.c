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

extern int ii;
extern int n;

int core(double A[restrict n], double B[restrict n]) {
int i;
i = 0;
for (i = 0; i <= n - 1; ++i) {
  A[i] = (A[i] + B[i]) + 5;
}
ii = i;
  return 0;
}
