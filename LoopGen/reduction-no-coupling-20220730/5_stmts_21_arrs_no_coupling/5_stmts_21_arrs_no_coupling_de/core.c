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

int core(double (*restrict Arr01)[399458], double (*restrict Arr02)[399458], double (*restrict Arr03)[399458], double (*restrict Arr04)[399458], double (*restrict Arr05)[399458], double (*restrict Arr06)[399458], double (*restrict Arr07)[399458], double (*restrict Arr08)[399458], double (*restrict Arr09)[399458], double (*restrict Arr10)[399458], double (*restrict Arr11)[399458], double (*restrict Arr12)[399458], double (*restrict Arr13)[399458], double (*restrict Arr14)[399458], double (*restrict Arr15)[399458], double (*restrict Arr16)[399458], double (*restrict Arr17)[399458], double (*restrict Arr18)[399458], double (*restrict Arr19)[399458], double (*restrict Arr20)[399458], double (*restrict Arr21)[399458]) {

  for (int i = 0; i <= (size - 1) / n_arrs; i += 1) {
    scalar2 = ((((scalar2 + (*Arr05)[i]) + (*Arr08)[i]) + (*Arr18)[i]) + (*Arr09)[i]) + (*Arr11)[i];
    scalar5 = ((((scalar5 + (*Arr06)[i]) + (*Arr20)[i]) + (*Arr04)[i]) + (*Arr21)[i]) + (*Arr13)[i];
    scalar1 = ((((scalar1 + (*Arr12)[i]) + (*Arr19)[i]) + (*Arr03)[i]) + (*Arr17)[i]) + (*Arr01)[i];
    scalar3 = ((((scalar3 + (*Arr15)[i]) + (*Arr02)[i]) + (*Arr14)[i]) + (*Arr10)[i]) + (*Arr16)[i];
    scalar4 = ((((scalar4 + (*Arr07)[i]) + (*Arr01)[i]) + (*Arr08)[i]) + (*Arr18)[i]) + (*Arr21)[i];
  }
  return 0;
}
