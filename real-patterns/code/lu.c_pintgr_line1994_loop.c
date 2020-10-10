#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int i;
extern int ibeg;
extern int ifin;
extern int iglob;
extern int j;
extern int jbeg;
extern int jfin;
extern int jglob;
extern int k;
extern int ki1;
extern double  phi1[64 + 2][64 + 2] ;
extern double  u[64][64 / 2 * 2 + 1][64 / 2 * 2 + 1][5] ;
extern int ki2;
extern double  phi2[64 + 2][64 + 2] ;

void loop()
{
#pragma scop

    for(i = ibeg; i <= ifin; i++)
    {
        iglob = i;
        for(j = jbeg; j <= jfin; j++)
        {
            jglob = j;
            k = ki1;
            phi1[i][j] = 0.40e+00 *(u[i][j][k][4] - 0.50 *(u[i][j][k][1] * u[i][j][k][1] + u[i][j][k][2] * u[i][j][k][2] + u[i][j][k][3] * u[i][j][k][3]) / u[i][j][k][0]);
            k = ki2;
            phi2[i][j] = 0.40e+00 *(u[i][j][k][4] - 0.50 *(u[i][j][k][1] * u[i][j][k][1] + u[i][j][k][2] * u[i][j][k][2] + u[i][j][k][3] * u[i][j][k][3]) / u[i][j][k][0]);
        }
    }

#pragma endscop
}
