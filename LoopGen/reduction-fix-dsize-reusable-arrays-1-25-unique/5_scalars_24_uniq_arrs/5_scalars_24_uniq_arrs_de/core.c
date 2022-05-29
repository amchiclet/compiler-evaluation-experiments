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

int core(double (*restrict Arr01)[349526], double (*restrict Arr02)[349526], double (*restrict Arr03)[349526], double (*restrict Arr04)[349526], double (*restrict Arr05)[349526], double (*restrict Arr06)[349526], double (*restrict Arr07)[349526], double (*restrict Arr08)[349526], double (*restrict Arr09)[349526], double (*restrict Arr10)[349526], double (*restrict Arr11)[349526], double (*restrict Arr12)[349526], double (*restrict Arr13)[349526], double (*restrict Arr14)[349526], double (*restrict Arr15)[349526], double (*restrict Arr16)[349526], double (*restrict Arr17)[349526], double (*restrict Arr18)[349526], double (*restrict Arr19)[349526], double (*restrict Arr20)[349526], double (*restrict Arr21)[349526], double (*restrict Arr22)[349526], double (*restrict Arr23)[349526], double (*restrict Arr24)[349526]) {

  for (int i = 0; i <= (size - 1) / n_unique_arrs; i += 1) {
    scalar4 = ((((scalar4 + (*Arr19)[i]) + (*Arr02)[i]) + (*Arr16)[i]) + (*Arr06)[i]) + (*Arr13)[i];
    scalar5 = ((((scalar5 + (*Arr01)[i]) + (*Arr22)[i]) + (*Arr12)[i]) + (*Arr10)[i]) + (*Arr04)[i];
    scalar1 = ((((scalar1 + (*Arr17)[i]) + (*Arr14)[i]) + (*Arr09)[i]) + (*Arr07)[i]) + (*Arr23)[i];
    scalar2 = ((((scalar2 + (*Arr08)[i]) + (*Arr05)[i]) + (*Arr21)[i]) + (*Arr24)[i]) + (*Arr11)[i];
    scalar3 = ((((scalar3 + (*Arr03)[i]) + (*Arr20)[i]) + (*Arr18)[i]) + (*Arr15)[i]) + (*Arr09)[i];
  }
  return 0;
}
