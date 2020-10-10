#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern long k;
extern long kn;
extern long j;
extern long jn;
extern double  Zu[7][101] ;
extern double  Xtra[40] ;
extern double  Za[7][101] ;
extern double  Zz[7][101] ;
extern double  Zb[7][101] ;
extern double  Zv[7][101] ;
extern double  Zr[7][101] ;

void loop()
{
#pragma scop

    for(k = 1; k < kn; k++)
    {
        for(j = 1; j < jn; j++)
        {
            Zu[k][j] += Xtra[32] *(Za[k][j] *(Zz[k][j] - Zz[k][j + 1]) - Za[k][j - 1] *(Zz[k][j] - Zz[k][j - 1]) - Zb[k][j] *(Zz[k][j] - Zz[k - 1][j]) + Zb[k + 1][j] *(Zz[k][j] - Zz[k + 1][j]));
            Zv[k][j] += Xtra[32] *(Za[k][j] *(Zr[k][j] - Zr[k][j + 1]) - Za[k][j - 1] *(Zr[k][j] - Zr[k][j - 1]) - Zb[k][j] *(Zr[k][j] - Zr[k - 1][j]) + Zb[k + 1][j] *(Zr[k][j] - Zr[k + 1][j]));
        }
    }

#pragma endscop
}
