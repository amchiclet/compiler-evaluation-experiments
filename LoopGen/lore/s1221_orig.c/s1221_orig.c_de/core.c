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



int core(double a[restrict 32000], double b[restrict 32000]) {

  for (int i = 4; i <= 31999; ++i) {
    b[i] = b[i - 4] + a[i];
  }
  return 0;
}
