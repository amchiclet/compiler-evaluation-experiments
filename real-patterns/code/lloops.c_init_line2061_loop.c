#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern long i;
extern double  Dex[1001] ;
extern double dw;
extern double  Grd[1001] ;
extern long  Ix[1001] ;

void loop()
{
#pragma scop

    for(i = 0; i < 1001; i++)
    {
        Dex[i] = dw * Dex[i];
        Grd[i] = Ix[i];
    }

#pragma endscop
}
