#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern float  bb[256][256] ;
extern float  array[256 * 256] ;
extern int k;
extern float  cc[256][256] ;

void loop()
{
#pragma scop

    for(int i = 0; i < 256; i++)
    {
        for(int j = 1; j < 256; j++)
        {
            bb[j][i] = bb[j - 1][i] + array[k - 1] * cc[j][i];
            ++k;
        }++k;
    }

#pragma endscop
}
