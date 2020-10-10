#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int j;
extern int nfft;
extern int ndata;
extern double* restrict tmpfft;

void loop()
{
#pragma scop

    for(j = nfft; j > ndata; j--)
    {
        tmpfft[j] = 0;
    }

#pragma endscop
}
