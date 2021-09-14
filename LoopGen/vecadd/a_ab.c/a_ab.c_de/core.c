#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>
#include <assert.h>
#include <limits.h>
#include <math.h>
#include <string.h>

extern int N;

int core(double a[restrict N], double b[restrict N]) {

  for (int i = 0; i <= N - 1; ++i) {
    a[i] = a[i] + b[i];
  }
  return 0;
}
