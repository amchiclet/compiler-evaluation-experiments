#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int k;
extern int j;
extern int i;
extern double  r[5][5][5] ;
extern double  tm1[5][5][5] ;
extern double  g4m1_s[6][5][5][5] ;
extern int sizei;
extern double  tm2[5][5][5] ;
extern double  g5m1_s[6][5][5][5] ;
extern double  g6m1_s[6][5][5][5] ;
extern double  bm1_s[6][5][5][5] ;
extern double rdtime;
extern double  u[5][5][5] ;

void loop()
{
#pragma scop

    for(k = 0; k < 5; k++)
    {
        for(j = 0; j < 5; j++)
        {
            for(i = 0; i < 5; i++)
            {
                r[k][j][i] = 0.005 *(tm1[k][j][i] * g4m1_s[sizei][k][j][i] + tm2[k][j][i] * g5m1_s[sizei][k][j][i] + r[k][j][i] * g6m1_s[sizei][k][j][i]) + bm1_s[sizei][k][j][i] * rdtime * u[k][j][i];
            }
        }
    }

#pragma endscop
}
