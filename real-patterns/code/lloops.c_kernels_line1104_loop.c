#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern long k;
extern long Inner_loops;
extern double  Vx[1001] ;
extern double  Xx[1001] ;
extern long  Ix[1001] ;
extern double  Grd[1001] ;
extern double  Xi[1001] ;
extern double  Ex1[1001] ;
extern double  Ex[1001] ;
extern double  Dex1[1001] ;
extern double  Dex[1001] ;

void loop()
{
#pragma scop

    for(k = 0; k < Inner_loops; k++)
    {
        Vx[k] = 0.0;
        Xx[k] = 0.0;
        Ix[k] =((long )Grd[k]);
        Xi[k] =((double )Ix[k]);
        Ex1[k] = Ex[Ix[k] - 1];
        Dex1[k] = Dex[Ix[k] - 1];
    }

#pragma endscop
}
