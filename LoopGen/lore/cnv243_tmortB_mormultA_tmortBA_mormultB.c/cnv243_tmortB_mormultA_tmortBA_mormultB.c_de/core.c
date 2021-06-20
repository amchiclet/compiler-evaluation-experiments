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

int core(double A[restrict 92700], double B[restrict 92700], double C[restrict 1], double mormult[restrict 92700], double tmort[restrict 92700]) {

  for (int i = 0; i <= nmor - 1; ++i) {
    tmort[i] = (((tmort[i] * 1) * 1) * B[i]) / (((mormult[i] * A[i]) * 1) * 1);
    tmort[i] = (((tmort[i] * 1) * B[i]) * A[i]) / (((mormult[i] * 1) * 1) * B[i]);
  }
  return 0;
}
