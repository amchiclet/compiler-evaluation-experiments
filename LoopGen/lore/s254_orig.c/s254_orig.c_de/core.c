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

int core(double a[restrict 32000], double b[restrict 32000]) {

  for (int i = 0; i <= 31999; ++i) {
    a[i] = (b[i] + x) * 0.5;
    x = b[i];
  }
  return 0;
}
