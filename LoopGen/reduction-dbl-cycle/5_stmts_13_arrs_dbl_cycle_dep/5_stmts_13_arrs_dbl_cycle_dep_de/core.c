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

int core(double (*restrict Arr01)[645278], double (*restrict Arr02)[645278], double (*restrict Arr03)[645278], double (*restrict Arr04)[645278], double (*restrict Arr05)[645278], double (*restrict Arr06)[645278], double (*restrict Arr07)[645278], double (*restrict Arr08)[645278], double (*restrict Arr09)[645278], double (*restrict Arr10)[645278], double (*restrict Arr11)[645278], double (*restrict Arr12)[645278], double (*restrict Arr13)[645278]) {

  for (int i = 0; i <= (size - 1) / n_arrs; i += 1) {
    scalar1 = ((((scalar1 + scalar2) + (*Arr08)[i]) + (*Arr06)[i]) + (*Arr13)[i]) + (*Arr02)[i];
    scalar5 = ((((scalar5 + (*Arr01)[i]) + (*Arr03)[i]) + (*Arr09)[i]) + (*Arr07)[i]) + (*Arr04)[i];
    scalar3 = ((((scalar3 + (*Arr10)[i]) + (*Arr05)[i]) + (*Arr11)[i]) + (*Arr12)[i]) + (*Arr09)[i];
    scalar4 = ((((scalar4 + (*Arr05)[i]) + (*Arr02)[i]) + (*Arr03)[i]) + (*Arr07)[i]) + (*Arr10)[i];
    scalar2 = ((((scalar2 + scalar1) + (*Arr07)[i]) + (*Arr02)[i]) + (*Arr02)[i]) + (*Arr07)[i];
  }
  return 0;
}
