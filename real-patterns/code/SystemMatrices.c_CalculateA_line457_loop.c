#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int i;
extern int j;
extern double ** restrict AT00;
extern double  BT00[4 * 4][4 * 4] ;
extern double ** restrict AT10;
extern double  BT10[4 * 4][4 * 4] ;
extern double ** restrict AT01;
extern double  BT01[4 * 4][4 * 4] ;
extern double ** restrict AT11;
extern double  BT11[4 * 4][4 * 4] ;
extern double ** restrict ATbar10;
extern double  BTbar10[4 * 4][4 * 4] ;
extern double ** restrict AT0bar1;
extern double  BT0bar1[4 * 4][4 * 4] ;
extern double ** restrict AT1bar1;
extern double  BT1bar1[4 * 4][4 * 4] ;
extern double ** restrict ATbar11;
extern double  BTbar11[4 * 4][4 * 4] ;
extern double ** restrict ATbar1bar1;
extern double  BTbar1bar1[4 * 4][4 * 4] ;

void loop()
{
#pragma scop

    for(i = 0; i < 4 * 4; i++)
    {
        for(j = 0; j < 4 * 4; j++)
        {
            AT00[i][j] = BT00[j][i];
            AT10[i][j] = BT10[j][i];
            AT01[i][j] = BT01[j][i];
            AT11[i][j] = BT11[j][i];
            ATbar10[i][j] = BTbar10[j][i];
            AT0bar1[i][j] = BT0bar1[j][i];
            AT1bar1[i][j] = BT1bar1[j][i];
            ATbar11[i][j] = BTbar11[j][i];
            ATbar1bar1[i][j] = BTbar1bar1[j][i];
        }
    }

#pragma endscop
}
