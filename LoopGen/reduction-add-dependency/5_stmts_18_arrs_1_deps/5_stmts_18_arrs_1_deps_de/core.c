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

int core(double (*restrict Arr01)[466034], double (*restrict Arr02)[466034], double (*restrict Arr03)[466034], double (*restrict Arr04)[466034], double (*restrict Arr05)[466034], double (*restrict Arr06)[466034], double (*restrict Arr07)[466034], double (*restrict Arr08)[466034], double (*restrict Arr09)[466034], double (*restrict Arr10)[466034], double (*restrict Arr11)[466034], double (*restrict Arr12)[466034], double (*restrict Arr13)[466034], double (*restrict Arr14)[466034], double (*restrict Arr15)[466034], double (*restrict Arr16)[466034], double (*restrict Arr17)[466034], double (*restrict Arr18)[466034]) {

  for (int i = 0; i <= (size - 1) / n_arrs; i += 1) {
    scalar1 = ((((scalar1 + scalar5) + (*Arr06)[i]) + (*Arr07)[i]) + (*Arr10)[i]) + (*Arr03)[i];
    scalar2 = ((((scalar2 + (*Arr04)[i]) + (*Arr08)[i]) + (*Arr11)[i]) + (*Arr15)[i]) + (*Arr12)[i];
    scalar3 = ((((scalar3 + (*Arr05)[i]) + (*Arr14)[i]) + (*Arr02)[i]) + (*Arr01)[i]) + (*Arr13)[i];
    scalar5 = ((((scalar5 + (*Arr18)[i]) + (*Arr09)[i]) + (*Arr16)[i]) + (*Arr17)[i]) + (*Arr12)[i];
    scalar4 = ((((scalar4 + (*Arr18)[i]) + (*Arr16)[i]) + (*Arr05)[i]) + (*Arr09)[i]) + (*Arr03)[i];
  }
  return 0;
}
