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

int core(double (*restrict Arr01)[699051], double (*restrict Arr02)[699051], double (*restrict Arr03)[699051], double (*restrict Arr04)[699051], double (*restrict Arr07)[699051], double (*restrict Arr09)[699051], double (*restrict Arr11)[699051], double (*restrict Arr12)[699051]) {

  for (int i = 0; i <= (size - 1) / n_unique_arrs; i += 1) {
    ;
    scalar3 = ((((scalar3 + 0) + 0) + 0) + 0) + (*Arr07)[i];
    scalar2 = ((((scalar2 + (*Arr04)[i]) + (*Arr09)[i]) + (*Arr11)[i]) + (*Arr02)[i]) + 0;
    ;
    scalar1 = ((((scalar1 + (*Arr12)[i]) + (*Arr03)[i]) + (*Arr01)[i]) + (*Arr07)[i]) + (*Arr11)[i];
  }
  return 0;
}
