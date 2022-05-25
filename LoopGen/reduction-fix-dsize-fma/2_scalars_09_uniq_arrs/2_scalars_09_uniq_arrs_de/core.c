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

int core(double (*restrict Arr01)[888889], double (*restrict Arr02)[888889], double (*restrict Arr03)[888889], double (*restrict Arr04)[888889], double (*restrict Arr05)[888889], double (*restrict Arr06)[888889], double (*restrict Arr07)[888889], double (*restrict Arr08)[888889], double (*restrict Arr09)[888889]) {

  for (int i = 0; i <= (size - 1) / n_unique_arrs; i += 1) {
    ;
    ;
    ;
    scalar1 = (scalar1 + ((*Arr08)[i] * (*Arr07)[i] + (*Arr05)[i])) + (*Arr09)[i] * (*Arr03)[i];
    scalar2 = (scalar2 + ((*Arr06)[i] * (*Arr04)[i] + (*Arr01)[i])) + (*Arr02)[i] * 0.7;
  }
  return 0;
}
