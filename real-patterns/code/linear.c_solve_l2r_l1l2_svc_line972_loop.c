#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int i;
extern int l;
extern double * restrict alpha;

void loop()
{
#pragma scop

    for(i = 0; i < l; i++) alpha[i] = 0;

#pragma endscop
}
