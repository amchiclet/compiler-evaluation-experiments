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

int core(double (*restrict A)[2796203], double (*restrict B)[2796203], double (*restrict C)[2796203]) {

  for (int i = 2; i <= (size - 1) / n_arrs; i += 1) {
    (*B)[i] = (*B)[i - 2] + (*B)[i - 1];
    (*A)[i] = (*A)[i - 2];
    (*C)[i] = (*C)[i - 2];
  }
  return 0;
}
