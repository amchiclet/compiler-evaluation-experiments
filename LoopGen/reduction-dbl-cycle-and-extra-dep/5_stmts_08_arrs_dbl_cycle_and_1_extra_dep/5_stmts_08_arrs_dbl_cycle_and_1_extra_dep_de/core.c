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

int core(double (*restrict Arr01)[1048576], double (*restrict Arr02)[1048576], double (*restrict Arr03)[1048576], double (*restrict Arr04)[1048576], double (*restrict Arr05)[1048576], double (*restrict Arr06)[1048576], double (*restrict Arr07)[1048576], double (*restrict Arr08)[1048576]) {

  for (int i = 0; i <= (size - 1) / n_arrs; i += 1) {
    scalar5 = ((((scalar5 + (*Arr06)[i]) + (*Arr08)[i]) + (*Arr05)[i]) + (*Arr02)[i]) + (*Arr03)[i];
    scalar1 = ((((scalar1 + scalar2) + (*Arr04)[i]) + (*Arr07)[i]) + (*Arr01)[i]) + (*Arr03)[i];
    scalar4 = ((((scalar4 + (*Arr03)[i]) + (*Arr05)[i]) + (*Arr06)[i]) + (*Arr06)[i]) + (*Arr06)[i];
    scalar3 = ((((scalar3 + scalar5) + (*Arr02)[i]) + (*Arr06)[i]) + (*Arr01)[i]) + (*Arr01)[i];
    scalar2 = ((((scalar2 + scalar1) + (*Arr05)[i]) + (*Arr03)[i]) + (*Arr03)[i]) + (*Arr05)[i];
  }
  return 0;
}
