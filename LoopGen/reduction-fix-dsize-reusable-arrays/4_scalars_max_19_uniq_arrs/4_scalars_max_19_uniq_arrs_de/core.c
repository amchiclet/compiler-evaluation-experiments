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
extern int size;

int core(double (*restrict Arr01)[441506], double (*restrict Arr02)[441506], double (*restrict Arr04)[441506], double (*restrict Arr05)[441506], double (*restrict Arr11)[441506], double (*restrict Arr12)[441506], double (*restrict Arr13)[441506], double (*restrict Arr14)[441506], double (*restrict Arr15)[441506], double (*restrict Arr16)[441506], double (*restrict Arr18)[441506]) {

  for (int i = 0; i <= (size - 1) / n_unique_arrs; i += 1) {
    scalar4 = ((((scalar4 + (*Arr05)[i]) + (*Arr12)[i]) + (*Arr14)[i]) + (*Arr02)[i]) + 0;
    ;
    scalar1 = ((((scalar1 + (*Arr15)[i]) + (*Arr13)[i]) + (*Arr15)[i]) + (*Arr02)[i]) + (*Arr04)[i];
    scalar3 = ((((scalar3 + (*Arr16)[i]) + (*Arr05)[i]) + (*Arr01)[i]) + (*Arr02)[i]) + 0;
    scalar2 = ((((scalar2 + 0) + (*Arr05)[i]) + (*Arr11)[i]) + (*Arr04)[i]) + (*Arr18)[i];
  }
  return 0;
}
