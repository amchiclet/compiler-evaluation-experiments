#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern float  a[32000] ;
extern float sum;

void loop()
{
#pragma scop

    for(int i = 0; i < 32000; i++)
    {
        if(a[i] >((float )0.))
        {
            sum += a[i];
        }
    }

#pragma endscop
}
