#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern float  a[32000] ;
extern float s1;
extern float s2;
extern float  b[32000] ;
extern float  c[32000] ;
extern float  d[32000] ;

void loop()
{
#pragma scop

    for(int i = 1; i < 32000; ++i)
    {
        a[i] = a[i - 1] + s1 + s2 + b[i] + c[i] + d[i];
    }

#pragma endscop
}
