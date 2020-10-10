#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int i;
extern int ibeg;
extern int ifin1;
extern int k;
extern int ki1;
extern int ki2;
extern double frc2;
extern double  phi1[64 + 2][64 + 2] ;
extern double  phi2[64 + 2][64 + 2] ;

void loop()
{
#pragma scop

    for(i = ibeg; i <= ifin1; i++)
    {
        for(k = ki1; k <= ki2 - 1; k++)
        {
            frc2 = frc2 +(phi1[i][k] + phi1[i + 1][k] + phi1[i][k + 1] + phi1[i + 1][k + 1] + phi2[i][k] + phi2[i + 1][k] + phi2[i][k + 1] + phi2[i + 1][k + 1]);
        }
    }

#pragma endscop
}
