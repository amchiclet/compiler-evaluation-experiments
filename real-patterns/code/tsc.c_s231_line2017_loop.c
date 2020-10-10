#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern float  aa[256][256] ;
extern float  bb[256][256] ;

void loop()
{
#pragma scop

    for(int i = 0; i < 256; ++i)
    {
        for(int j = 1; j < 256; j++)
        {
            aa[j][i] = aa[j - 1][i] + bb[j][i];
        }
    }

#pragma endscop
}
