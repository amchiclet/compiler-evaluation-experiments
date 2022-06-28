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

int core(double (*restrict Arr01)[559241], double (*restrict Arr02)[559241], double (*restrict Arr03)[559241], double (*restrict Arr04)[559241], double (*restrict Arr05)[559241], double (*restrict Arr06)[559241], double (*restrict Arr07)[559241], double (*restrict Arr08)[559241], double (*restrict Arr09)[559241], double (*restrict Arr10)[559241], double (*restrict Arr11)[559241], double (*restrict Arr12)[559241], double (*restrict Arr13)[559241], double (*restrict Arr14)[559241], double (*restrict Arr15)[559241]) {

  for (int i = 0; i <= (size - 1) / n_arrs; i += 1) {
    scalar5 = ((((scalar5 + (*Arr13)[i]) + (*Arr02)[i]) + (*Arr04)[i]) + (*Arr15)[i]) + (*Arr07)[i];
    scalar1 = ((((scalar1 + scalar2) + (*Arr06)[i]) + (*Arr14)[i]) + (*Arr10)[i]) + (*Arr12)[i];
    scalar2 = ((((scalar2 + (*Arr08)[i]) + (*Arr01)[i]) + (*Arr11)[i]) + (*Arr09)[i]) + (*Arr05)[i];
    scalar4 = ((((scalar4 + (*Arr03)[i]) + (*Arr02)[i]) + (*Arr10)[i]) + (*Arr08)[i]) + (*Arr06)[i];
    scalar3 = ((((scalar3 + (*Arr03)[i]) + (*Arr05)[i]) + (*Arr04)[i]) + (*Arr11)[i]) + (*Arr07)[i];
  }
  return 0;
}
