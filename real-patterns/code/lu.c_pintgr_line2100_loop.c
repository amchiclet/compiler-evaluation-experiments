#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int j;
extern int jbeg;
extern int jfin;
extern int jglob;
extern int k;
extern int ki1;
extern int ki2;
extern double  phi1[64 + 2][64 + 2] ;
extern double  u[64][64 / 2 * 2 + 1][64 / 2 * 2 + 1][5] ;
extern int ibeg;

void loop()
{
#pragma scop

    for(j = jbeg; j <= jfin; j++)
    {
        jglob = j;
        for(k = ki1; k <= ki2; k++)
        {
            phi1[j][k] = 0.40e+00 *(u[ibeg][j][k][4] - 0.50 *(u[ibeg][j][k][1] * u[ibeg][j][k][1] + u[ibeg][j][k][2] * u[ibeg][j][k][2] + u[ibeg][j][k][3] * u[ibeg][j][k][3]) / u[ibeg][j][k][0]);
        }
    }

#pragma endscop
}
