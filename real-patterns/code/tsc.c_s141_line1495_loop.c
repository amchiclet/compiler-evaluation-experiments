#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int k;
extern float  array[256 * 256] ;
extern float  bb[256][256] ;

void loop()
{
#pragma scop

    for(int i = 0; i < 256; i++)
    {
        k =(i + 1) *(i + 1 - 1) / 2 +(i + 1) - 1;
        for(int j = i; j < 256; j++)
        {
            array[k] += bb[j][i];
            k += j + 1;
        }
    }

#pragma endscop
}
