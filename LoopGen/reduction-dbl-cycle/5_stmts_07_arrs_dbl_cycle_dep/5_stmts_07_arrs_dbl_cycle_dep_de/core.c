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

int core(double (*restrict Arr01)[1198373], double (*restrict Arr02)[1198373], double (*restrict Arr03)[1198373], double (*restrict Arr04)[1198373], double (*restrict Arr05)[1198373], double (*restrict Arr06)[1198373], double (*restrict Arr07)[1198373]) {

  for (int i = 0; i <= (size - 1) / n_arrs; i += 1) {
    scalar4 = ((((scalar4 + (*Arr06)[i]) + (*Arr01)[i]) + (*Arr07)[i]) + (*Arr02)[i]) + (*Arr03)[i];
    scalar3 = ((((scalar3 + (*Arr04)[i]) + (*Arr05)[i]) + (*Arr07)[i]) + (*Arr03)[i]) + (*Arr03)[i];
    scalar1 = ((((scalar1 + scalar2) + (*Arr06)[i]) + (*Arr02)[i]) + (*Arr01)[i]) + (*Arr04)[i];
    scalar2 = ((((scalar2 + scalar1) + (*Arr07)[i]) + (*Arr04)[i]) + (*Arr06)[i]) + (*Arr01)[i];
    scalar5 = ((((scalar5 + (*Arr01)[i]) + (*Arr03)[i]) + (*Arr04)[i]) + (*Arr07)[i]) + (*Arr07)[i];
  }
  return 0;
}
