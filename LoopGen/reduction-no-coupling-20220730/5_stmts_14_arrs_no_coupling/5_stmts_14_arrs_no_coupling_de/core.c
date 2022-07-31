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

int core(double (*restrict Arr01)[599187], double (*restrict Arr02)[599187], double (*restrict Arr03)[599187], double (*restrict Arr04)[599187], double (*restrict Arr05)[599187], double (*restrict Arr06)[599187], double (*restrict Arr07)[599187], double (*restrict Arr08)[599187], double (*restrict Arr09)[599187], double (*restrict Arr10)[599187], double (*restrict Arr11)[599187], double (*restrict Arr12)[599187], double (*restrict Arr13)[599187], double (*restrict Arr14)[599187]) {

  for (int i = 0; i <= (size - 1) / n_arrs; i += 1) {
    scalar4 = ((((scalar4 + (*Arr01)[i]) + (*Arr05)[i]) + (*Arr08)[i]) + (*Arr09)[i]) + (*Arr12)[i];
    scalar3 = ((((scalar3 + (*Arr07)[i]) + (*Arr10)[i]) + (*Arr11)[i]) + (*Arr14)[i]) + (*Arr04)[i];
    scalar5 = ((((scalar5 + (*Arr03)[i]) + (*Arr13)[i]) + (*Arr02)[i]) + (*Arr06)[i]) + (*Arr09)[i];
    scalar2 = ((((scalar2 + (*Arr10)[i]) + (*Arr05)[i]) + (*Arr03)[i]) + (*Arr07)[i]) + (*Arr03)[i];
    scalar1 = ((((scalar1 + (*Arr03)[i]) + (*Arr13)[i]) + (*Arr04)[i]) + (*Arr06)[i]) + (*Arr09)[i];
  }
  return 0;
}
