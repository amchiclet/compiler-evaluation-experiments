#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern long k;
extern long Inner_loops;
extern double  Vx[1001] ;
extern double  Ex1[1001] ;
extern double  Xx[1001] ;
extern double  Xi[1001] ;
extern double  Dex1[1001] ;
extern double  Xtra[40] ;
extern long  Ir[1001] ;
extern double  Rx[1001] ;

void loop()
{
#pragma scop

    for(k = 0; k < Inner_loops; k++)
    {
        Vx[k] = Vx[k] + Ex1[k] +(Xx[k] - Xi[k]) * Dex1[k];
        Xx[k] = Xx[k] + Vx[k] + Xtra[27];
        Ir[k] =((long )Xx[k]);
        Rx[k] = Xx[k] - Ir[k];
        Ir[k] =(Ir[k] &(2048 - 1)) + 1;
        Xx[k] = Rx[k] + Ir[k];
    }

#pragma endscop
}
