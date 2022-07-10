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

int core(double (*restrict Arr01)[524288], double (*restrict Arr02)[524288], double (*restrict Arr03)[524288], double (*restrict Arr04)[524288], double (*restrict Arr05)[524288], double (*restrict Arr06)[524288], double (*restrict Arr07)[524288], double (*restrict Arr08)[524288], double (*restrict Arr09)[524288], double (*restrict Arr10)[524288], double (*restrict Arr11)[524288], double (*restrict Arr12)[524288], double (*restrict Arr13)[524288], double (*restrict Arr14)[524288], double (*restrict Arr15)[524288], double (*restrict Arr16)[524288]) {

  for (int i = 0; i <= (size - 1) / n_arrs; i += 1) {
    scalar3 = ((((scalar3 + scalar1) + (*Arr16)[i]) + (*Arr02)[i]) + (*Arr04)[i]) + (*Arr15)[i];
    scalar5 = ((((scalar5 + (*Arr03)[i]) + (*Arr08)[i]) + (*Arr05)[i]) + (*Arr14)[i]) + (*Arr07)[i];
    scalar1 = ((((scalar1 + scalar2) + (*Arr13)[i]) + (*Arr12)[i]) + (*Arr10)[i]) + (*Arr11)[i];
    scalar4 = ((((scalar4 + (*Arr01)[i]) + (*Arr09)[i]) + (*Arr06)[i]) + (*Arr06)[i]) + (*Arr08)[i];
    scalar2 = ((((scalar2 + scalar3) + (*Arr15)[i]) + (*Arr11)[i]) + (*Arr05)[i]) + (*Arr12)[i];
  }
  return 0;
}
