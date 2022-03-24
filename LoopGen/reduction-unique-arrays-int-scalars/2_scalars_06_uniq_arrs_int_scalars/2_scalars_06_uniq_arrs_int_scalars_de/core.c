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
extern int size;

int core(double (*restrict Arr01)[32000], double (*restrict Arr02)[32000], double (*restrict Arr03)[32000], double (*restrict Arr04)[32000], double (*restrict Arr05)[32000], double (*restrict Arr06)[32000]) {

  for (int i = 0; i <= size - 1; i += 1) {
    scalar1 = ((((scalar1 + 0) + 0) + (*Arr05)[i]) + (*Arr06)[i]) + (*Arr02)[i];
    ;
    scalar2 = ((((scalar2 + (*Arr03)[i]) + 0) + 0) + (*Arr04)[i]) + (*Arr01)[i];
    ;
    ;
  }
  return 0;
}
