#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int i;
extern int ibeg;
extern int ifin;
extern int iglob;
extern int k;
extern int ki1;
extern int ki2;
extern double  phi1[64 + 2][64 + 2] ;
extern double  u[64][64 / 2 * 2 + 1][64 / 2 * 2 + 1][5] ;
extern int jbeg;

void loop()
{
#pragma scop

    for(i = ibeg; i <= ifin; i++)
    {
        iglob = i;
        for(k = ki1; k <= ki2; k++)
        {
            phi1[i][k] = 0.40e+00 *(u[i][jbeg][k][4] - 0.50 *(u[i][jbeg][k][1] * u[i][jbeg][k][1] + u[i][jbeg][k][2] * u[i][jbeg][k][2] + u[i][jbeg][k][3] * u[i][jbeg][k][3]) / u[i][jbeg][k][0]);
        }
    }

#pragma endscop
}
