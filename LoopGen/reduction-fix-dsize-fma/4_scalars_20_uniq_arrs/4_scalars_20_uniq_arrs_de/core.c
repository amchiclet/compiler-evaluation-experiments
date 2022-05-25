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

int core(double (*restrict Arr01)[400000], double (*restrict Arr02)[400000], double (*restrict Arr03)[400000], double (*restrict Arr04)[400000], double (*restrict Arr05)[400000], double (*restrict Arr06)[400000], double (*restrict Arr07)[400000], double (*restrict Arr08)[400000], double (*restrict Arr09)[400000], double (*restrict Arr10)[400000], double (*restrict Arr11)[400000], double (*restrict Arr12)[400000], double (*restrict Arr13)[400000], double (*restrict Arr14)[400000], double (*restrict Arr15)[400000], double (*restrict Arr16)[400000], double (*restrict Arr17)[400000], double (*restrict Arr18)[400000], double (*restrict Arr19)[400000], double (*restrict Arr20)[400000]) {

  for (int i = 0; i <= (size - 1) / n_unique_arrs; i += 1) {
    scalar1 = (scalar1 + ((*Arr13)[i] * (*Arr15)[i] + (*Arr01)[i])) + (*Arr17)[i] * (*Arr12)[i];
    scalar3 = (scalar3 + ((*Arr09)[i] * (*Arr05)[i] + (*Arr08)[i])) + (*Arr07)[i] * (*Arr16)[i];
    scalar4 = (scalar4 + ((*Arr03)[i] * (*Arr06)[i] + (*Arr04)[i])) + (*Arr11)[i] * (*Arr02)[i];
    ;
    scalar2 = (scalar2 + ((*Arr20)[i] * (*Arr14)[i] + (*Arr19)[i])) + (*Arr18)[i] * (*Arr10)[i];
  }
  return 0;
}
