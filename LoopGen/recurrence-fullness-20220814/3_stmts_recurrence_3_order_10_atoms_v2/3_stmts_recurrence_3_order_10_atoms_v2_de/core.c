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
    (*C)[i] = (((((*C)[i - 3] + (*C)[i - 3]) + 0) + (*C)[i - 1]) + 0) + 0;
    (*A)[i] = (((((*A)[i - 3] + 0) + 0) + 0) + (*C)[i - 2]) + 0;
    (*B)[i] = (((((*B)[i - 3] + (*C)[i - 2]) + (*A)[i - 2]) + (*B)[i - 2]) + (*B)[i - 3]) + 0;
  }
  return 0;
}