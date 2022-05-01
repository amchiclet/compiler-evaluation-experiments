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

int core(int (*restrict a)[N]) {

  for (int i = 0; i <= N - 1; i += 1) {
    (*a)[i] = (*a)[i] + (*a)[i];
  }
  return 0;
}
