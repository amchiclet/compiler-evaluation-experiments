#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int i;
extern int j;
extern double ** restrict A11;
extern double  temp1[4 * 4][4 * 4] ;
extern double ** restrict Abar11;
extern double  temp2[4 * 4][4 * 4] ;
extern double ** restrict A1bar1;
extern double  temp3[4 * 4][4 * 4] ;
extern double ** restrict Abar1bar1;
extern double  temp4[4 * 4][4 * 4] ;

void loop()
{
#pragma scop

    for(i = 0; i < 4 * 4; i++)
    {
        for(j = 0; j < 4 * 4; j++)
        {
            A11[i][j] += temp1[i][j];
            Abar11[i][j] += temp2[i][j];
            A1bar1[i][j] += temp3[i][j];
            Abar1bar1[i][j] += temp4[i][j];
        }
    }

#pragma endscop
}
