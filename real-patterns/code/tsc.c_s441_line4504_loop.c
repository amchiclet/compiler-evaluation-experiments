#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern float  d[32000] ;
extern float  a[32000] ;
extern float  b[32000] ;
extern float  c[32000] ;

void loop()
{
#pragma scop

    for(int i = 0; i < 32000; i++)
    {
        if(d[i] <((float )0.))
        {
            a[i] += b[i] * c[i];
        }
        else if(d[i] ==((float )0.))
        {
            a[i] += b[i] * b[i];
        }
        else
        {
            a[i] += c[i] * c[i];
        }
    }

#pragma endscop
}
