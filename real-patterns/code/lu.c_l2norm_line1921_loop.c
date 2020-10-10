#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int i;
extern int ist;
extern int iend;
extern int j;
extern int jst;
extern int jend;
extern int k;
extern int nz0;
extern double sum0;
extern double  v[64][64 / 2 * 2 + 1][64 / 2 * 2 + 1][5] ;
extern double sum1;
extern double sum2;
extern double sum3;
extern double sum4;

void loop()
{
#pragma scop

    for(i = ist; i <= iend; i++)
    {
        for(j = jst; j <= jend; j++)
        {
            for(k = 1; k <= nz0 - 2; k++)
            {
                sum0 = sum0 + v[i][j][k][0] * v[i][j][k][0];
                sum1 = sum1 + v[i][j][k][1] * v[i][j][k][1];
                sum2 = sum2 + v[i][j][k][2] * v[i][j][k][2];
                sum3 = sum3 + v[i][j][k][3] * v[i][j][k][3];
                sum4 = sum4 + v[i][j][k][4] * v[i][j][k][4];
            }
        }
    }

#pragma endscop
}
