#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern float s;
extern float  b[32000] ;
extern float  c[32000] ;
extern float  a[32000] ;
extern float  d[32000] ;
extern float  e[32000] ;

void loop()
{
#pragma scop

    for(int i = 0; i < 32000; i++)
    {
        s = b[i] + c[i];
        b[i] = a[i] + d[i];
        a[i] = s * e[i];
    }

#pragma endscop
}
