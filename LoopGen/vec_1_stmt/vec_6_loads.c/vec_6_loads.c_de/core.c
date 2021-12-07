#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>
#include <assert.h>
#include <limits.h>
#include <math.h>
#include <string.h>

extern int I;

int core(double A[restrict 32000], double B1[restrict 32000], double B2[restrict 32000], double B3[restrict 32000], double B4[restrict 32000], double B5[restrict 32000], double B6[restrict 32000], double B7[restrict 1], double B8[restrict 1], double B9[restrict 1]) {

  for (int i = 0; i <= I - 1; ++i) {
    A[i] = ((B2[i] * B5[i] + B1[i]) + (B3[i] * B6[i] + B5[i])) + (B4[i] * B3[i] + B1[i]);
  }
  return 0;
}
