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

int core(double (*restrict Arr01)[615385], double (*restrict Arr02)[615385], double (*restrict Arr03)[615385], double (*restrict Arr04)[615385], double (*restrict Arr05)[615385], double (*restrict Arr06)[615385], double (*restrict Arr07)[615385], double (*restrict Arr08)[615385], double (*restrict Arr09)[615385], double (*restrict Arr10)[615385], double (*restrict Arr11)[615385], double (*restrict Arr12)[615385], double (*restrict Arr13)[615385]) {

  for (int i = 0; i <= (size - 1) / n_unique_arrs; i += 1) {
    scalar3 = (scalar3 + ((*Arr02)[i] * (*Arr09)[i] + 0.7)) + (*Arr05)[i] * (*Arr01)[i];
    ;
    ;
    scalar1 = (scalar1 + ((*Arr08)[i] * (*Arr06)[i] + (*Arr04)[i])) + (*Arr10)[i] * (*Arr12)[i];
    scalar2 = (scalar2 + ((*Arr11)[i] * (*Arr13)[i] + (*Arr07)[i])) + (*Arr03)[i] * 1.8;
  }
  return 0;
}
