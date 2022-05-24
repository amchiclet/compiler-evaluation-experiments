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

int core(double (*restrict Arr01)[8388608], double (*restrict Arr03)[8388608], double (*restrict Arr04)[8388608], double (*restrict Arr05)[8388608], double (*restrict Arr06)[8388608], double (*restrict Arr07)[8388608], double (*restrict Arr08)[8388608], double (*restrict Arr10)[8388608], double (*restrict Arr12)[8388608], double (*restrict Arr20)[8388608]) {

  for (int i = 0; i <= (size - 1) / n_unique_arrs; i += 1) {
    scalar1 = ((((scalar1 + (*Arr12)[i]) + (*Arr06)[i]) + (*Arr01)[i]) + (*Arr08)[i]) + (*Arr12)[i];
    scalar4 = ((((scalar4 + (*Arr03)[i]) + (*Arr20)[i]) + (*Arr05)[i]) + (*Arr07)[i]) + (*Arr01)[i];
    scalar5 = ((((scalar5 + (*Arr07)[i]) + 0) + 0) + 0) + (*Arr04)[i];
    scalar2 = ((((scalar2 + 0) + (*Arr01)[i]) + (*Arr10)[i]) + (*Arr12)[i]) + 0;
    scalar3 = ((((scalar3 + (*Arr01)[i]) + (*Arr20)[i]) + (*Arr08)[i]) + (*Arr05)[i]) + (*Arr06)[i];
  }
  return 0;
}
