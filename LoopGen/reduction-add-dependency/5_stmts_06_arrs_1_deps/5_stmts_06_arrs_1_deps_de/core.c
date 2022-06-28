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

int core(double (*restrict Arr01)[1398102], double (*restrict Arr02)[1398102], double (*restrict Arr03)[1398102], double (*restrict Arr04)[1398102], double (*restrict Arr05)[1398102], double (*restrict Arr06)[1398102]) {

  for (int i = 0; i <= (size - 1) / n_arrs; i += 1) {
    scalar3 = ((((scalar3 + (*Arr01)[i]) + (*Arr06)[i]) + (*Arr03)[i]) + (*Arr02)[i]) + (*Arr04)[i];
    scalar4 = ((((scalar4 + (*Arr05)[i]) + (*Arr03)[i]) + (*Arr03)[i]) + (*Arr05)[i]) + (*Arr02)[i];
    scalar5 = ((((scalar5 + (*Arr05)[i]) + (*Arr05)[i]) + (*Arr06)[i]) + (*Arr02)[i]) + (*Arr05)[i];
    scalar1 = ((((scalar1 + scalar4) + (*Arr01)[i]) + (*Arr04)[i]) + (*Arr06)[i]) + (*Arr05)[i];
    scalar2 = ((((scalar2 + (*Arr04)[i]) + (*Arr06)[i]) + (*Arr03)[i]) + (*Arr03)[i]) + (*Arr04)[i];
  }
  return 0;
}
