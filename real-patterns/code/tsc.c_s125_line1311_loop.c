#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int k;
extern float  array[256 * 256] ;
extern float  aa[256][256] ;
extern float  bb[256][256] ;
extern float  cc[256][256] ;

void loop()
{
#pragma scop

    for(int i = 0; i < 256; i++)
    {
        for(int j = 0; j < 256; j++)
        {
            k++;
            array[k] = aa[i][j] + bb[i][j] * cc[i][j];
        }
    }

#pragma endscop
}
