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

int core(double (*restrict Arr01)[493448], double (*restrict Arr02)[493448], double (*restrict Arr05)[493448], double (*restrict Arr07)[493448], double (*restrict Arr08)[493448], double (*restrict Arr09)[493448], double (*restrict Arr11)[493448], double (*restrict Arr13)[493448], double (*restrict Arr14)[493448], double (*restrict Arr16)[493448], double (*restrict Arr17)[493448]) {

  for (int i = 0; i <= (size - 1) / n_unique_arrs; i += 1) {
    ;
    scalar2 = ((((scalar2 + 0) + (*Arr13)[i]) + (*Arr14)[i]) + (*Arr17)[i]) + (*Arr16)[i];
    scalar1 = ((((scalar1 + (*Arr11)[i]) + (*Arr16)[i]) + (*Arr16)[i]) + (*Arr07)[i]) + 0;
    scalar4 = ((((scalar4 + 0) + (*Arr08)[i]) + (*Arr01)[i]) + (*Arr11)[i]) + (*Arr11)[i];
    scalar3 = ((((scalar3 + (*Arr11)[i]) + (*Arr02)[i]) + (*Arr17)[i]) + (*Arr05)[i]) + (*Arr09)[i];
  }
  return 0;
}
