#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern float  a[32000] ;
extern float  b[32000] ;
extern int * __restrict__ restrict ip;
extern float s;

void loop()
{
#pragma scop

    for(int i = 0; i < 32000; i++)
    {
        a[i] += b[ip[i]] * s;
    }

#pragma endscop
}
