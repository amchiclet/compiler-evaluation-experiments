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

int core(double (*restrict Arr01)[1142858], double (*restrict Arr02)[1142858], double (*restrict Arr03)[1142858], double (*restrict Arr04)[1142858], double (*restrict Arr05)[1142858], double (*restrict Arr06)[1142858], double (*restrict Arr07)[1142858]) {

  for (int i = 0; i <= (size - 1) / n_unique_arrs; i += 1) {
    ;
    scalar1 = ((((scalar1 + (*Arr01)[i]) + 0) + (*Arr03)[i]) + (*Arr02)[i]) + (*Arr04)[i];
    scalar2 = ((((scalar2 + (*Arr06)[i]) + (*Arr05)[i]) + 0) + (*Arr07)[i]) + 0;
    ;
    ;
  }
  return 0;
}
