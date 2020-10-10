#include <inttypes.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
extern int i;
extern double  window[1024] ;
extern double sqrt_8_over_3;

void loop()
{
#pragma scop

    for(i = 0; i < 1024; i++)
    {
        window[i] = sqrt_8_over_3 * 0.5 *(1 - cos(2.0 * 3.14159265358979 * i / 1024)) / 1024;
    }

#pragma endscop
}
