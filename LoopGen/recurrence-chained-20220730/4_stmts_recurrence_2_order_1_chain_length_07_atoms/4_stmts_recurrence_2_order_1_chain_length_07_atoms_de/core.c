#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>
#include <assert.h>
#include <limits.h>
#include <math.h>
#include <string.h>

extern int n_arrs;
extern int size;

int core(double (*restrict A)[2097152], double (*restrict B)[2097152], double (*restrict C)[2097152], double (*restrict D)[2097152]) {

  for (int i = 2; i <= (size - 1) / n_arrs; i += 1) {
    (*B)[i] = (*B)[i - 2];
    (*C)[i] = (*C)[i - 1] + (*C)[i - 2];
    (*A)[i] = (*A)[i - 1] + (*A)[i - 2];
    (*D)[i] = 2 * (*D)[i - 1] + (*D)[i - 2];
  }
  return 0;
}
