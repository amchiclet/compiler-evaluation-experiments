#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern float  arr[256][256] ;

void loop()
{
#pragma scop

    for(int i = 0; i < 256; i++)
    {
        for(int j = 0; j < 256; j++)
        {
            arr[i][j] =(1. /((float )((i + 1) *(i + 1))));
        }
    }

#pragma endscop
}
