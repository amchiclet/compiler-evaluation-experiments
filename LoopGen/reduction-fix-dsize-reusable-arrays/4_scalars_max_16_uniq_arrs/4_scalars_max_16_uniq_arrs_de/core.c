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
extern double scalar4;
extern int size;

int core(double (*restrict Arr01)[524288], double (*restrict Arr03)[524288], double (*restrict Arr04)[524288], double (*restrict Arr06)[524288], double (*restrict Arr07)[524288], double (*restrict Arr08)[524288], double (*restrict Arr09)[524288], double (*restrict Arr10)[524288], double (*restrict Arr12)[524288], double (*restrict Arr13)[524288], double (*restrict Arr14)[524288], double (*restrict Arr15)[524288], double (*restrict Arr16)[524288]) {

  for (int i = 0; i <= (size - 1) / n_unique_arrs; i += 1) {
    scalar1 = ((((scalar1 + (*Arr13)[i]) + (*Arr01)[i]) + (*Arr04)[i]) + (*Arr13)[i]) + 0;
    scalar3 = ((((scalar3 + 0) + (*Arr10)[i]) + (*Arr15)[i]) + (*Arr16)[i]) + 0;
    ;
    scalar2 = ((((scalar2 + (*Arr07)[i]) + (*Arr14)[i]) + (*Arr03)[i]) + (*Arr12)[i]) + (*Arr08)[i];
    scalar4 = ((((scalar4 + (*Arr09)[i]) + 0) + (*Arr06)[i]) + (*Arr14)[i]) + (*Arr07)[i];
  }
  return 0;
}
