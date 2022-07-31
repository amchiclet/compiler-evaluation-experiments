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

int core(double (*restrict Arr01)[381301], double (*restrict Arr02)[381301], double (*restrict Arr03)[381301], double (*restrict Arr04)[381301], double (*restrict Arr05)[381301], double (*restrict Arr06)[381301], double (*restrict Arr07)[381301], double (*restrict Arr08)[381301], double (*restrict Arr09)[381301], double (*restrict Arr10)[381301], double (*restrict Arr11)[381301], double (*restrict Arr12)[381301], double (*restrict Arr13)[381301], double (*restrict Arr14)[381301], double (*restrict Arr15)[381301], double (*restrict Arr16)[381301], double (*restrict Arr17)[381301], double (*restrict Arr18)[381301], double (*restrict Arr19)[381301], double (*restrict Arr20)[381301], double (*restrict Arr21)[381301], double (*restrict Arr22)[381301]) {

  for (int i = 0; i <= (size - 1) / n_arrs; i += 1) {
    scalar3 = ((((scalar3 + (*Arr08)[i]) + (*Arr02)[i]) + (*Arr01)[i]) + (*Arr11)[i]) + (*Arr15)[i];
    scalar1 = ((((scalar1 + (*Arr05)[i]) + (*Arr04)[i]) + (*Arr12)[i]) + (*Arr19)[i]) + (*Arr14)[i];
    scalar4 = ((((scalar4 + (*Arr07)[i]) + (*Arr10)[i]) + (*Arr20)[i]) + (*Arr18)[i]) + (*Arr09)[i];
    scalar2 = ((((scalar2 + (*Arr13)[i]) + (*Arr16)[i]) + (*Arr06)[i]) + (*Arr21)[i]) + (*Arr22)[i];
    scalar5 = ((((scalar5 + (*Arr17)[i]) + (*Arr03)[i]) + (*Arr01)[i]) + (*Arr14)[i]) + (*Arr09)[i];
  }
  return 0;
}
