#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern float  a[32000] ;
extern float  b[32000] ;
extern float  c[32000] ;

void loop()
{
#pragma scop

    for(int i = 0; i < 32000; i++)
    {
        if(a[i] > b[i])
        {
            a[i] += b[i] * c[i];
        }
    }

#pragma endscop
}
