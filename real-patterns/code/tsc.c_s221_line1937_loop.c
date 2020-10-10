#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern float  a[32000] ;
extern float  c[32000] ;
extern float  d[32000] ;
extern float  b[32000] ;

void loop()
{
#pragma scop

    for(int i = 1; i < 32000; i++)
    {
        a[i] += c[i] * d[i];
        b[i] = b[i - 1] + a[i] + d[i];
    }

#pragma endscop
}
