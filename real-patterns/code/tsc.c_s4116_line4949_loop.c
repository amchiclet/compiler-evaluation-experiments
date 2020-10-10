#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int off;
extern int inc;
extern float sum;
extern float  a[32000] ;
extern float  aa[256][256] ;
extern int j;
extern int * __restrict__ restrict ip;

void loop()
{
#pragma scop

    for(int i = 0; i < 256 - 1; i++)
    {
        off = inc + i;
        sum += a[off] * aa[j - 1][ip[i]];
    }

#pragma endscop
}
