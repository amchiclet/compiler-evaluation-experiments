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

  for (int i = 3; i <= (size - 1) / n_arrs; i += 1) {
    (*B)[i] = (((((*B)[i - 3] + 0) + 0) + 0) + 0) + 0;
    (*A)[i] = (((((*A)[i - 3] + 0) + (*A)[i - 2]) + 0) + 0) + 0;
    (*C)[i] = (((((*C)[i - 3] + (*A)[i - 2]) + (*A)[i - 3]) + 0) + 0) + (*A)[i - 1];
  }
  return 0;
}