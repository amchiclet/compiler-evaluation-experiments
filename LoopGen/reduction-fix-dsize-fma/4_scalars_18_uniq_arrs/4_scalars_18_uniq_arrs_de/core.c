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

int core(double (*restrict Arr01)[444445], double (*restrict Arr02)[444445], double (*restrict Arr03)[444445], double (*restrict Arr04)[444445], double (*restrict Arr05)[444445], double (*restrict Arr06)[444445], double (*restrict Arr07)[444445], double (*restrict Arr08)[444445], double (*restrict Arr09)[444445], double (*restrict Arr10)[444445], double (*restrict Arr11)[444445], double (*restrict Arr12)[444445], double (*restrict Arr13)[444445], double (*restrict Arr14)[444445], double (*restrict Arr15)[444445], double (*restrict Arr16)[444445], double (*restrict Arr17)[444445], double (*restrict Arr18)[444445]) {

  for (int i = 0; i <= (size - 1) / n_unique_arrs; i += 1) {
    scalar1 = (scalar1 + ((*Arr17)[i] * (*Arr10)[i] + (*Arr04)[i])) + (*Arr06)[i] * (*Arr18)[i];
    scalar3 = (scalar3 + (1.8 * (*Arr13)[i] + (*Arr09)[i])) + (*Arr02)[i] * (*Arr03)[i];
    scalar2 = (scalar2 + ((*Arr14)[i] * (*Arr05)[i] + (*Arr07)[i])) + (*Arr12)[i] * (*Arr08)[i];
    scalar4 = (scalar4 + ((*Arr01)[i] * 0.7 + (*Arr15)[i])) + (*Arr16)[i] * (*Arr11)[i];
    ;
  }
  return 0;
}
