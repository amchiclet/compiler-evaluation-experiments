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

int core(double (*restrict Arr01)[1333334], double (*restrict Arr02)[1333334], double (*restrict Arr03)[1333334], double (*restrict Arr04)[1333334], double (*restrict Arr05)[1333334], double (*restrict Arr06)[1333334]) {

  for (int i = 0; i <= (size - 1) / n_unique_arrs; i += 1) {
    ;
    ;
    ;
    scalar1 = ((((scalar1 + 0) + 0) + (*Arr05)[i]) + (*Arr04)[i]) + (*Arr06)[i];
    scalar2 = ((((scalar2 + (*Arr03)[i]) + (*Arr01)[i]) + 0) + (*Arr02)[i]) + 0;
  }
  return 0;
}
