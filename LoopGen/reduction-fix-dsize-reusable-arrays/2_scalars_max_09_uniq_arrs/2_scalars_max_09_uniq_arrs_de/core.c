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

int core(double (*restrict Arr02)[932068], double (*restrict Arr03)[932068], double (*restrict Arr04)[932068], double (*restrict Arr05)[932068], double (*restrict Arr06)[932068], double (*restrict Arr07)[932068], double (*restrict Arr08)[932068]) {

  for (int i = 0; i <= (size - 1) / n_unique_arrs; i += 1) {
    ;
    scalar2 = ((((scalar2 + 0) + (*Arr02)[i]) + (*Arr07)[i]) + (*Arr04)[i]) + (*Arr05)[i];
    scalar1 = ((((scalar1 + (*Arr06)[i]) + (*Arr08)[i]) + 0) + (*Arr03)[i]) + (*Arr04)[i];
    ;
    ;
  }
  return 0;
}
