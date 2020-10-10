#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern float  a[32000] ;
extern float  cc[256][256] ;
extern float  bb[256][256] ;
extern float  d[32000] ;

void loop()
{
#pragma scop

    for(int i = 0; i < 256; i++)
    {
        for(int j = 1; j < 256; j++)
        {
            a[j] =((float )1.) - a[j - 1];
            cc[j][i] = a[j] + bb[j][i] * d[j];
        }
    }

#pragma endscop
}
