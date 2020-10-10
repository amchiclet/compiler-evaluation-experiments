#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern long k;
extern long kn;
extern long j;
extern long jn;
extern double  Zr[7][101] ;
extern double  Xtra[40] ;
extern double  Zu[7][101] ;
extern double  Zz[7][101] ;
extern double  Zv[7][101] ;

void loop()
{
#pragma scop

    for(k = 1; k < kn; k++)
    {
        for(j = 1; j < jn; j++)
        {
            Zr[k][j] = Zr[k][j] + Xtra[36] * Zu[k][j];
            Zz[k][j] = Zz[k][j] + Xtra[36] * Zv[k][j];
        }
    }

#pragma endscop
}
