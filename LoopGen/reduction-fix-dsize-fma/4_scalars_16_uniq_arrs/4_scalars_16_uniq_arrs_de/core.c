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

int core(double (*restrict Arr01)[500000], double (*restrict Arr02)[500000], double (*restrict Arr03)[500000], double (*restrict Arr04)[500000], double (*restrict Arr05)[500000], double (*restrict Arr06)[500000], double (*restrict Arr07)[500000], double (*restrict Arr08)[500000], double (*restrict Arr09)[500000], double (*restrict Arr10)[500000], double (*restrict Arr11)[500000], double (*restrict Arr12)[500000], double (*restrict Arr13)[500000], double (*restrict Arr14)[500000], double (*restrict Arr15)[500000], double (*restrict Arr16)[500000]) {

  for (int i = 0; i <= (size - 1) / n_unique_arrs; i += 1) {
    scalar3 = (scalar3 + (0.7 * (*Arr13)[i] + 2.9)) + 4.0 * (*Arr02)[i];
    scalar2 = (scalar2 + ((*Arr11)[i] * (*Arr03)[i] + (*Arr15)[i])) + (*Arr12)[i] * (*Arr16)[i];
    scalar1 = (scalar1 + ((*Arr04)[i] * (*Arr10)[i] + (*Arr07)[i])) + (*Arr06)[i] * (*Arr14)[i];
    ;
    scalar4 = (scalar4 + (1.8 * (*Arr09)[i] + (*Arr05)[i])) + (*Arr08)[i] * (*Arr01)[i];
  }
  return 0;
}
