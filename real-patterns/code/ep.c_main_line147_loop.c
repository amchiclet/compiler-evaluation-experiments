#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int i;
extern double * restrict x;

void loop()
{
#pragma scop

    for(i = 0; i < 2 *(1 << 16); i++) x[i] = - 1.0e99;

#pragma endscop
}
