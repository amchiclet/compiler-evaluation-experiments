#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int i;
extern int n;
extern double bnrm2;
extern double * restrict b;

void loop()
{
#pragma scop

    for(i = 0; i < n; i++)
    {
        bnrm2 = bnrm2 + b[i] * b[i];
    }

#pragma endscop
}
