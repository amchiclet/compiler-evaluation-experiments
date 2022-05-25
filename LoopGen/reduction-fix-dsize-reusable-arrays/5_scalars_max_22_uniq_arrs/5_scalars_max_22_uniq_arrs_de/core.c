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

int core(double (*restrict Arr01)[381301], double (*restrict Arr02)[381301], double (*restrict Arr03)[381301], double (*restrict Arr05)[381301], double (*restrict Arr06)[381301], double (*restrict Arr08)[381301], double (*restrict Arr10)[381301], double (*restrict Arr11)[381301], double (*restrict Arr12)[381301], double (*restrict Arr13)[381301], double (*restrict Arr14)[381301], double (*restrict Arr17)[381301], double (*restrict Arr18)[381301], double (*restrict Arr20)[381301], double (*restrict Arr22)[381301]) {

  for (int i = 0; i <= (size - 1) / n_unique_arrs; i += 1) {
    scalar5 = ((((scalar5 + (*Arr05)[i]) + (*Arr08)[i]) + (*Arr11)[i]) + (*Arr17)[i]) + (*Arr08)[i];
    scalar3 = ((((scalar3 + (*Arr08)[i]) + 0) + (*Arr06)[i]) + (*Arr10)[i]) + (*Arr12)[i];
    scalar1 = ((((scalar1 + (*Arr14)[i]) + (*Arr22)[i]) + (*Arr02)[i]) + (*Arr05)[i]) + (*Arr20)[i];
    scalar4 = ((((scalar4 + (*Arr01)[i]) + (*Arr13)[i]) + (*Arr03)[i]) + 0) + (*Arr03)[i];
    scalar2 = ((((scalar2 + (*Arr05)[i]) + (*Arr14)[i]) + (*Arr10)[i]) + (*Arr18)[i]) + (*Arr14)[i];
  }
  return 0;
}
