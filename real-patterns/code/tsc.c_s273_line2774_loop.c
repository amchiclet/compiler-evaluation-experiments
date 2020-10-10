#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern float  a[32000] ;
extern float  d[32000] ;
extern float  e[32000] ;
extern float  b[32000] ;
extern float  c[32000] ;

void loop()
{
#pragma scop

    for(int i = 0; i < 32000; i++)
    {
        a[i] += d[i] * e[i];
        if(a[i] <((float )0.)) b[i] += d[i] * e[i];
        c[i] += a[i] * d[i];
    }

#pragma endscop
}
