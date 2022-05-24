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

int core(double (*restrict Arr01)[8388608], double (*restrict Arr02)[8388608], double (*restrict Arr03)[8388608], double (*restrict Arr05)[8388608], double (*restrict Arr06)[8388608], double (*restrict Arr08)[8388608], double (*restrict Arr10)[8388608], double (*restrict Arr11)[8388608], double (*restrict Arr12)[8388608], double (*restrict Arr13)[8388608], double (*restrict Arr14)[8388608], double (*restrict Arr17)[8388608], double (*restrict Arr18)[8388608], double (*restrict Arr20)[8388608], double (*restrict Arr22)[8388608]) {

  for (int i = 0; i <= (size - 1) / n_unique_arrs; i += 1) {
    scalar5 = ((((scalar5 + (*Arr05)[i]) + (*Arr08)[i]) + (*Arr11)[i]) + (*Arr17)[i]) + (*Arr08)[i];
    scalar3 = ((((scalar3 + (*Arr08)[i]) + 0) + (*Arr06)[i]) + (*Arr10)[i]) + (*Arr12)[i];
    scalar1 = ((((scalar1 + (*Arr14)[i]) + (*Arr22)[i]) + (*Arr02)[i]) + (*Arr05)[i]) + (*Arr20)[i];
    scalar4 = ((((scalar4 + (*Arr01)[i]) + (*Arr13)[i]) + (*Arr03)[i]) + 0) + (*Arr03)[i];
    scalar2 = ((((scalar2 + (*Arr05)[i]) + (*Arr14)[i]) + (*Arr10)[i]) + (*Arr18)[i]) + (*Arr14)[i];
  }
  return 0;
}
