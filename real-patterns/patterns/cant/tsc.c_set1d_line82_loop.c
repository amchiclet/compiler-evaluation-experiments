#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern float  arr[32000] ;

void loop()
{
#pragma scop

    for(int i = 0; i < 32000; i++)
    {
        arr[i] =(1. /((float )(i + 1)));
    }

#pragma endscop
}
