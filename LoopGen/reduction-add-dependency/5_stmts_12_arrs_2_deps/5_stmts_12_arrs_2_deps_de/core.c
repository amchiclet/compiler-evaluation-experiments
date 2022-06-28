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

int core(double (*restrict Arr01)[699051], double (*restrict Arr02)[699051], double (*restrict Arr03)[699051], double (*restrict Arr04)[699051], double (*restrict Arr05)[699051], double (*restrict Arr06)[699051], double (*restrict Arr07)[699051], double (*restrict Arr08)[699051], double (*restrict Arr09)[699051], double (*restrict Arr10)[699051], double (*restrict Arr11)[699051], double (*restrict Arr12)[699051]) {

  for (int i = 0; i <= (size - 1) / n_arrs; i += 1) {
    scalar5 = ((((scalar5 + (*Arr08)[i]) + (*Arr02)[i]) + (*Arr03)[i]) + (*Arr11)[i]) + (*Arr10)[i];
    scalar4 = ((((scalar4 + (*Arr07)[i]) + (*Arr06)[i]) + (*Arr12)[i]) + (*Arr01)[i]) + (*Arr05)[i];
    scalar2 = ((((scalar2 + scalar3) + (*Arr09)[i]) + (*Arr04)[i]) + (*Arr02)[i]) + (*Arr05)[i];
    scalar3 = ((((scalar3 + (*Arr03)[i]) + (*Arr06)[i]) + (*Arr02)[i]) + (*Arr03)[i]) + (*Arr11)[i];
    scalar1 = ((((scalar1 + scalar3) + (*Arr01)[i]) + (*Arr11)[i]) + (*Arr03)[i]) + (*Arr10)[i];
  }
  return 0;
}
