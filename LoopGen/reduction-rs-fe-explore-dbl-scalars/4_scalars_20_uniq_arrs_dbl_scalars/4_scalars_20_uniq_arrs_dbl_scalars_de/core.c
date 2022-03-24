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
extern double scalar4;
extern int size;

int core(double (*restrict Arr01)[32000], double (*restrict Arr02)[32000], double (*restrict Arr03)[32000], double (*restrict Arr04)[32000], double (*restrict Arr05)[32000], double (*restrict Arr06)[32000], double (*restrict Arr07)[32000], double (*restrict Arr08)[32000], double (*restrict Arr09)[32000], double (*restrict Arr10)[32000], double (*restrict Arr11)[32000], double (*restrict Arr12)[32000], double (*restrict Arr13)[32000], double (*restrict Arr14)[32000], double (*restrict Arr15)[32000], double (*restrict Arr16)[32000], double (*restrict Arr17)[32000], double (*restrict Arr18)[32000], double (*restrict Arr19)[32000], double (*restrict Arr20)[32000]) {

  for (int i = 0; i <= size - 1; i += 1) {
    scalar4 = ((((scalar4 + (*Arr04)[i]) + (*Arr06)[i]) + (*Arr10)[i]) + (*Arr13)[i]) + (*Arr19)[i];
    ;
    scalar3 = ((((scalar3 + (*Arr03)[i]) + (*Arr08)[i]) + (*Arr11)[i]) + (*Arr15)[i]) + (*Arr17)[i];
    scalar2 = ((((scalar2 + (*Arr01)[i]) + (*Arr07)[i]) + (*Arr09)[i]) + (*Arr16)[i]) + (*Arr20)[i];
    scalar1 = ((((scalar1 + (*Arr02)[i]) + (*Arr05)[i]) + (*Arr12)[i]) + (*Arr14)[i]) + (*Arr18)[i];
  }
  return 0;
}
