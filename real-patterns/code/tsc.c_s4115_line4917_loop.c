#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern float sum;
extern float  a[32000] ;
extern float  b[32000] ;
extern int * __restrict__ restrict ip;

void loop()
{
#pragma scop

    for(int i = 0; i < 32000; i++)
    {
        sum += a[i] * b[ip[i]];
    }

#pragma endscop
}
