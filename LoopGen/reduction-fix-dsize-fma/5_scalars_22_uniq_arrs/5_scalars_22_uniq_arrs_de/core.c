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

int core(double (*restrict Arr01)[363637], double (*restrict Arr02)[363637], double (*restrict Arr03)[363637], double (*restrict Arr04)[363637], double (*restrict Arr05)[363637], double (*restrict Arr06)[363637], double (*restrict Arr07)[363637], double (*restrict Arr08)[363637], double (*restrict Arr09)[363637], double (*restrict Arr10)[363637], double (*restrict Arr11)[363637], double (*restrict Arr12)[363637], double (*restrict Arr13)[363637], double (*restrict Arr14)[363637], double (*restrict Arr15)[363637], double (*restrict Arr16)[363637], double (*restrict Arr17)[363637], double (*restrict Arr18)[363637], double (*restrict Arr19)[363637], double (*restrict Arr20)[363637], double (*restrict Arr21)[363637], double (*restrict Arr22)[363637]) {

  for (int i = 0; i <= (size - 1) / n_unique_arrs; i += 1) {
    scalar4 = (scalar4 + ((*Arr21)[i] * (*Arr02)[i] + (*Arr16)[i])) + (*Arr11)[i] * (*Arr06)[i];
    scalar5 = (scalar5 + ((*Arr20)[i] * (*Arr03)[i] + (*Arr10)[i])) + (*Arr01)[i] * (*Arr19)[i];
    scalar3 = (scalar3 + ((*Arr14)[i] * (*Arr13)[i] + (*Arr04)[i])) + (*Arr22)[i] * (*Arr07)[i];
    scalar2 = (scalar2 + ((*Arr08)[i] * 0.7 + (*Arr05)[i])) + (*Arr15)[i] * (*Arr09)[i];
    scalar1 = (scalar1 + ((*Arr12)[i] * (*Arr17)[i] + 1.8)) + 2.9 * (*Arr18)[i];
  }
  return 0;
}
