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

extern double x;
extern double x2;
extern double x3;
extern double x4;
extern double x5;
extern double x6;
extern double x7;
extern double x8;

int core(double a[restrict 32000], double a2[restrict 32000], double a3[restrict 1], double a4[restrict 1], double a5[restrict 1], double a6[restrict 1], double a7[restrict 1], double a8[restrict 1], double b[restrict 32000], double b2[restrict 32000], double b3[restrict 32000], double b4[restrict 32000], double b5[restrict 32000], double b6[restrict 32000], double b7[restrict 1], double b8[restrict 1]) {

  for (int i = 0; i <= 31999; ++i) {
    a[i] = (b[i] + x) * 0.5;
    a2[i] = (b2[i] + x2) * 0.5;
    ;
    ;
    ;
    ;
    ;
    ;
    x = b[i];
    x2 = b2[i];
    x3 = b3[i];
    x4 = b4[i];
    x5 = b5[i];
    x6 = b6[i];
    ;
    ;
  }
  return 0;
}
