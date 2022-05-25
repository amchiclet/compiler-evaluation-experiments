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
extern int size;

int core(double (*restrict Arr01)[762601], double (*restrict Arr04)[762601], double (*restrict Arr07)[762601], double (*restrict Arr08)[762601], double (*restrict Arr10)[762601], double (*restrict Arr11)[762601]) {

  for (int i = 0; i <= (size - 1) / n_unique_arrs; i += 1) {
    scalar1 = ((((scalar1 + (*Arr04)[i]) + (*Arr04)[i]) + (*Arr11)[i]) + (*Arr08)[i]) + (*Arr07)[i];
    scalar3 = ((((scalar3 + 0) + 0) + (*Arr11)[i]) + (*Arr10)[i]) + 0;
    ;
    ;
    scalar2 = ((((scalar2 + (*Arr07)[i]) + (*Arr01)[i]) + (*Arr07)[i]) + 0) + 0;
  }
  return 0;
}
