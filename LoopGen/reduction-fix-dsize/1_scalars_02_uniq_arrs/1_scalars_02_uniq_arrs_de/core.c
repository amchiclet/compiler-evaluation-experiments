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

int core(double (*restrict Arr01)[4000000], double (*restrict Arr02)[4000000]) {

  for (int i = 0; i <= (size - 1) / n_unique_arrs; i += 1) {
    ;
    ;
    ;
    scalar1 = ((((scalar1 + (*Arr01)[i]) + (*Arr02)[i]) + 0) + 0) + 0;
    ;
  }
  return 0;
}
