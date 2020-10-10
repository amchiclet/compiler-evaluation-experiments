#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int i;
extern int ibeg;
extern int ifin1;
extern int j;
extern int jbeg;
extern int jfin1;
extern double frc1;
extern double  phi1[64 + 2][64 + 2] ;
extern double  phi2[64 + 2][64 + 2] ;

void loop()
{
#pragma scop

    for(i = ibeg; i <= ifin1; i++)
    {
        for(j = jbeg; j <= jfin1; j++)
        {
            frc1 = frc1 +(phi1[i][j] + phi1[i + 1][j] + phi1[i][j + 1] + phi1[i + 1][j + 1] + phi2[i][j] + phi2[i + 1][j] + phi2[i][j + 1] + phi2[i + 1][j + 1]);
        }
    }

#pragma endscop
}
