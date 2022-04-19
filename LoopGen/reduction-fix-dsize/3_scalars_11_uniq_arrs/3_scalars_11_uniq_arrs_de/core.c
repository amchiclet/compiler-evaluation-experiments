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

int core(double (*restrict Arr01)[727273], double (*restrict Arr02)[727273], double (*restrict Arr03)[727273], double (*restrict Arr04)[727273], double (*restrict Arr05)[727273], double (*restrict Arr06)[727273], double (*restrict Arr07)[727273], double (*restrict Arr08)[727273], double (*restrict Arr09)[727273], double (*restrict Arr10)[727273], double (*restrict Arr11)[727273]) {

  for (int i = 0; i <= (size - 1) / n_unique_arrs; i += 1) {
    scalar1 = ((((scalar1 + (*Arr01)[i]) + (*Arr08)[i]) + 0) + (*Arr09)[i]) + (*Arr07)[i];
    ;
    scalar2 = ((((scalar2 + (*Arr02)[i]) + (*Arr06)[i]) + (*Arr03)[i]) + 0) + (*Arr04)[i];
    scalar3 = ((((scalar3 + 0) + (*Arr05)[i]) + (*Arr10)[i]) + (*Arr11)[i]) + 0;
    ;
  }
  return 0;
}
