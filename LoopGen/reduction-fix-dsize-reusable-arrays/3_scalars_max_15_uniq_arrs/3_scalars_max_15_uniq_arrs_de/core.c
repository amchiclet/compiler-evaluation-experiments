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

int core(double (*restrict Arr02)[8388608], double (*restrict Arr05)[8388608], double (*restrict Arr06)[8388608], double (*restrict Arr07)[8388608], double (*restrict Arr08)[8388608], double (*restrict Arr09)[8388608], double (*restrict Arr13)[8388608], double (*restrict Arr14)[8388608], double (*restrict Arr15)[8388608]) {

  for (int i = 0; i <= (size - 1) / n_unique_arrs; i += 1) {
    scalar3 = ((((scalar3 + (*Arr07)[i]) + (*Arr14)[i]) + (*Arr06)[i]) + (*Arr05)[i]) + (*Arr07)[i];
    scalar2 = ((((scalar2 + (*Arr02)[i]) + (*Arr02)[i]) + (*Arr09)[i]) + (*Arr15)[i]) + (*Arr08)[i];
    ;
    scalar1 = ((((scalar1 + (*Arr08)[i]) + (*Arr06)[i]) + (*Arr14)[i]) + (*Arr13)[i]) + (*Arr13)[i];
    ;
  }
  return 0;
}
