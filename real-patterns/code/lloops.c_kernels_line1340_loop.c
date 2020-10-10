#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern long k;
extern long kn;
extern long j;
extern long jn;
extern double  Za[7][101] ;
extern double  Zp[7][101] ;
extern double  Zq[7][101] ;
extern double  Zr[7][101] ;
extern double  Zm[7][101] ;
extern double  Zb[7][101] ;

void loop()
{
#pragma scop

    for(k = 1; k < kn; k++)
    {
        for(j = 1; j < jn; j++)
        {
            Za[k][j] =(Zp[k + 1][j - 1] + Zq[k + 1][j - 1] - Zp[k][j - 1] - Zq[k][j - 1]) *(Zr[k][j] + Zr[k][j - 1]) /(Zm[k][j - 1] + Zm[k + 1][j - 1]);
            Zb[k][j] =(Zp[k][j - 1] + Zq[k][j - 1] - Zp[k][j] - Zq[k][j]) *(Zr[k][j] + Zr[k - 1][j]) /(Zm[k][j] + Zm[k][j - 1]);
        }
    }

#pragma endscop
}
