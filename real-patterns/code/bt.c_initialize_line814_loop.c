#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int i;
extern int  grid_points[3] ;
extern double xi;
extern double dnxm1;
extern int j;
extern double eta;
extern double dnym1;
extern double  temp[5] ;
extern double  ce[5][13] ;
extern double zeta;
extern double  u[(64 + 1) / 2 * 2 + 1][(64 + 1) / 2 * 2 + 1][(64 + 1) / 2 * 2 + 1][5] ;
extern int k;

void loop()
{
#pragma scop

    for(i = 0; i < grid_points[0]; i++)
    {
        xi =((double )i) * dnxm1;
        for(j = 0; j < grid_points[1]; j++)
        {
            int m;
            eta =((double )j) * dnym1;
            {
                for(m = 0; m < 5; m++)
                {
                    temp[m] = ce[m][0] + xi *(ce[m][1] + xi *(ce[m][4] + xi *(ce[m][7] + xi * ce[m]['\n']))) + eta *(ce[m][2] + eta *(ce[m][5] + eta *(ce[m][8] + eta * ce[m][11]))) + zeta *(ce[m][3] + zeta *(ce[m][6] + zeta *(ce[m][9] + zeta * ce[m][12])));
                }
            };
            for(m = 0; m < 5; m++)
            {
                u[i][j][k][m] = temp[m];
            }
        }
    }

#pragma endscop
}
