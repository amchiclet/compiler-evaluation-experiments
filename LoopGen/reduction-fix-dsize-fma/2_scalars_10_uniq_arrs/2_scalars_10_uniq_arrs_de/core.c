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

int core(double (*restrict Arr01)[800000], double (*restrict Arr02)[800000], double (*restrict Arr03)[800000], double (*restrict Arr04)[800000], double (*restrict Arr05)[800000], double (*restrict Arr06)[800000], double (*restrict Arr07)[800000], double (*restrict Arr08)[800000], double (*restrict Arr09)[800000], double (*restrict Arr10)[800000]) {

  for (int i = 0; i <= (size - 1) / n_unique_arrs; i += 1) {
    ;
    scalar1 = (scalar1 + ((*Arr03)[i] * (*Arr05)[i] + (*Arr06)[i])) + (*Arr09)[i] * (*Arr07)[i];
    scalar2 = (scalar2 + ((*Arr08)[i] * (*Arr10)[i] + (*Arr01)[i])) + (*Arr04)[i] * (*Arr02)[i];
    ;
    ;
  }
  return 0;
}
