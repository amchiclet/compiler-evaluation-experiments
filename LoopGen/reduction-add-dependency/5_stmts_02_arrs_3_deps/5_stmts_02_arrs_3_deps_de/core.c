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
extern double scalar1;
extern double scalar2;
extern double scalar3;
extern double scalar4;
extern double scalar5;
extern int size;

int core(double (*restrict Arr01)[4194304], double (*restrict Arr02)[4194304]) {

  for (int i = 0; i <= (size - 1) / n_arrs; i += 1) {
    scalar4 = ((((scalar4 + (*Arr02)[i]) + (*Arr01)[i]) + (*Arr01)[i]) + (*Arr01)[i]) + (*Arr02)[i];
    scalar3 = ((((scalar3 + scalar1) + (*Arr02)[i]) + (*Arr01)[i]) + (*Arr01)[i]) + (*Arr02)[i];
    scalar1 = ((((scalar1 + scalar3) + (*Arr02)[i]) + (*Arr01)[i]) + (*Arr02)[i]) + (*Arr01)[i];
    scalar2 = ((((scalar2 + scalar1) + (*Arr02)[i]) + (*Arr01)[i]) + (*Arr01)[i]) + (*Arr02)[i];
    scalar5 = ((((scalar5 + (*Arr01)[i]) + (*Arr01)[i]) + (*Arr01)[i]) + (*Arr01)[i]) + (*Arr02)[i];
  }
  return 0;
}
