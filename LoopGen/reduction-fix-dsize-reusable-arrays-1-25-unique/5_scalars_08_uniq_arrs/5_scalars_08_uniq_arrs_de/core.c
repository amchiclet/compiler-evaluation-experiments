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

int core(double (*restrict Arr01)[1048576], double (*restrict Arr02)[1048576], double (*restrict Arr03)[1048576], double (*restrict Arr04)[1048576], double (*restrict Arr05)[1048576], double (*restrict Arr06)[1048576], double (*restrict Arr07)[1048576], double (*restrict Arr08)[1048576]) {

  for (int i = 0; i <= (size - 1) / n_unique_arrs; i += 1) {
    scalar3 = ((((scalar3 + (*Arr05)[i]) + (*Arr02)[i]) + (*Arr03)[i]) + (*Arr08)[i]) + (*Arr06)[i];
    scalar1 = ((((scalar1 + (*Arr04)[i]) + (*Arr07)[i]) + (*Arr01)[i]) + (*Arr05)[i]) + (*Arr02)[i];
    scalar4 = ((((scalar4 + (*Arr08)[i]) + (*Arr04)[i]) + (*Arr01)[i]) + (*Arr05)[i]) + (*Arr03)[i];
    scalar2 = ((((scalar2 + (*Arr02)[i]) + (*Arr05)[i]) + (*Arr07)[i]) + (*Arr06)[i]) + (*Arr05)[i];
    scalar5 = ((((scalar5 + (*Arr07)[i]) + (*Arr02)[i]) + (*Arr02)[i]) + (*Arr08)[i]) + (*Arr08)[i];
  }
  return 0;
}