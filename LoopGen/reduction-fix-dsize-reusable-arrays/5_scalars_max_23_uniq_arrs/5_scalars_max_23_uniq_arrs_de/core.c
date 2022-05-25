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

int core(double (*restrict Arr01)[364723], double (*restrict Arr03)[364723], double (*restrict Arr05)[364723], double (*restrict Arr06)[364723], double (*restrict Arr07)[364723], double (*restrict Arr08)[364723], double (*restrict Arr10)[364723], double (*restrict Arr11)[364723], double (*restrict Arr12)[364723], double (*restrict Arr13)[364723], double (*restrict Arr14)[364723], double (*restrict Arr15)[364723], double (*restrict Arr16)[364723], double (*restrict Arr17)[364723], double (*restrict Arr20)[364723], double (*restrict Arr21)[364723], double (*restrict Arr23)[364723]) {

  for (int i = 0; i <= (size - 1) / n_unique_arrs; i += 1) {
    scalar3 = ((((scalar3 + (*Arr13)[i]) + (*Arr06)[i]) + 0) + (*Arr14)[i]) + (*Arr14)[i];
    scalar1 = ((((scalar1 + (*Arr06)[i]) + (*Arr08)[i]) + (*Arr15)[i]) + (*Arr11)[i]) + (*Arr17)[i];
    scalar5 = ((((scalar5 + (*Arr05)[i]) + (*Arr12)[i]) + (*Arr15)[i]) + (*Arr21)[i]) + (*Arr21)[i];
    scalar2 = ((((scalar2 + (*Arr03)[i]) + (*Arr16)[i]) + 0) + (*Arr07)[i]) + (*Arr10)[i];
    scalar4 = ((((scalar4 + (*Arr01)[i]) + (*Arr23)[i]) + (*Arr15)[i]) + (*Arr20)[i]) + (*Arr15)[i];
  }
  return 0;
}
