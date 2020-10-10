#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int stride;
extern float  arr[256][256] ;
extern float value;

void loop()
{
#pragma scop

    for(int i = 0; i < 256; i++)
    {
        for(int j = 0; j < 256; j += stride)
        {
            arr[i][j] = value;
        }
    }

#pragma endscop
}
