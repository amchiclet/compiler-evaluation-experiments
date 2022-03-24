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
extern int size;

int core(double (*restrict Arr01)[32000], double (*restrict Arr02)[32000], double (*restrict Arr03)[32000]) {

  for (int i = 0; i <= size - 1; i += 1) {
    ;
    ;
    ;
    ;
    scalar1 = ((((scalar1 + 0) + (*Arr03)[i]) + (*Arr01)[i]) + (*Arr02)[i]) + 0;
  }
  return 0;
}
