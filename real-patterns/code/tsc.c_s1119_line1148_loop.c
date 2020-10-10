#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern float  aa[256][256] ;
extern float  bb[256][256] ;

void loop()
{
#pragma scop

    for(int i = 1; i < 256; i++)
    {
        for(int j = 0; j < 256; j++)
        {
            aa[i][j] = aa[i - 1][j] + bb[i][j];
        }
    }

#pragma endscop
}
