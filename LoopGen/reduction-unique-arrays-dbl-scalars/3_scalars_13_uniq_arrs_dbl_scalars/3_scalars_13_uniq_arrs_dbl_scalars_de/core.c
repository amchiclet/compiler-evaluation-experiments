#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>
#include <assert.h>
#include <limits.h>
#include <math.h>
#include <string.h>

extern double scalar1;
extern double scalar2;
extern double scalar3;
extern int size;

int core(double (*restrict Arr01)[32000], double (*restrict Arr02)[32000], double (*restrict Arr03)[32000], double (*restrict Arr04)[32000], double (*restrict Arr05)[32000], double (*restrict Arr06)[32000], double (*restrict Arr07)[32000], double (*restrict Arr08)[32000], double (*restrict Arr09)[32000], double (*restrict Arr10)[32000], double (*restrict Arr11)[32000], double (*restrict Arr12)[32000], double (*restrict Arr13)[32000]) {

  for (int i = 0; i <= size - 1; i += 1) {
    ;
    scalar3 = ((((scalar3 + (*Arr05)[i]) + (*Arr07)[i]) + (*Arr08)[i]) + (*Arr09)[i]) + (*Arr02)[i];
    scalar1 = ((((scalar1 + (*Arr11)[i]) + (*Arr01)[i]) + (*Arr03)[i]) + (*Arr10)[i]) + (*Arr06)[i];
    scalar2 = ((((scalar2 + (*Arr12)[i]) + 0) + (*Arr13)[i]) + 0) + (*Arr04)[i];
    ;
  }
  return 0;
}
