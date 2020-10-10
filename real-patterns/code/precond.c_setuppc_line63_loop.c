#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int k;
extern int j;
extern int i;
extern int q;
extern double  dpcelm[2400][5][5][5] ;
extern int ie;
extern double  g1m1_s[6][5][5][5] ;
extern int isize;
extern double  dxtm1_2[5][5] ;
extern double rdtime;
extern double  bm1_s[6][5][5][5] ;

void loop()
{
#pragma scop

    for(k = 0; k < 5; k++)
    {
        for(j = 0; j < 5; j++)
        {
            for(i = 0; i < 5; i++)
            {
                for(q = 0; q < 5; q++)
                {
                    dpcelm[ie][k][j][i] = dpcelm[ie][k][j][i] + g1m1_s[isize][k][j][q] * dxtm1_2[q][i] + g1m1_s[isize][k][q][i] * dxtm1_2[q][j] + g1m1_s[isize][q][j][i] * dxtm1_2[q][k];
                }
                dpcelm[ie][k][j][i] = 0.005 * dpcelm[ie][k][j][i] + rdtime * bm1_s[isize][k][j][i];
            }
        }
    }

#pragma endscop
}
