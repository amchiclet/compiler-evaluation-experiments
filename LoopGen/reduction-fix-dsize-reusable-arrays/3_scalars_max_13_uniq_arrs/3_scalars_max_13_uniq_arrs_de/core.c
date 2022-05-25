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

int core(double (*restrict Arr02)[645278], double (*restrict Arr03)[645278], double (*restrict Arr05)[645278], double (*restrict Arr06)[645278], double (*restrict Arr08)[645278], double (*restrict Arr09)[645278], double (*restrict Arr11)[645278], double (*restrict Arr13)[645278]) {

  for (int i = 0; i <= (size - 1) / n_unique_arrs; i += 1) {
    scalar1 = ((((scalar1 + (*Arr05)[i]) + 0) + (*Arr08)[i]) + (*Arr13)[i]) + (*Arr13)[i];
    ;
    scalar3 = ((((scalar3 + (*Arr02)[i]) + 0) + (*Arr05)[i]) + (*Arr03)[i]) + (*Arr11)[i];
    scalar2 = ((((scalar2 + (*Arr09)[i]) + 0) + (*Arr11)[i]) + (*Arr11)[i]) + (*Arr06)[i];
    ;
  }
  return 0;
}
