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

extern int nmor;

int core(double A[restrict 92700], double B[restrict 92700], double C[restrict 92700], double mormult[restrict 92700], double tmort[restrict 92700]) {

  for (int i = 0; i <= nmor - 1; ++i) {
    ;
    tmort[i] = (((tmort[i] * B[i]) * B[i]) * 1) / (((mormult[i] * C[i]) * 1) * A[i]);
  }
  return 0;
}
