#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>
#include <assert.h>
#include <limits.h>
#include <math.h>
#include <string.h>

extern int n_arrs;
extern double scalar1;
extern double scalar2;
extern double scalar3;
extern double scalar4;
extern double scalar5;
extern int size;

int core(double (*restrict Arr01)[335545], double (*restrict Arr02)[335545], double (*restrict Arr03)[335545], double (*restrict Arr04)[335545], double (*restrict Arr05)[335545], double (*restrict Arr06)[335545], double (*restrict Arr07)[335545], double (*restrict Arr08)[335545], double (*restrict Arr09)[335545], double (*restrict Arr10)[335545], double (*restrict Arr11)[335545], double (*restrict Arr12)[335545], double (*restrict Arr13)[335545], double (*restrict Arr14)[335545], double (*restrict Arr15)[335545], double (*restrict Arr16)[335545], double (*restrict Arr17)[335545], double (*restrict Arr18)[335545], double (*restrict Arr19)[335545], double (*restrict Arr20)[335545], double (*restrict Arr21)[335545], double (*restrict Arr22)[335545], double (*restrict Arr23)[335545], double (*restrict Arr24)[335545], double (*restrict Arr25)[335545]) {

  for (int i = 0; i <= (size - 1) / n_arrs; i += 1) {
    scalar1 = ((((scalar1 + (*Arr07)[i]) + (*Arr06)[i]) + (*Arr17)[i]) + (*Arr03)[i]) + (*Arr18)[i];
    scalar5 = ((((scalar5 + (*Arr16)[i]) + (*Arr12)[i]) + (*Arr13)[i]) + (*Arr22)[i]) + (*Arr20)[i];
    scalar2 = ((((scalar2 + (*Arr15)[i]) + (*Arr09)[i]) + (*Arr02)[i]) + (*Arr10)[i]) + (*Arr01)[i];
    scalar4 = ((((scalar4 + (*Arr23)[i]) + (*Arr04)[i]) + (*Arr19)[i]) + (*Arr08)[i]) + (*Arr21)[i];
    scalar3 = ((((scalar3 + (*Arr24)[i]) + (*Arr25)[i]) + (*Arr14)[i]) + (*Arr11)[i]) + (*Arr05)[i];
  }
  return 0;
}
