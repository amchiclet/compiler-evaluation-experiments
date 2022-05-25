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

int core(double (*restrict Arr01)[380953], double (*restrict Arr02)[380953], double (*restrict Arr03)[380953], double (*restrict Arr04)[380953], double (*restrict Arr05)[380953], double (*restrict Arr06)[380953], double (*restrict Arr07)[380953], double (*restrict Arr08)[380953], double (*restrict Arr09)[380953], double (*restrict Arr10)[380953], double (*restrict Arr11)[380953], double (*restrict Arr12)[380953], double (*restrict Arr13)[380953], double (*restrict Arr14)[380953], double (*restrict Arr15)[380953], double (*restrict Arr16)[380953], double (*restrict Arr17)[380953], double (*restrict Arr18)[380953], double (*restrict Arr19)[380953], double (*restrict Arr20)[380953], double (*restrict Arr21)[380953]) {

  for (int i = 0; i <= (size - 1) / n_unique_arrs; i += 1) {
    scalar4 = (scalar4 + ((*Arr21)[i] * (*Arr01)[i] + (*Arr05)[i])) + (*Arr11)[i] * (*Arr03)[i];
    scalar2 = (scalar2 + ((*Arr02)[i] * (*Arr14)[i] + (*Arr19)[i])) + 4.0 * (*Arr20)[i];
    scalar5 = (scalar5 + ((*Arr13)[i] * (*Arr06)[i] + 1.8)) + (*Arr10)[i] * (*Arr15)[i];
    scalar3 = (scalar3 + ((*Arr12)[i] * (*Arr09)[i] + (*Arr07)[i])) + (*Arr04)[i] * (*Arr08)[i];
    scalar1 = (scalar1 + ((*Arr18)[i] * 0.7 + 2.9)) + (*Arr17)[i] * (*Arr16)[i];
  }
  return 0;
}
