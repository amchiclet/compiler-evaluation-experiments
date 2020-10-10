#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int i;
extern int n;
extern double * restrict bw;
extern double* restrict d;
extern double * restrict zw;

void loop()
{
#pragma scop

    for(i = 0; i < n; i++)
    {
        bw[i] = d[i];
        zw[i] = 0.0;
    }

#pragma endscop
}
