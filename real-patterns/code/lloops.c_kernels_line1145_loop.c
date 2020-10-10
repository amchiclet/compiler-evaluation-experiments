#include <inttypes.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
extern long j;
extern long ng;
extern long k;
extern long nz;
extern double  Vy[25][101] ;
extern double  Vh[7][101] ;
extern double  Xtra[40] ;
extern double ar;
extern double br;
extern double  Vf[7][101] ;
extern double  Vg[7][101] ;
extern double  Vs[7][101] ;

void loop()
{
#pragma scop

    for(j = 1; j < ng; j++)
    {
        for(k = 1; k < nz; k++)
        {
            if(j + 1 >= ng)
            {
                Vy[j][k] = 0.0;
                continue;
            }
            if(Vh[j + 1][k] > Vh[j][k])
            {
                Xtra[36] = ar;
            }
            else
            {
                Xtra[36] = br;
            }
            if(Vf[j][k] < Vf[j][k - 1])
            {
                if(Vh[j][k - 1] > Vh[j + 1][k - 1]) Xtra[30] = Vh[j][k - 1];
                else Xtra[30] = Vh[j + 1][k - 1];
                Xtra[32] = Vf[j][k - 1];
            }
            else
            {
                if(Vh[j][k] > Vh[j + 1][k]) Xtra[30] = Vh[j][k];
                else Xtra[30] = Vh[j + 1][k];
                Xtra[32] = Vf[j][k];
            }
            Vy[j][k] = sqrt(Vg[j][k] * Vg[j][k] + Xtra[30] * Xtra[30]) * Xtra[36] / Xtra[32];
            if(k + 1 >= nz)
            {
                Vs[j][k] = 0.0;
                continue;
            }
            if(Vf[j][k] < Vf[j - 1][k])
            {
                if(Vg[j - 1][k] > Vg[j - 1][k + 1]) Xtra[30] = Vg[j - 1][k];
                else Xtra[30] = Vg[j - 1][k + 1];
                Xtra[32] = Vf[j - 1][k];
                Xtra[36] = br;
            }
            else
            {
                if(Vg[j][k] > Vg[j][k + 1]) Xtra[30] = Vg[j][k];
                else Xtra[30] = Vg[j][k + 1];
                Xtra[32] = Vf[j][k];
                Xtra[36] = ar;
            }
            Vs[j][k] = sqrt(Vh[j][k] * Vh[j][k] + Xtra[30] * Xtra[30]) * Xtra[36] / Xtra[32];
        }
    }

#pragma endscop
}
