#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern float  a[32000] ;

void loop()
{
#pragma scop

    for(int i = 0; i < 32000; i++)
    {
        a[i] = a[0];
    }

#pragma endscop
}
