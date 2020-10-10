#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int j;
extern int srange;
extern double * restrict power;
extern int k;

void loop()
{
#pragma scop

    for(j = -srange; j <= +srange; j++) power[k + j] = - 200.0;

#pragma endscop
}
