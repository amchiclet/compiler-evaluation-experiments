#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int i;
extern int ist;
extern int iend;
extern int j;
extern int jst;
extern int jend;
extern int m;
extern double  v[64][64 / 2 * 2 + 1][64 / 2 * 2 + 1][5] ;
extern int k;
extern double omega;
extern double  ldz[64][64][5][5] ;

void loop()
{
#pragma scop

    for(i = ist; i <= iend; i++)
    {
        for(j = jst; j <= jend; j++)
        {
            for(m = 0; m < 5; m++)
            {
                v[i][j][k][m] = v[i][j][k][m] - omega *(ldz[i][j][m][0] * v[i][j][k - 1][0] + ldz[i][j][m][1] * v[i][j][k - 1][1] + ldz[i][j][m][2] * v[i][j][k - 1][2] + ldz[i][j][m][3] * v[i][j][k - 1][3] + ldz[i][j][m][4] * v[i][j][k - 1][4]);
            }
        }
    }

#pragma endscop
}
