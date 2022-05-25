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

int core(double (*restrict Arr01)[470589], double (*restrict Arr02)[470589], double (*restrict Arr03)[470589], double (*restrict Arr04)[470589], double (*restrict Arr05)[470589], double (*restrict Arr06)[470589], double (*restrict Arr07)[470589], double (*restrict Arr08)[470589], double (*restrict Arr09)[470589], double (*restrict Arr10)[470589], double (*restrict Arr11)[470589], double (*restrict Arr12)[470589], double (*restrict Arr13)[470589], double (*restrict Arr14)[470589], double (*restrict Arr15)[470589], double (*restrict Arr16)[470589], double (*restrict Arr17)[470589]) {

  for (int i = 0; i <= (size - 1) / n_unique_arrs; i += 1) {
    scalar4 = (scalar4 + ((*Arr12)[i] * (*Arr15)[i] + (*Arr02)[i])) + 0.7 * (*Arr16)[i];
    scalar2 = (scalar2 + ((*Arr09)[i] * (*Arr01)[i] + (*Arr04)[i])) + (*Arr13)[i] * (*Arr06)[i];
    scalar3 = (scalar3 + ((*Arr03)[i] * (*Arr05)[i] + (*Arr10)[i])) + 1.8 * (*Arr11)[i];
    scalar1 = (scalar1 + ((*Arr07)[i] * (*Arr17)[i] + (*Arr08)[i])) + 2.9 * (*Arr14)[i];
    ;
  }
  return 0;
}
