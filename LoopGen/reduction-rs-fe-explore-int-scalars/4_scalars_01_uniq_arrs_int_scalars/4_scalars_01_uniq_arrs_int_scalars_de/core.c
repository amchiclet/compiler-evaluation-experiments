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
extern int size;

int core(double (*restrict Arr01)[32000]) {

  for (int i = 0; i <= size - 1; i += 1) {
    scalar1 = ((((scalar1 + (*Arr01)[i]) + 0) + 0) + 0) + 0;
    scalar4 = ((((scalar4 + 0) + 0) + 0) + 0) + 0;
    scalar3 = ((((scalar3 + 0) + 0) + 0) + 0) + 0;
    ;
    scalar2 = ((((scalar2 + 0) + 0) + 0) + 0) + 0;
  }
  return 0;
}
