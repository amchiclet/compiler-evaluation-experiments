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

int core(double (*restrict Arr01)[421053], double (*restrict Arr02)[421053], double (*restrict Arr03)[421053], double (*restrict Arr04)[421053], double (*restrict Arr05)[421053], double (*restrict Arr06)[421053], double (*restrict Arr07)[421053], double (*restrict Arr08)[421053], double (*restrict Arr09)[421053], double (*restrict Arr10)[421053], double (*restrict Arr11)[421053], double (*restrict Arr12)[421053], double (*restrict Arr13)[421053], double (*restrict Arr14)[421053], double (*restrict Arr15)[421053], double (*restrict Arr16)[421053], double (*restrict Arr17)[421053], double (*restrict Arr18)[421053], double (*restrict Arr19)[421053]) {

  for (int i = 0; i <= (size - 1) / n_unique_arrs; i += 1) {
    scalar1 = (scalar1 + ((*Arr04)[i] * (*Arr17)[i] + (*Arr13)[i])) + (*Arr10)[i] * (*Arr06)[i];
    scalar3 = (scalar3 + ((*Arr01)[i] * (*Arr07)[i] + (*Arr11)[i])) + (*Arr12)[i] * (*Arr16)[i];
    scalar2 = (scalar2 + ((*Arr09)[i] * (*Arr14)[i] + (*Arr18)[i])) + (*Arr03)[i] * (*Arr19)[i];
    scalar4 = (scalar4 + ((*Arr02)[i] * (*Arr05)[i] + 0.7)) + (*Arr15)[i] * (*Arr08)[i];
    ;
  }
  return 0;
}
