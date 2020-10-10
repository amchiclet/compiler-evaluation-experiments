#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern float  a[32000] ;
extern float  bb[256][256] ;

void loop()
{
#pragma scop

    for(int i = 1; i < 256; i++)
    {
        for(int j = 0; j <= i - 1; j++)
        {
            a[i] += bb[j][i] * a[i - j - 1];
        }
    }

#pragma endscop
}
