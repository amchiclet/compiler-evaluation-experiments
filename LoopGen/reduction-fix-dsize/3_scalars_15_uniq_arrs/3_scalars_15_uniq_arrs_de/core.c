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

int core(double (*restrict Arr01)[533334], double (*restrict Arr02)[533334], double (*restrict Arr03)[533334], double (*restrict Arr04)[533334], double (*restrict Arr05)[533334], double (*restrict Arr06)[533334], double (*restrict Arr07)[533334], double (*restrict Arr08)[533334], double (*restrict Arr09)[533334], double (*restrict Arr10)[533334], double (*restrict Arr11)[533334], double (*restrict Arr12)[533334], double (*restrict Arr13)[533334], double (*restrict Arr14)[533334], double (*restrict Arr15)[533334]) {

  for (int i = 0; i <= (size - 1) / n_unique_arrs; i += 1) {
    scalar3 = ((((scalar3 + (*Arr10)[i]) + (*Arr07)[i]) + (*Arr13)[i]) + (*Arr14)[i]) + (*Arr08)[i];
    scalar2 = ((((scalar2 + (*Arr12)[i]) + (*Arr11)[i]) + (*Arr06)[i]) + (*Arr15)[i]) + (*Arr04)[i];
    scalar1 = ((((scalar1 + (*Arr05)[i]) + (*Arr02)[i]) + (*Arr09)[i]) + (*Arr01)[i]) + (*Arr03)[i];
    ;
    ;
  }
  return 0;
}
