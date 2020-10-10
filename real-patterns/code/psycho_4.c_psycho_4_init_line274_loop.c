#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int j;
extern double * restrict tmn;
extern double * restrict cbval;

void loop()
{
#pragma scop

    for(j = 0; j < 64; j++) tmn[j] =(15.5 + cbval[j] > 24.5?15.5 + cbval[j] : 24.5);

#pragma endscop
}
