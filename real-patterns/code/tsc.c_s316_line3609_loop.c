#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern float  a[32000] ;
extern float x;

void loop()
{
#pragma scop

    for(int i = 1; i < 32000; ++i)
    {
        if(a[i] < x)
        {
            x = a[i];
        }
    }

#pragma endscop
}
