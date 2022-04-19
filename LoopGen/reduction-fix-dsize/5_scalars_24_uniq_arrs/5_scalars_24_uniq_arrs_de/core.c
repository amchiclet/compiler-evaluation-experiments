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
extern double scalar4;
extern double scalar5;
extern int size;

int core(double (*restrict Arr01)[333334], double (*restrict Arr02)[333334], double (*restrict Arr03)[333334], double (*restrict Arr04)[333334], double (*restrict Arr05)[333334], double (*restrict Arr06)[333334], double (*restrict Arr07)[333334], double (*restrict Arr08)[333334], double (*restrict Arr09)[333334], double (*restrict Arr10)[333334], double (*restrict Arr11)[333334], double (*restrict Arr12)[333334], double (*restrict Arr13)[333334], double (*restrict Arr14)[333334], double (*restrict Arr15)[333334], double (*restrict Arr16)[333334], double (*restrict Arr17)[333334], double (*restrict Arr18)[333334], double (*restrict Arr19)[333334], double (*restrict Arr20)[333334], double (*restrict Arr21)[333334], double (*restrict Arr22)[333334], double (*restrict Arr23)[333334], double (*restrict Arr24)[333334]) {

  for (int i = 0; i <= (size - 1) / n_unique_arrs; i += 1) {
    scalar1 = ((((scalar1 + (*Arr07)[i]) + (*Arr10)[i]) + (*Arr24)[i]) + (*Arr12)[i]) + (*Arr13)[i];
    scalar3 = ((((scalar3 + (*Arr21)[i]) + (*Arr17)[i]) + (*Arr11)[i]) + (*Arr23)[i]) + (*Arr18)[i];
    scalar5 = ((((scalar5 + (*Arr22)[i]) + (*Arr19)[i]) + (*Arr04)[i]) + (*Arr01)[i]) + (*Arr08)[i];
    scalar4 = ((((scalar4 + (*Arr20)[i]) + (*Arr03)[i]) + (*Arr02)[i]) + (*Arr14)[i]) + (*Arr15)[i];
    scalar2 = ((((scalar2 + (*Arr16)[i]) + (*Arr05)[i]) + (*Arr09)[i]) + 0) + (*Arr06)[i];
  }
  return 0;
}
