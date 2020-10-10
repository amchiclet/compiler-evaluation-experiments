#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int k;
extern int j;
extern int i;
extern double  trhs[2400][5][5][5] ;
extern int iel;
extern double  bm1_s[6][5][5][5] ;
extern int isize;
extern double  ta1[2400][5][5][5] ;
extern double rdtime;
extern double  tempa[5][5][5] ;
extern double dtime;

void loop()
{
#pragma scop

    for(k = 0; k < 5; k++)
    {
        for(j = 0; j < 5; j++)
        {
            for(i = 0; i < 5; i++)
            {
                trhs[iel][k][j][i] = bm1_s[isize][k][j][i] *(ta1[iel][k][j][i] * rdtime + tempa[k][j][i]);
                ta1[iel][k][j][i] = ta1[iel][k][j][i] + tempa[k][j][i] * dtime;
            }
        }
    }

#pragma endscop
}
