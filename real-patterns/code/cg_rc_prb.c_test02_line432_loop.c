#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int i;
extern int n;
extern double rnrm2;
extern double * restrict r;

void loop()
{
#pragma scop

    for(i = 0; i < n; i++)
    {
        rnrm2 = rnrm2 + r[i] * r[i];
    }

#pragma endscop
}
