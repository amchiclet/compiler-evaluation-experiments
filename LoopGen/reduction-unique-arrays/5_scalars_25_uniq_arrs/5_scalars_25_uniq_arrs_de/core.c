#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>
#include <assert.h>
#include <limits.h>
#include <math.h>
#include <string.h>

extern int scalar1;
extern int scalar2;
extern int scalar3;
extern int scalar4;
extern int scalar5;
extern int size;

int core(double (*restrict Arr01)[32000], double (*restrict Arr02)[32000], double (*restrict Arr03)[32000], double (*restrict Arr04)[32000], double (*restrict Arr05)[32000], double (*restrict Arr06)[32000], double (*restrict Arr07)[32000], double (*restrict Arr08)[32000], double (*restrict Arr09)[32000], double (*restrict Arr10)[32000], double (*restrict Arr11)[32000], double (*restrict Arr12)[32000], double (*restrict Arr13)[32000], double (*restrict Arr14)[32000], double (*restrict Arr15)[32000], double (*restrict Arr16)[32000], double (*restrict Arr17)[32000], double (*restrict Arr18)[32000], double (*restrict Arr19)[32000], double (*restrict Arr20)[32000], double (*restrict Arr21)[32000], double (*restrict Arr22)[32000], double (*restrict Arr23)[32000], double (*restrict Arr24)[32000], double (*restrict Arr25)[32000]) {

  for (int i = 0; i <= size - 1; i += 1) {
    scalar2 = ((((scalar2 + (*Arr18)[i]) + (*Arr06)[i]) + (*Arr10)[i]) + (*Arr08)[i]) + (*Arr12)[i];
    scalar4 = ((((scalar4 + (*Arr15)[i]) + (*Arr13)[i]) + (*Arr14)[i]) + (*Arr25)[i]) + (*Arr23)[i];
    scalar5 = ((((scalar5 + (*Arr24)[i]) + (*Arr03)[i]) + (*Arr22)[i]) + (*Arr16)[i]) + (*Arr19)[i];
    scalar1 = ((((scalar1 + (*Arr04)[i]) + (*Arr01)[i]) + (*Arr07)[i]) + (*Arr20)[i]) + (*Arr17)[i];
    scalar3 = ((((scalar3 + (*Arr02)[i]) + (*Arr11)[i]) + (*Arr05)[i]) + (*Arr09)[i]) + (*Arr21)[i];
  }
  return 0;
}
