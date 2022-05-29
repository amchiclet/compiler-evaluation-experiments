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

int core(double (*restrict Arr01)[838861], double (*restrict Arr02)[838861], double (*restrict Arr03)[838861], double (*restrict Arr04)[838861], double (*restrict Arr05)[838861], double (*restrict Arr06)[838861], double (*restrict Arr07)[838861], double (*restrict Arr08)[838861], double (*restrict Arr09)[838861], double (*restrict Arr10)[838861]) {

  for (int i = 0; i <= (size - 1) / n_unique_arrs; i += 1) {
    scalar5 = ((((scalar5 + (*Arr06)[i]) + (*Arr09)[i]) + (*Arr10)[i]) + (*Arr07)[i]) + (*Arr08)[i];
    scalar4 = ((((scalar4 + (*Arr02)[i]) + (*Arr03)[i]) + (*Arr01)[i]) + (*Arr05)[i]) + (*Arr04)[i];
    scalar3 = ((((scalar3 + (*Arr06)[i]) + (*Arr01)[i]) + (*Arr09)[i]) + (*Arr03)[i]) + (*Arr05)[i];
    scalar2 = ((((scalar2 + (*Arr10)[i]) + (*Arr03)[i]) + (*Arr07)[i]) + (*Arr10)[i]) + (*Arr05)[i];
    scalar1 = ((((scalar1 + (*Arr08)[i]) + (*Arr02)[i]) + (*Arr02)[i]) + (*Arr09)[i]) + (*Arr01)[i];
  }
  return 0;
}
