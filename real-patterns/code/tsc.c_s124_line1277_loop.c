#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern float  b[32000] ;
extern int j;
extern float  a[32000] ;
extern float  d[32000] ;
extern float  e[32000] ;
extern float  c[32000] ;

void loop()
{
#pragma scop

    for(int i = 0; i < 32000; i++)
    {
        if(b[i] >((float )0.))
        {
            j++;
            a[j] = b[i] + d[i] * e[i];
        }
        else
        {
            j++;
            a[j] = c[i] + d[i] * e[i];
        }
    }

#pragma endscop
}
