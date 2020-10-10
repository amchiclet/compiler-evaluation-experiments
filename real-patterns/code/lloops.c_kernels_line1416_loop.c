#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern long k;
extern long Inner_loops;
extern double di;
extern double  Y[1001] ;
extern double  G[1001] ;
extern double  Xx[1001] ;
extern double  Xtra[40] ;
extern double dn;
extern double  Z[1001] ;
extern double  X[1001] ;
extern double  W[1001] ;
extern double  V[1001] ;
extern double  U[1001] ;
extern double  Vx[1001] ;

void loop()
{
#pragma scop

    for(k = 0; k < Inner_loops; k++)
    {
        di = Y[k] - G[k] /(Xx[k] + Xtra[15]);
        dn = 0.2;
        if(di)
        {
            dn = Z[k] / di;
            if(Xtra[36] < dn) dn = Xtra[36];
            if(Xtra[32] > dn) dn = Xtra[32];
        }
        X[k] =((W[k] + V[k] * dn) * Xx[k] + U[k]) /(Vx[k] + V[k] * dn);
        Xx[k + 1] =(X[k] - Xx[k]) * dn + Xx[k];
    }

#pragma endscop
}
