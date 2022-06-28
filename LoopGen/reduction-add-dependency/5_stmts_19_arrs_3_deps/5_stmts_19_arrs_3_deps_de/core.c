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

int core(double (*restrict Arr01)[441506], double (*restrict Arr02)[441506], double (*restrict Arr03)[441506], double (*restrict Arr04)[441506], double (*restrict Arr05)[441506], double (*restrict Arr06)[441506], double (*restrict Arr07)[441506], double (*restrict Arr08)[441506], double (*restrict Arr09)[441506], double (*restrict Arr10)[441506], double (*restrict Arr11)[441506], double (*restrict Arr12)[441506], double (*restrict Arr13)[441506], double (*restrict Arr14)[441506], double (*restrict Arr15)[441506], double (*restrict Arr16)[441506], double (*restrict Arr17)[441506], double (*restrict Arr18)[441506], double (*restrict Arr19)[441506]) {

  for (int i = 0; i <= (size - 1) / n_arrs; i += 1) {
    scalar1 = ((((scalar1 + scalar5) + (*Arr16)[i]) + (*Arr09)[i]) + (*Arr06)[i]) + (*Arr01)[i];
    scalar5 = ((((scalar5 + (*Arr05)[i]) + (*Arr10)[i]) + (*Arr08)[i]) + (*Arr19)[i]) + (*Arr03)[i];
    scalar4 = ((((scalar4 + (*Arr02)[i]) + (*Arr15)[i]) + (*Arr13)[i]) + (*Arr11)[i]) + (*Arr17)[i];
    scalar3 = ((((scalar3 + scalar5) + (*Arr07)[i]) + (*Arr14)[i]) + (*Arr12)[i]) + (*Arr04)[i];
    scalar2 = ((((scalar2 + scalar3) + (*Arr18)[i]) + (*Arr08)[i]) + (*Arr12)[i]) + (*Arr16)[i];
  }
  return 0;
}
