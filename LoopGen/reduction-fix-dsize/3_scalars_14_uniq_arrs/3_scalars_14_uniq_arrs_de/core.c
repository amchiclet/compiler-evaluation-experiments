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

int core(double (*restrict Arr01)[571429], double (*restrict Arr02)[571429], double (*restrict Arr03)[571429], double (*restrict Arr04)[571429], double (*restrict Arr05)[571429], double (*restrict Arr06)[571429], double (*restrict Arr07)[571429], double (*restrict Arr08)[571429], double (*restrict Arr09)[571429], double (*restrict Arr10)[571429], double (*restrict Arr11)[571429], double (*restrict Arr12)[571429], double (*restrict Arr13)[571429], double (*restrict Arr14)[571429]) {

  for (int i = 0; i <= (size - 1) / n_unique_arrs; i += 1) {
    scalar2 = ((((scalar2 + (*Arr02)[i]) + (*Arr08)[i]) + (*Arr11)[i]) + (*Arr12)[i]) + (*Arr06)[i];
    scalar3 = ((((scalar3 + (*Arr13)[i]) + (*Arr14)[i]) + (*Arr05)[i]) + (*Arr07)[i]) + (*Arr01)[i];
    scalar1 = ((((scalar1 + (*Arr09)[i]) + (*Arr04)[i]) + (*Arr10)[i]) + (*Arr03)[i]) + 0;
    ;
    ;
  }
  return 0;
}
