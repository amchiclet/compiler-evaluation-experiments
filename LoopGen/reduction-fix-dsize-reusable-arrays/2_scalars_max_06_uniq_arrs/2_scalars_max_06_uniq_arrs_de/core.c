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
extern double scalar2;
extern int size;

int core(double (*restrict Arr01)[1398102], double (*restrict Arr02)[1398102], double (*restrict Arr03)[1398102]) {

  for (int i = 0; i <= (size - 1) / n_unique_arrs; i += 1) {
    scalar2 = ((((scalar2 + 0) + (*Arr02)[i]) + (*Arr02)[i]) + (*Arr03)[i]) + (*Arr03)[i];
    ;
    scalar1 = ((((scalar1 + (*Arr01)[i]) + (*Arr02)[i]) + 0) + 0) + 0;
    ;
    ;
  }
  return 0;
}
