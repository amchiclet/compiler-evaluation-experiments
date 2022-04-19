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

int core(double (*restrict Arr01)[320000], double (*restrict Arr02)[320000], double (*restrict Arr03)[320000], double (*restrict Arr04)[320000], double (*restrict Arr05)[320000], double (*restrict Arr06)[320000], double (*restrict Arr07)[320000], double (*restrict Arr08)[320000], double (*restrict Arr09)[320000], double (*restrict Arr10)[320000], double (*restrict Arr11)[320000], double (*restrict Arr12)[320000], double (*restrict Arr13)[320000], double (*restrict Arr14)[320000], double (*restrict Arr15)[320000], double (*restrict Arr16)[320000], double (*restrict Arr17)[320000], double (*restrict Arr18)[320000], double (*restrict Arr19)[320000], double (*restrict Arr20)[320000], double (*restrict Arr21)[320000], double (*restrict Arr22)[320000], double (*restrict Arr23)[320000], double (*restrict Arr24)[320000], double (*restrict Arr25)[320000]) {

  for (int i = 0; i <= (size - 1) / n_unique_arrs; i += 1) {
    scalar2 = ((((scalar2 + (*Arr24)[i]) + (*Arr14)[i]) + (*Arr08)[i]) + (*Arr07)[i]) + (*Arr12)[i];
    scalar1 = ((((scalar1 + (*Arr01)[i]) + (*Arr23)[i]) + (*Arr22)[i]) + (*Arr19)[i]) + (*Arr03)[i];
    scalar3 = ((((scalar3 + (*Arr04)[i]) + (*Arr13)[i]) + (*Arr20)[i]) + (*Arr10)[i]) + (*Arr05)[i];
    scalar4 = ((((scalar4 + (*Arr25)[i]) + (*Arr16)[i]) + (*Arr11)[i]) + (*Arr18)[i]) + (*Arr21)[i];
    scalar5 = ((((scalar5 + (*Arr17)[i]) + (*Arr09)[i]) + (*Arr02)[i]) + (*Arr06)[i]) + (*Arr15)[i];
  }
  return 0;
}
