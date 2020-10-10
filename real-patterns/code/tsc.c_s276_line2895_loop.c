#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int mid;
extern float  a[32000] ;
extern float  b[32000] ;
extern float  c[32000] ;
extern float  d[32000] ;

void loop()
{
#pragma scop

    for(int i = 0; i < 32000; i++)
    {
        if(i + 1 < mid)
        {
            a[i] += b[i] * c[i];
        }
        else
        {
            a[i] += b[i] * d[i];
        }
    }

#pragma endscop
}
