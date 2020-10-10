#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int stride;
extern float  arr[32000] ;
extern float value;

void loop()
{
#pragma scop

    for(int i = 0; i < 32000; i += stride)
    {
        arr[i] = value;
    }

#pragma endscop
}
