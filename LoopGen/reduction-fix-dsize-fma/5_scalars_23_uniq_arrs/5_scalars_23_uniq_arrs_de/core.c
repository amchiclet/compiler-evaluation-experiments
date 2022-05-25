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

int core(double (*restrict Arr01)[347827], double (*restrict Arr02)[347827], double (*restrict Arr03)[347827], double (*restrict Arr04)[347827], double (*restrict Arr05)[347827], double (*restrict Arr06)[347827], double (*restrict Arr07)[347827], double (*restrict Arr08)[347827], double (*restrict Arr09)[347827], double (*restrict Arr10)[347827], double (*restrict Arr11)[347827], double (*restrict Arr12)[347827], double (*restrict Arr13)[347827], double (*restrict Arr14)[347827], double (*restrict Arr15)[347827], double (*restrict Arr16)[347827], double (*restrict Arr17)[347827], double (*restrict Arr18)[347827], double (*restrict Arr19)[347827], double (*restrict Arr20)[347827], double (*restrict Arr21)[347827], double (*restrict Arr22)[347827], double (*restrict Arr23)[347827]) {

  for (int i = 0; i <= (size - 1) / n_unique_arrs; i += 1) {
    scalar5 = (scalar5 + ((*Arr21)[i] * (*Arr03)[i] + (*Arr07)[i])) + (*Arr14)[i] * (*Arr02)[i];
    scalar1 = (scalar1 + ((*Arr09)[i] * (*Arr12)[i] + (*Arr16)[i])) + (*Arr05)[i] * (*Arr18)[i];
    scalar3 = (scalar3 + ((*Arr23)[i] * (*Arr11)[i] + (*Arr15)[i])) + (*Arr19)[i] * (*Arr01)[i];
    scalar2 = (scalar2 + (0.7 * 1.8 + (*Arr20)[i])) + (*Arr13)[i] * (*Arr10)[i];
    scalar4 = (scalar4 + ((*Arr17)[i] * (*Arr08)[i] + (*Arr22)[i])) + (*Arr06)[i] * (*Arr04)[i];
  }
  return 0;
}
