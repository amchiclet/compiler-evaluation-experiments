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

int core(double (*restrict Arr01)[32000], double (*restrict Arr02)[1], double (*restrict Arr03)[32000], double (*restrict Arr04)[32000], double (*restrict Arr05)[32000], double (*restrict Arr06)[32000], double (*restrict Arr07)[1], double (*restrict Arr08)[32000], double (*restrict Arr09)[32000], double (*restrict Arr10)[32000], double (*restrict Arr11)[32000], double (*restrict Arr12)[32000], double (*restrict Arr13)[1], double (*restrict Arr14)[1], double (*restrict Arr15)[1], double (*restrict Arr16)[1], double (*restrict Arr17)[1], double (*restrict Arr18)[1], double (*restrict Arr19)[1], double (*restrict Arr20)[1], double (*restrict Arr21)[1], double (*restrict Arr22)[1], double (*restrict Arr23)[1], double (*restrict Arr24)[1], double (*restrict Arr25)[1]) {

  for (int i = 0; i <= size - 1; i += 1) {
    scalar1 = (scalar1 * (*Arr06)[i] + (*Arr08)[i] * (*Arr11)[i]) + (*Arr12)[i] * (*Arr11)[i];
    scalar3 = (scalar3 * (*Arr11)[i] + (*Arr04)[i] * (*Arr05)[i]) + (*Arr06)[i] * (*Arr11)[i];
    scalar2 = (scalar2 * (*Arr03)[i] + (*Arr05)[i] * (*Arr01)[i]) + (*Arr06)[i] * (*Arr10)[i];
    ;
    scalar4 = (scalar4 * (*Arr09)[i] + (*Arr01)[i] * (*Arr12)[i]) + (*Arr11)[i] * (*Arr03)[i];
  }
  return 0;
}
