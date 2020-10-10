#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern float  a[32000] ;
extern float  aa[256][256] ;
extern float  bb[256][256] ;

void loop()
{
#pragma scop

    for(int i = 1; i < 256; i++)
    {
        for(int j = 0; j < 256; j++)
        {
            a[i] = aa[j][i] - a[i - 1];
            aa[j][i] = a[i] + bb[j][i];
        }
    }

#pragma endscop
}
