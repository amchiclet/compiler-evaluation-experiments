#include <inttypes.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
extern int i;
extern double  energy[1024] ;
extern double  power[513] ;

void loop()
{
#pragma scop

    for(i = 1; i < 513; i++)
    {
        if(energy[i] < 1E-20) power[i] = - 200.0 + 90.3090;
        else power[i] = 10 * log10(energy[i]) + 90.3090;
    }

#pragma endscop
}
