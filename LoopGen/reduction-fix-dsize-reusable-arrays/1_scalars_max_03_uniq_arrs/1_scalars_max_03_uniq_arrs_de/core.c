#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>
#include <assert.h>
#include <limits.h>
#include <math.h>
#include <string.h>

extern int n_unique_arrs;
extern double scalar1;
extern int size;

int core(double (*restrict Arr01)[8388608], double (*restrict Arr03)[8388608]) {

  for (int i = 0; i <= (size - 1) / n_unique_arrs; i += 1) {
    ;
    ;
    ;
    ;
    scalar1 = ((((scalar1 + 0) + (*Arr03)[i]) + (*Arr01)[i]) + 0) + (*Arr01)[i];
  }
  return 0;
}
