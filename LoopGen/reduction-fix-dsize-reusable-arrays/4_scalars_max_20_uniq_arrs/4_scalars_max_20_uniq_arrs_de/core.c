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

int core(double (*restrict Arr01)[8388608], double (*restrict Arr02)[8388608], double (*restrict Arr03)[8388608], double (*restrict Arr04)[8388608], double (*restrict Arr05)[8388608], double (*restrict Arr07)[8388608], double (*restrict Arr08)[8388608], double (*restrict Arr09)[8388608], double (*restrict Arr10)[8388608], double (*restrict Arr14)[8388608], double (*restrict Arr16)[8388608], double (*restrict Arr17)[8388608], double (*restrict Arr19)[8388608]) {

  for (int i = 0; i <= (size - 1) / n_unique_arrs; i += 1) {
    scalar4 = ((((scalar4 + (*Arr03)[i]) + (*Arr02)[i]) + (*Arr02)[i]) + (*Arr16)[i]) + (*Arr09)[i];
    scalar3 = ((((scalar3 + (*Arr01)[i]) + (*Arr17)[i]) + (*Arr19)[i]) + (*Arr19)[i]) + (*Arr07)[i];
    scalar1 = ((((scalar1 + (*Arr08)[i]) + (*Arr03)[i]) + (*Arr17)[i]) + (*Arr17)[i]) + (*Arr14)[i];
    ;
    scalar2 = ((((scalar2 + (*Arr17)[i]) + (*Arr10)[i]) + (*Arr04)[i]) + (*Arr05)[i]) + (*Arr14)[i];
  }
  return 0;
}
