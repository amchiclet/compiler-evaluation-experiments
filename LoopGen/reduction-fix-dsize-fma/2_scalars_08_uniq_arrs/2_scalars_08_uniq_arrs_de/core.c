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
extern int size;

int core(double (*restrict Arr01)[1000000], double (*restrict Arr02)[1000000], double (*restrict Arr03)[1000000], double (*restrict Arr04)[1000000], double (*restrict Arr05)[1000000], double (*restrict Arr06)[1000000], double (*restrict Arr07)[1000000], double (*restrict Arr08)[1000000]) {

  for (int i = 0; i <= (size - 1) / n_unique_arrs; i += 1) {
    ;
    scalar1 = (scalar1 + ((*Arr02)[i] * (*Arr06)[i] + (*Arr08)[i])) + (*Arr05)[i] * (*Arr03)[i];
    ;
    scalar2 = (scalar2 + ((*Arr01)[i] * 1.8 + (*Arr04)[i])) + (*Arr07)[i] * 0.7;
    ;
  }
  return 0;
}
