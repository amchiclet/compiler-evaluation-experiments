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
    (*D)[i] = 1 * (*D)[i - 1] + 2 * (*D)[i - 2];
    (*C)[i] = (0 * (*C)[i - 1] + 1 * (*C)[i - 2]) + 0;
    (*B)[i] = (1 * (*B)[i - 1] + 0 * (*B)[i - 2]) + 0;
    (*A)[i] = (2 * (*A)[i - 1] + 1 * (*A)[i - 2]) + 0;
  }
  return 0;
}
