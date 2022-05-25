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

int core(double (*restrict Arr01)[466034], double (*restrict Arr03)[466034], double (*restrict Arr06)[466034], double (*restrict Arr07)[466034], double (*restrict Arr08)[466034], double (*restrict Arr10)[466034], double (*restrict Arr13)[466034], double (*restrict Arr14)[466034], double (*restrict Arr16)[466034], double (*restrict Arr17)[466034], double (*restrict Arr18)[466034]) {

  for (int i = 0; i <= (size - 1) / n_unique_arrs; i += 1) {
    scalar4 = ((((scalar4 + 0) + (*Arr03)[i]) + (*Arr17)[i]) + 0) + (*Arr03)[i];
    scalar3 = ((((scalar3 + (*Arr14)[i]) + (*Arr07)[i]) + (*Arr10)[i]) + (*Arr18)[i]) + 0;
    ;
    scalar2 = ((((scalar2 + (*Arr14)[i]) + (*Arr16)[i]) + (*Arr13)[i]) + 0) + 0;
    scalar1 = ((((scalar1 + (*Arr08)[i]) + (*Arr01)[i]) + (*Arr01)[i]) + (*Arr06)[i]) + (*Arr10)[i];
  }
  return 0;
}
