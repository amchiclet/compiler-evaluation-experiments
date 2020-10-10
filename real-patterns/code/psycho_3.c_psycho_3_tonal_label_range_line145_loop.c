#include <inttypes.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
extern int j;
extern int srange;
extern double * restrict power;
extern int k;
extern int * restrict tonelabel;

void loop()
{
#pragma scop

    for(j = -srange; j <= +srange; j++) if(abs(j) > 1) if(power[k] - power[k + j] < 7.0) tonelabel[k] = 0;

#pragma endscop
}
