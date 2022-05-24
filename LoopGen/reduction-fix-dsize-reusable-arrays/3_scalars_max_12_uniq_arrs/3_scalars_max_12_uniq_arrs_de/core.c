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
extern double scalar3;
extern int size;

int core(double (*restrict Arr01)[8388608], double (*restrict Arr02)[8388608], double (*restrict Arr03)[8388608], double (*restrict Arr04)[8388608], double (*restrict Arr07)[8388608], double (*restrict Arr09)[8388608], double (*restrict Arr11)[8388608], double (*restrict Arr12)[8388608]) {

  for (int i = 0; i <= (size - 1) / n_unique_arrs; i += 1) {
    ;
    scalar3 = ((((scalar3 + 0) + 0) + 0) + 0) + (*Arr07)[i];
    scalar2 = ((((scalar2 + (*Arr04)[i]) + (*Arr09)[i]) + (*Arr11)[i]) + (*Arr02)[i]) + 0;
    ;
    scalar1 = ((((scalar1 + (*Arr12)[i]) + (*Arr03)[i]) + (*Arr01)[i]) + (*Arr07)[i]) + (*Arr11)[i];
  }
  return 0;
}
