#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern long I;
extern long N2;
extern double  E1[5] ;
extern double T;

void loop()
{
#pragma scop

    for(I = 1; I <= N2; I++)
    {
        E1[1] =(E1[1] + E1[2] + E1[3] - E1[4]) * T;
        E1[2] =(E1[1] + E1[2] - E1[3] + E1[4]) * T;
        E1[3] =(E1[1] - E1[2] + E1[3] + E1[4]) * T;
        E1[4] =(-E1[1] + E1[2] + E1[3] + E1[4]) * T;
    }

#pragma endscop
}
