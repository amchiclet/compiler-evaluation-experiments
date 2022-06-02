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

int core(double (*restrict Arr01)[1677722], double (*restrict Arr02)[1677722], double (*restrict Arr03)[1677722], double (*restrict Arr04)[1677722], double (*restrict Arr05)[1677722]) {

  for (int i = 0; i <= (size - 1) / n_unique_arrs; i += 1) {
    scalar4 = ((scalar4 + (*Arr04)[i]) + (*Arr03)[i]) + (*Arr02)[i];
    scalar5 = ((scalar5 + (*Arr05)[i]) + (*Arr01)[i]) + (*Arr05)[i];
    scalar1 = ((scalar1 + (*Arr02)[i]) + (*Arr03)[i]) + (*Arr02)[i];
    scalar3 = ((scalar3 + (*Arr01)[i]) + (*Arr05)[i]) + (*Arr03)[i];
    scalar2 = ((scalar2 + (*Arr05)[i]) + (*Arr05)[i]) + (*Arr02)[i];
  }
  return 0;
}
