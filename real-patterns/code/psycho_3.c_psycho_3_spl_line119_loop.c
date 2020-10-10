#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int i;
extern double  Xmax[32] ;
extern double * restrict power;

void loop()
{
#pragma scop

    for(i = 1; i < 513; i++)
    {
        int index = i - 1 >> 4;
        if(Xmax[index] < power[i]) Xmax[index] = power[i];
    }

#pragma endscop
}
