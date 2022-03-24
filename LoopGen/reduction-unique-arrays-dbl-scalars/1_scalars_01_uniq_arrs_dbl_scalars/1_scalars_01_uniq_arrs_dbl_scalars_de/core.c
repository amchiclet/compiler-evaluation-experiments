#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>
#include <assert.h>
#include <limits.h>
#include <math.h>
#include <string.h>

extern double scalar1;
extern int size;

int core(double (*restrict Arr01)[32000]) {

  for (int i = 0; i <= size - 1; i += 1) {
    ;
    ;
    scalar1 = ((((scalar1 + 0) + 0) + 0) + 0) + (*Arr01)[i];
    ;
    ;
  }
  return 0;
}
