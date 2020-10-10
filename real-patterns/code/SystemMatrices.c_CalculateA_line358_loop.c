#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int i;
extern int j;
extern double ** restrict A01;
extern double  temp1[4 * 4][4 * 4] ;
extern double  temp2[4 * 4][4 * 4] ;
extern double ** restrict A0bar1;
extern double  temp3[4 * 4][4 * 4] ;
extern double  temp4[4 * 4][4 * 4] ;

void loop()
{
#pragma scop

    for(i = 0; i < 4 * 4; i++)
    {
        for(j = 0; j < 4 * 4; j++)
        {
            A01[i][j] += temp1[i][j] + temp2[i][j];
            A0bar1[i][j] += temp3[i][j] + temp4[i][j];
        }
    }

#pragma endscop
}
