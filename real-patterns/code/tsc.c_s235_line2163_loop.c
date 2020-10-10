#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern float  a[32000] ;
extern float  b[32000] ;
extern float  c[32000] ;
extern float  aa[256][256] ;
extern float  bb[256][256] ;

void loop()
{
#pragma scop

    for(int i = 0; i < 256; i++)
    {
        a[i] += b[i] * c[i];
        for(int j = 1; j < 256; j++)
        {
            aa[j][i] = aa[j - 1][i] + bb[j][i] * a[i];
        }
    }

#pragma endscop
}
