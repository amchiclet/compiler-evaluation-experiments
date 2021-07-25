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

extern int m;

int core(double a[restrict 32000], double a10[restrict 32000], double a11[restrict 32000], double a12[restrict 1], double a13[restrict 1], double a14[restrict 1], double a15[restrict 1], double a16[restrict 1], double a2[restrict 32000], double a3[restrict 32000], double a4[restrict 32000], double a5[restrict 32000], double a6[restrict 32000], double a7[restrict 32000], double a8[restrict 32000], double a9[restrict 32000], double b[restrict 32000], double b10[restrict 31999], double b11[restrict 31999], double b12[restrict 1], double b13[restrict 1], double b14[restrict 1], double b15[restrict 1], double b16[restrict 1], double b2[restrict 31999], double b3[restrict 31999], double b4[restrict 31999], double b5[restrict 31999], double b6[restrict 31999], double b7[restrict 31999], double b8[restrict 31999], double b9[restrict 31999]) {

  for (int i = 0; i <= 31998; ++i) {
    a[i] = a[i + m] + b[i];
    a2[i] = a2[i + m] + b2[i];
    a3[i] = a3[i + m] + b3[i];
    a4[i] = a4[i + m] + b4[i];
    a5[i] = a5[i + m] + b5[i];
    a6[i] = a6[i + m] + b6[i];
    a7[i] = a7[i + m] + b7[i];
    a8[i] = a8[i + m] + b8[i];
    a9[i] = a9[i + m] + b9[i];
    a10[i] = a10[i + m] + b10[i];
    a11[i] = a11[i + m] + b11[i];
    ;
    ;
    ;
    ;
    ;
  }
  return 0;
}
