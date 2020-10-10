#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern float  e[32000] ;
extern float t;
extern float  a[32000] ;
extern float  c[32000] ;
extern float  d[32000] ;
extern float  b[32000] ;

void loop()
{
#pragma scop

    for(int i = 0; i < 32000; i++)
    {
        if(e[i] >= t)
        {
            a[i] += c[i] * d[i];
            b[i] += c[i] * c[i];
        }
    }

#pragma endscop
}
