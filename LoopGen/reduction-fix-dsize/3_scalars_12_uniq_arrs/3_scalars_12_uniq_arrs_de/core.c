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

int core(double (*restrict Arr01)[666667], double (*restrict Arr02)[666667], double (*restrict Arr03)[666667], double (*restrict Arr04)[666667], double (*restrict Arr05)[666667], double (*restrict Arr06)[666667], double (*restrict Arr07)[666667], double (*restrict Arr08)[666667], double (*restrict Arr09)[666667], double (*restrict Arr10)[666667], double (*restrict Arr11)[666667], double (*restrict Arr12)[666667]) {

  for (int i = 0; i <= (size - 1) / n_unique_arrs; i += 1) {
    scalar3 = ((((scalar3 + (*Arr11)[i]) + (*Arr05)[i]) + (*Arr10)[i]) + (*Arr07)[i]) + (*Arr08)[i];
    scalar1 = ((((scalar1 + 0) + (*Arr01)[i]) + 0) + (*Arr12)[i]) + 0;
    scalar2 = ((((scalar2 + (*Arr06)[i]) + (*Arr09)[i]) + (*Arr03)[i]) + (*Arr02)[i]) + (*Arr04)[i];
    ;
    ;
  }
  return 0;
}
