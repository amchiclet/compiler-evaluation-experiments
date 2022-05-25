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

int core(double (*restrict Arr02)[349526], double (*restrict Arr03)[349526], double (*restrict Arr04)[349526], double (*restrict Arr05)[349526], double (*restrict Arr06)[349526], double (*restrict Arr07)[349526], double (*restrict Arr08)[349526], double (*restrict Arr09)[349526], double (*restrict Arr10)[349526], double (*restrict Arr11)[349526], double (*restrict Arr14)[349526], double (*restrict Arr17)[349526], double (*restrict Arr18)[349526], double (*restrict Arr19)[349526], double (*restrict Arr21)[349526]) {

  for (int i = 0; i <= (size - 1) / n_unique_arrs; i += 1) {
    scalar3 = ((((scalar3 + (*Arr02)[i]) + (*Arr03)[i]) + (*Arr09)[i]) + (*Arr10)[i]) + (*Arr18)[i];
    scalar4 = ((((scalar4 + (*Arr11)[i]) + (*Arr04)[i]) + (*Arr17)[i]) + (*Arr08)[i]) + 0;
    scalar5 = ((((scalar5 + (*Arr06)[i]) + (*Arr03)[i]) + (*Arr14)[i]) + (*Arr10)[i]) + (*Arr10)[i];
    scalar1 = ((((scalar1 + (*Arr17)[i]) + (*Arr05)[i]) + (*Arr19)[i]) + (*Arr17)[i]) + (*Arr21)[i];
    scalar2 = ((((scalar2 + (*Arr07)[i]) + (*Arr18)[i]) + (*Arr04)[i]) + (*Arr14)[i]) + (*Arr21)[i];
  }
  return 0;
}
