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

int core(double (*restrict Arr02)[8388608], double (*restrict Arr03)[8388608], double (*restrict Arr04)[8388608], double (*restrict Arr05)[8388608], double (*restrict Arr06)[8388608], double (*restrict Arr07)[8388608], double (*restrict Arr08)[8388608], double (*restrict Arr09)[8388608], double (*restrict Arr10)[8388608], double (*restrict Arr11)[8388608], double (*restrict Arr14)[8388608], double (*restrict Arr17)[8388608], double (*restrict Arr18)[8388608], double (*restrict Arr19)[8388608], double (*restrict Arr21)[8388608]) {

  for (int i = 0; i <= (size - 1) / n_unique_arrs; i += 1) {
    scalar3 = ((((scalar3 + (*Arr02)[i]) + (*Arr03)[i]) + (*Arr09)[i]) + (*Arr10)[i]) + (*Arr18)[i];
    scalar4 = ((((scalar4 + (*Arr11)[i]) + (*Arr04)[i]) + (*Arr17)[i]) + (*Arr08)[i]) + 0;
    scalar5 = ((((scalar5 + (*Arr06)[i]) + (*Arr03)[i]) + (*Arr14)[i]) + (*Arr10)[i]) + (*Arr10)[i];
    scalar1 = ((((scalar1 + (*Arr17)[i]) + (*Arr05)[i]) + (*Arr19)[i]) + (*Arr17)[i]) + (*Arr21)[i];
    scalar2 = ((((scalar2 + (*Arr07)[i]) + (*Arr18)[i]) + (*Arr04)[i]) + (*Arr14)[i]) + (*Arr21)[i];
  }
  return 0;
}
