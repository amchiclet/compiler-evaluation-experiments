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
extern double  phi2[64 + 2][64 + 2] ;
extern double  u[64][64 / 2 * 2 + 1][64 / 2 * 2 + 1][5] ;
extern int ifin;

void loop()
{
#pragma scop

    for(j = jbeg; j <= jfin; j++)
    {
        jglob = j;
        for(k = ki1; k <= ki2; k++)
        {
            phi2[j][k] = 0.40e+00 *(u[ifin][j][k][4] - 0.50 *(u[ifin][j][k][1] * u[ifin][j][k][1] + u[ifin][j][k][2] * u[ifin][j][k][2] + u[ifin][j][k][3] * u[ifin][j][k][3]) / u[ifin][j][k][0]);
        }
    }

#pragma endscop
}
