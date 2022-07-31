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

int core(double (*restrict Arr01)[2097152], double (*restrict Arr02)[2097152], double (*restrict Arr03)[2097152], double (*restrict Arr04)[2097152]) {

  for (int i = 0; i <= (size - 1) / n_arrs; i += 1) {
    scalar1 = ((((scalar1 + (*Arr02)[i]) + (*Arr04)[i]) + (*Arr01)[i]) + (*Arr03)[i]) + (*Arr02)[i];
    scalar2 = ((((scalar2 + (*Arr01)[i]) + (*Arr01)[i]) + (*Arr04)[i]) + (*Arr01)[i]) + (*Arr03)[i];
    scalar5 = ((((scalar5 + (*Arr01)[i]) + (*Arr02)[i]) + (*Arr01)[i]) + (*Arr03)[i]) + (*Arr03)[i];
    scalar3 = ((((scalar3 + (*Arr04)[i]) + (*Arr02)[i]) + (*Arr01)[i]) + (*Arr04)[i]) + (*Arr01)[i];
    scalar4 = ((((scalar4 + (*Arr01)[i]) + (*Arr04)[i]) + (*Arr02)[i]) + (*Arr03)[i]) + (*Arr03)[i];
  }
  return 0;
}
