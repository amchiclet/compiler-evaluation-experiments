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

int core(double a[restrict 32000], double b[restrict 32000]) {

  for (int i = 0; i <= 31998; ++i) {
    a[i] = a[i + m] + b[i];
  }
  return 0;
}
