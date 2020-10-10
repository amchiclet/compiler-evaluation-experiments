#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern float  aa[256][256] ;
extern float  bb[256][256] ;
extern float  cc[256][256] ;
extern float  a[32000] ;
extern float  b[32000] ;
extern float  c[32000] ;
extern float  d[32000] ;

void loop()
{
#pragma scop

    for(int i = 0; i < 256; i++)
    {
        for(int j = 0; j < 256; j++)
        {
            aa[j][i] = aa[j][i] + bb[j][i] * cc[j][i];
        }
        a[i] = b[i] + c[i] * d[i];
    }

#pragma endscop
}
