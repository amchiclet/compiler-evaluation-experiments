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
extern int size;

int core(double (*restrict Arr01)[1600000], double (*restrict Arr02)[1600000], double (*restrict Arr03)[1600000], double (*restrict Arr04)[1600000], double (*restrict Arr05)[1600000]) {

  for (int i = 0; i <= (size - 1) / n_unique_arrs; i += 1) {
    scalar1 = (scalar1 + ((*Arr02)[i] * (*Arr03)[i] + (*Arr01)[i])) + (*Arr04)[i] * (*Arr05)[i];
    ;
    ;
    ;
    ;
  }
  return 0;
}
