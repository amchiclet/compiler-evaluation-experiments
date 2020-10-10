#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern float temp;
extern float  array[256 * 256] ;

void loop()
{
#pragma scop

    for(int i = 0; i < 32000; i++)
    {
        temp += array[i];
    }

#pragma endscop
}
