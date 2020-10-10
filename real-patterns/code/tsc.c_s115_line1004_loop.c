#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern float  a[32000] ;
extern float  aa[256][256] ;

void loop()
{
#pragma scop

    for(int j = 0; j < 256; j++)
    {
        for(int i = j + 1; i < 256; i++)
        {
            a[i] -= aa[j][i] * a[j];
        }
    }

#pragma endscop
}
