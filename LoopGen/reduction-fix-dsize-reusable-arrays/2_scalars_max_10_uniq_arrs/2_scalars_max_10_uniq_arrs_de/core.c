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

int core(double (*restrict Arr01)[838861], double (*restrict Arr02)[838861], double (*restrict Arr03)[838861], double (*restrict Arr05)[838861], double (*restrict Arr06)[838861], double (*restrict Arr08)[838861], double (*restrict Arr09)[838861]) {

  for (int i = 0; i <= (size - 1) / n_unique_arrs; i += 1) {
    ;
    ;
    ;
    scalar2 = ((((scalar2 + (*Arr05)[i]) + (*Arr03)[i]) + (*Arr09)[i]) + (*Arr01)[i]) + (*Arr08)[i];
    scalar1 = ((((scalar1 + (*Arr02)[i]) + (*Arr06)[i]) + (*Arr01)[i]) + (*Arr09)[i]) + (*Arr05)[i];
  }
  return 0;
}
