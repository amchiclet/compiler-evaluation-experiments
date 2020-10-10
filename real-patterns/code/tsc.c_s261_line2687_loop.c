#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern float t;
extern float  a[32000] ;
extern float  b[32000] ;
extern float  c[32000] ;
extern float  d[32000] ;

void loop()
{
#pragma scop

    for(int i = 1; i < 32000; ++i)
    {
        t = a[i] + b[i];
        a[i] = t + c[i - 1];
        t = c[i] * d[i];
        c[i] = t;
    }

#pragma endscop
}
