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

int core(double (*restrict Arr01)[335545], double (*restrict Arr02)[335545], double (*restrict Arr03)[335545], double (*restrict Arr04)[335545], double (*restrict Arr07)[335545], double (*restrict Arr09)[335545], double (*restrict Arr12)[335545], double (*restrict Arr13)[335545], double (*restrict Arr16)[335545], double (*restrict Arr17)[335545], double (*restrict Arr20)[335545], double (*restrict Arr21)[335545], double (*restrict Arr22)[335545], double (*restrict Arr23)[335545], double (*restrict Arr24)[335545]) {

  for (int i = 0; i <= (size - 1) / n_unique_arrs; i += 1) {
    scalar1 = ((((scalar1 + (*Arr02)[i]) + (*Arr20)[i]) + (*Arr07)[i]) + (*Arr01)[i]) + (*Arr12)[i];
    scalar5 = ((((scalar5 + (*Arr16)[i]) + (*Arr13)[i]) + (*Arr01)[i]) + (*Arr17)[i]) + (*Arr03)[i];
    scalar3 = ((((scalar3 + (*Arr22)[i]) + (*Arr03)[i]) + (*Arr22)[i]) + (*Arr24)[i]) + (*Arr22)[i];
    scalar2 = ((((scalar2 + (*Arr13)[i]) + (*Arr01)[i]) + (*Arr12)[i]) + (*Arr02)[i]) + (*Arr04)[i];
    scalar4 = ((((scalar4 + (*Arr20)[i]) + (*Arr01)[i]) + (*Arr09)[i]) + (*Arr21)[i]) + (*Arr23)[i];
  }
  return 0;
}
