#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int i;
extern int n;
extern int m;
extern int j;
extern int ln;
typedef short int16_t;
extern int16_t  fft_rev[512] ;

void loop()
{
#pragma scop

    for(i = 0; i < n; i++)
    {
        m = 0;
        for(j = 0; j < ln; j++)
        {
            m |=(i >> j & 1) << ln - j - 1;
        }
        fft_rev[i] = m;
    }

#pragma endscop
}
