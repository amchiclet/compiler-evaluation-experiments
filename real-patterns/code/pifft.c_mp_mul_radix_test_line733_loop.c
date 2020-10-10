#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int j;
extern int ndata;
extern double* restrict tmpfft;
extern int radix_2;

void loop()
{
#pragma scop

    for(j = ndata; j > 2; j--)
    {
        tmpfft[j] = radix_2;
    }

#pragma endscop
}
