#include <inttypes.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
extern int i;
extern double * restrict scale;
extern double * restrict Lsb;
extern double  Xmax[32] ;

void loop()
{
#pragma scop

    for(i = 0; i < 32; i++)
    {
        double val = 20 * log10(scale[i] * 32768) - 10;
        Lsb[i] =(Xmax[i] > val?Xmax[i] : val);
    }

#pragma endscop
}
