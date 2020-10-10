#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern float  a[32000] ;
extern float s;
extern float  d[32000] ;
extern float  b[32000] ;
extern float  c[32000] ;
extern float  e[32000] ;
extern float  aa[256][256] ;

void loop()
{
#pragma scop

    for(int i = 0; i < 256; ++i)
    {
        if(a[i] > 0.)
        {
            s = d[i] * d[i];
        }
        b[i] = s * c[i] + d[i];
        e[i] =(s +((float )1.)) * aa[0][i];
    }

#pragma endscop
}
