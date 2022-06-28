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

int core(double (*restrict Arr01)[493448], double (*restrict Arr02)[493448], double (*restrict Arr03)[493448], double (*restrict Arr04)[493448], double (*restrict Arr05)[493448], double (*restrict Arr06)[493448], double (*restrict Arr07)[493448], double (*restrict Arr08)[493448], double (*restrict Arr09)[493448], double (*restrict Arr10)[493448], double (*restrict Arr11)[493448], double (*restrict Arr12)[493448], double (*restrict Arr13)[493448], double (*restrict Arr14)[493448], double (*restrict Arr15)[493448], double (*restrict Arr16)[493448], double (*restrict Arr17)[493448]) {

  for (int i = 0; i <= (size - 1) / n_arrs; i += 1) {
    scalar4 = ((((scalar4 + (*Arr12)[i]) + (*Arr06)[i]) + (*Arr07)[i]) + (*Arr05)[i]) + (*Arr11)[i];
    scalar1 = ((((scalar1 + scalar2) + (*Arr13)[i]) + (*Arr10)[i]) + (*Arr01)[i]) + (*Arr08)[i];
    scalar3 = ((((scalar3 + (*Arr17)[i]) + (*Arr15)[i]) + (*Arr16)[i]) + (*Arr04)[i]) + (*Arr03)[i];
    scalar5 = ((((scalar5 + (*Arr02)[i]) + (*Arr14)[i]) + (*Arr09)[i]) + (*Arr13)[i]) + (*Arr10)[i];
    scalar2 = ((((scalar2 + scalar1) + (*Arr16)[i]) + (*Arr07)[i]) + (*Arr01)[i]) + (*Arr15)[i];
  }
  return 0;
}
