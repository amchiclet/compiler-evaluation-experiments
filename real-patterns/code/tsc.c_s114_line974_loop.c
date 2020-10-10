#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern float  aa[256][256] ;
extern float  bb[256][256] ;

void loop()
{
#pragma scop

    for(int i = 0; i < 256; i++)
    {
        for(int j = 0; j < i; j++)
        {
            aa[i][j] = aa[j][i] + bb[i][j];
        }
    }

#pragma endscop
}
