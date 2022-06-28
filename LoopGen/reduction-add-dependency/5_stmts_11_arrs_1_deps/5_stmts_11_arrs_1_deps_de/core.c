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

int core(double (*restrict Arr01)[762601], double (*restrict Arr02)[762601], double (*restrict Arr03)[762601], double (*restrict Arr04)[762601], double (*restrict Arr05)[762601], double (*restrict Arr06)[762601], double (*restrict Arr07)[762601], double (*restrict Arr08)[762601], double (*restrict Arr09)[762601], double (*restrict Arr10)[762601], double (*restrict Arr11)[762601]) {

  for (int i = 0; i <= (size - 1) / n_arrs; i += 1) {
    scalar2 = ((((scalar2 + (*Arr01)[i]) + (*Arr02)[i]) + (*Arr04)[i]) + (*Arr06)[i]) + (*Arr11)[i];
    scalar1 = ((((scalar1 + scalar2) + (*Arr05)[i]) + (*Arr09)[i]) + (*Arr03)[i]) + (*Arr08)[i];
    scalar5 = ((((scalar5 + (*Arr10)[i]) + (*Arr07)[i]) + (*Arr04)[i]) + (*Arr03)[i]) + (*Arr06)[i];
    scalar4 = ((((scalar4 + (*Arr09)[i]) + (*Arr04)[i]) + (*Arr09)[i]) + (*Arr07)[i]) + (*Arr02)[i];
    scalar3 = ((((scalar3 + (*Arr03)[i]) + (*Arr07)[i]) + (*Arr10)[i]) + (*Arr11)[i]) + (*Arr06)[i];
  }
  return 0;
}
