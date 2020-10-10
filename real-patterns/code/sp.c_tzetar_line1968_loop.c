#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int i;
extern int  grid_points[3] ;
extern int j;
extern int k;
extern double xvel;
extern double  us[64 / 2 * 2 + 1][64 / 2 * 2 + 1][64 / 2 * 2 + 1] ;
extern double yvel;
extern double  vs[64 / 2 * 2 + 1][64 / 2 * 2 + 1][64 / 2 * 2 + 1] ;
extern double zvel;
extern double  ws[64 / 2 * 2 + 1][64 / 2 * 2 + 1][64 / 2 * 2 + 1] ;
extern double ac;
extern double  speed[64 / 2 * 2 + 1][64 / 2 * 2 + 1][64 / 2 * 2 + 1] ;
extern double acinv;
extern double  ainv[64 / 2 * 2 + 1][64 / 2 * 2 + 1][64 / 2 * 2 + 1] ;
extern double ac2u;
extern double r1;
extern double  rhs[5][64 / 2 * 2 + 1][64 / 2 * 2 + 1][64 / 2 * 2 + 1] ;
extern double r2;
extern double r3;
extern double r4;
extern double r5;
extern double uzik1;
extern double  u[5][64 / 2 * 2 + 1][64 / 2 * 2 + 1][64 / 2 * 2 + 1] ;
extern double btuz;
extern double bt;
extern double t1;
extern double t2;
extern double t3;
extern double  qs[64 / 2 * 2 + 1][64 / 2 * 2 + 1][64 / 2 * 2 + 1] ;
extern double c2iv;

void loop()
{
#pragma scop

    for(i = 1; i <= grid_points[0] - 2; i++)
    {
        for(j = 1; j <= grid_points[1] - 2; j++)
        {
            for(k = 1; k <= grid_points[2] - 2; k++)
            {
                xvel = us[i][j][k];
                yvel = vs[i][j][k];
                zvel = ws[i][j][k];
                ac = speed[i][j][k];
                acinv = ainv[i][j][k];
                ac2u = ac * ac;
                r1 = rhs[0][i][j][k];
                r2 = rhs[1][i][j][k];
                r3 = rhs[2][i][j][k];
                r4 = rhs[3][i][j][k];
                r5 = rhs[4][i][j][k];
                uzik1 = u[0][i][j][k];
                btuz = bt * uzik1;
                t1 = btuz * acinv *(r4 + r5);
                t2 = r3 + t1;
                t3 = btuz *(r4 - r5);
                rhs[0][i][j][k] = t2;
                rhs[1][i][j][k] = -uzik1 * r2 + xvel * t2;
                rhs[2][i][j][k] = uzik1 * r1 + yvel * t2;
                rhs[3][i][j][k] = zvel * t2 + t3;
                rhs[4][i][j][k] = uzik1 *(-xvel * r2 + yvel * r1) + qs[i][j][k] * t2 + c2iv * ac2u * t1 + zvel * t3;
            }
        }
    }

#pragma endscop
}
