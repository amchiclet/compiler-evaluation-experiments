#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern float  aa[256][256] ;

void loop()
{
#pragma scop

    for(int i = 0; i < 256; i++)
    {
        for(int j = 0; j < 256; j++)
        {
            aa[j][i] =((float )0.);
        }
        aa[i][i] =((float )1.);
    }

#pragma endscop
}
