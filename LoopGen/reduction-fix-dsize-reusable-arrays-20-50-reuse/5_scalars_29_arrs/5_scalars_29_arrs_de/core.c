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
extern double scalar5;
extern int size;

int core(double (*restrict Arr01)[419431], double (*restrict Arr02)[419431], double (*restrict Arr03)[419431], double (*restrict Arr04)[419431], double (*restrict Arr05)[419431], double (*restrict Arr06)[419431], double (*restrict Arr07)[419431], double (*restrict Arr08)[419431], double (*restrict Arr09)[419431], double (*restrict Arr10)[419431], double (*restrict Arr11)[419431], double (*restrict Arr12)[419431], double (*restrict Arr13)[419431], double (*restrict Arr14)[419431], double (*restrict Arr15)[419431], double (*restrict Arr16)[419431], double (*restrict Arr17)[419431], double (*restrict Arr18)[419431], double (*restrict Arr19)[419431], double (*restrict Arr20)[419431]) {

  for (int i = 0; i <= (size - 1) / n_unique_arrs; i += 1) {
    scalar4 = (((((((((scalar4 + (*Arr15)[i]) + (*Arr12)[i]) + (*Arr05)[i]) + (*Arr07)[i]) + 0) + 0) + 0) + 0) + 0) + 0;
    scalar5 = (((((((((scalar5 + (*Arr04)[i]) + (*Arr17)[i]) + (*Arr02)[i]) + (*Arr11)[i]) + 0) + 0) + 0) + 0) + 0) + 0;
    scalar3 = (((((((((scalar3 + (*Arr13)[i]) + (*Arr19)[i]) + (*Arr16)[i]) + (*Arr06)[i]) + 0) + 0) + 0) + 0) + 0) + 0;
    scalar2 = (((((((((scalar2 + (*Arr10)[i]) + (*Arr08)[i]) + (*Arr20)[i]) + (*Arr14)[i]) + 0) + 0) + 0) + (*Arr01)[i]) + (*Arr12)[i]) + (*Arr02)[i];
    scalar1 = (((((((((scalar1 + (*Arr18)[i]) + (*Arr01)[i]) + (*Arr09)[i]) + (*Arr03)[i]) + (*Arr04)[i]) + (*Arr20)[i]) + (*Arr01)[i]) + (*Arr09)[i]) + (*Arr10)[i]) + (*Arr08)[i];
  }
  return 0;
}
