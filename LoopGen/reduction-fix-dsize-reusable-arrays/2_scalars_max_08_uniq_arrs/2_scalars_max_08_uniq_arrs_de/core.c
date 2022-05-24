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

int core(double (*restrict Arr01)[8388608], double (*restrict Arr02)[8388608], double (*restrict Arr03)[8388608], double (*restrict Arr04)[8388608], double (*restrict Arr08)[8388608]) {

  for (int i = 0; i <= (size - 1) / n_unique_arrs; i += 1) {
    scalar2 = ((((scalar2 + (*Arr02)[i]) + (*Arr01)[i]) + 0) + (*Arr01)[i]) + (*Arr04)[i];
    scalar1 = ((((scalar1 + (*Arr03)[i]) + (*Arr02)[i]) + (*Arr08)[i]) + (*Arr04)[i]) + (*Arr01)[i];
    ;
    ;
    ;
  }
  return 0;
}
