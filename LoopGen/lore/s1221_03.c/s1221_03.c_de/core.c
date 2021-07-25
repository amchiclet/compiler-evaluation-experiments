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

int core(double a[restrict 32000], double a10[restrict 1], double a11[restrict 1], double a12[restrict 1], double a13[restrict 1], double a14[restrict 1], double a15[restrict 1], double a16[restrict 1], double a2[restrict 32000], double a3[restrict 32000], double a4[restrict 1], double a5[restrict 1], double a6[restrict 1], double a7[restrict 1], double a8[restrict 1], double a9[restrict 1], double b[restrict 32000], double b10[restrict 1], double b11[restrict 1], double b12[restrict 1], double b13[restrict 1], double b14[restrict 1], double b15[restrict 1], double b16[restrict 1], double b2[restrict 32000], double b3[restrict 32000], double b4[restrict 1], double b5[restrict 1], double b6[restrict 1], double b7[restrict 1], double b8[restrict 1], double b9[restrict 1]) {

  for (int i = 4; i <= 31999; ++i) {
    b[i] = b[i - 4] + a[i];
    b2[i] = b2[i - 4] + a2[i];
    b3[i] = b3[i - 4] + a3[i];
    ;
    ;
    ;
    ;
    ;
    ;
    ;
    ;
    ;
    ;
    ;
    ;
    ;
  }
  return 0;
}
