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

int core(double (*restrict Arr01)[32000], double (*restrict Arr02)[32000], double (*restrict Arr03)[32000], double (*restrict Arr04)[32000], double (*restrict Arr05)[32000], double (*restrict Arr06)[32000], double (*restrict Arr07)[32000], double (*restrict Arr08)[32000], double (*restrict Arr09)[32000], double (*restrict Arr10)[32000], double (*restrict Arr11)[32000], double (*restrict Arr12)[32000], double (*restrict Arr13)[32000], double (*restrict Arr14)[32000]) {

  for (int i = 0; i <= size - 1; i += 1) {
    scalar1 = ((((scalar1 + (*Arr01)[i]) + (*Arr04)[i]) + (*Arr08)[i]) + (*Arr11)[i]) + 0;
    ;
    ;
    scalar2 = ((((scalar2 + (*Arr03)[i]) + (*Arr06)[i]) + (*Arr07)[i]) + (*Arr12)[i]) + (*Arr14)[i];
    scalar3 = ((((scalar3 + (*Arr02)[i]) + (*Arr05)[i]) + (*Arr09)[i]) + (*Arr10)[i]) + (*Arr13)[i];
  }
  return 0;
}
