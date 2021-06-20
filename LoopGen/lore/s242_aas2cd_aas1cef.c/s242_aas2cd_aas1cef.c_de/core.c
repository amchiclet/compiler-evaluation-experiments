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

extern double s1;
extern double s2;

int core(double a[restrict 32000], double b[restrict 32000], double c[restrict 32000], double d[restrict 32000], double e[restrict 32000], double f[restrict 32000], double g[restrict 32000]) {

  for (int i = 1; i <= 31999; ++i) {
    a[i] = (((((((a[i - 1] + 0) + s2) + 0) + c[i]) + d[i]) + 0) + 0) + 0;
  }
  for (int i = 1; i <= 31999; ++i) {
    a[i] = (((((((a[i - 1] + s1) + 0) + 0) + c[i]) + 0) + e[i]) + f[i]) + 0;
  }
  return 0;
}
