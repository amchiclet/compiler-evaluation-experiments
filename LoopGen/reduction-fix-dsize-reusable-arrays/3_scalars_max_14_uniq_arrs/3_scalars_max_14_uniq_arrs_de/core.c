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
extern int size;

int core(double (*restrict Arr01)[8388608], double (*restrict Arr02)[8388608], double (*restrict Arr03)[8388608], double (*restrict Arr05)[8388608], double (*restrict Arr06)[8388608], double (*restrict Arr07)[8388608], double (*restrict Arr10)[8388608], double (*restrict Arr12)[8388608], double (*restrict Arr13)[8388608]) {

  for (int i = 0; i <= (size - 1) / n_unique_arrs; i += 1) {
    ;
    scalar3 = ((((scalar3 + (*Arr07)[i]) + (*Arr10)[i]) + (*Arr05)[i]) + (*Arr01)[i]) + (*Arr03)[i];
    ;
    scalar1 = ((((scalar1 + (*Arr03)[i]) + (*Arr05)[i]) + (*Arr06)[i]) + (*Arr06)[i]) + (*Arr13)[i];
    scalar2 = ((((scalar2 + (*Arr06)[i]) + (*Arr12)[i]) + (*Arr02)[i]) + (*Arr06)[i]) + (*Arr13)[i];
  }
  return 0;
}
