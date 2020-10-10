#include <inttypes.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
extern int i;
extern int sblimit;
extern double max;
extern double  scale[32] ;
extern double  spike[32] ;
extern double  ltmin[32] ;

void loop()
{
#pragma scop

    for(i = 0; i < sblimit; i++)
    {
        max = 20 * log10(scale[i] * 32768) - 10;
        if(spike[i] > max) max = spike[i];
        max -= ltmin[i];
        ltmin[i] = max;
    }

#pragma endscop
}
