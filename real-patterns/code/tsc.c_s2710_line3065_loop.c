#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern float  a[32000] ;
extern float  b[32000] ;
extern float  d[32000] ;
extern float  c[32000] ;
extern float  e[32000] ;
extern float x;

void loop()
{
#pragma scop

    for(int i = 0; i < 32000; i++)
    {
        if(a[i] > b[i])
        {
            a[i] += b[i] * d[i];
            if(32000 > 10)
            {
                c[i] += d[i] * d[i];
            }
            else
            {
                c[i] = d[i] * e[i] +((float )1.);
            }
        }
        else
        {
            b[i] = a[i] + e[i] * e[i];
            if(x >((float )0.))
            {
                c[i] = a[i] + d[i] * d[i];
            }
            else
            {
                c[i] += e[i] * e[i];
            }
        }
    }

#pragma endscop
}
