#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int j;
extern int jbeg;
extern int jfin1;
extern int k;
extern int ki1;
extern int ki2;
extern double frc3;
extern double  phi1[64 + 2][64 + 2] ;
extern double  phi2[64 + 2][64 + 2] ;

void loop()
{
#pragma scop

    for(j = jbeg; j <= jfin1; j++)
    {
        for(k = ki1; k <= ki2 - 1; k++)
        {
            frc3 = frc3 +(phi1[j][k] + phi1[j + 1][k] + phi1[j][k + 1] + phi1[j + 1][k + 1] + phi2[j][k] + phi2[j + 1][k] + phi2[j][k + 1] + phi2[j + 1][k + 1]);
        }
    }

#pragma endscop
}
