#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern float sumarray;
extern float  array[256 * 256] ;

void loop()
{
#pragma scop

    for(int i = 0; i < 256 * 256; i++)
    {
        sumarray += array[i];
    }

#pragma endscop
}
