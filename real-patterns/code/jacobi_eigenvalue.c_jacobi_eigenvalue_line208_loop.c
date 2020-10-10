#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int i;
extern int n;
extern double * restrict bw;
extern double * restrict zw;
extern double* restrict d;

void loop()
{
#pragma scop

    for(i = 0; i < n; i++)
    {
        bw[i] = bw[i] + zw[i];
        d[i] = bw[i];
        zw[i] = 0.0;
    }

#pragma endscop
}
