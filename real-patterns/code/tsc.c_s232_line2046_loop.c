#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern float  aa[256][256] ;
extern float  bb[256][256] ;

void loop()
{
#pragma scop

    for(int j = 1; j < 256; j++)
    {
        for(int i = 1; i <= j; i++)
        {
            aa[j][i] = aa[j][i - 1] * aa[j][i - 1] + bb[j][i];
        }
    }

#pragma endscop
}
