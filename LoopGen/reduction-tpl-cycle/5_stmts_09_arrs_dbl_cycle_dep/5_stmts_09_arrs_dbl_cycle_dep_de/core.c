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

int core(double (*restrict Arr01)[932068], double (*restrict Arr02)[932068], double (*restrict Arr03)[932068], double (*restrict Arr04)[932068], double (*restrict Arr05)[932068], double (*restrict Arr06)[932068], double (*restrict Arr07)[932068], double (*restrict Arr08)[932068], double (*restrict Arr09)[932068]) {

  for (int i = 0; i <= (size - 1) / n_arrs; i += 1) {
    scalar4 = ((((scalar4 + (*Arr09)[i]) + (*Arr02)[i]) + (*Arr04)[i]) + (*Arr06)[i]) + (*Arr05)[i];
    scalar2 = ((((scalar2 + scalar3) + (*Arr07)[i]) + (*Arr03)[i]) + (*Arr01)[i]) + (*Arr08)[i];
    scalar1 = ((((scalar1 + scalar2) + (*Arr09)[i]) + (*Arr08)[i]) + (*Arr08)[i]) + (*Arr06)[i];
    scalar5 = ((((scalar5 + (*Arr06)[i]) + (*Arr02)[i]) + (*Arr08)[i]) + (*Arr02)[i]) + (*Arr08)[i];
    scalar3 = ((((scalar3 + scalar1) + (*Arr07)[i]) + (*Arr01)[i]) + (*Arr05)[i]) + (*Arr06)[i];
  }
  return 0;
}
