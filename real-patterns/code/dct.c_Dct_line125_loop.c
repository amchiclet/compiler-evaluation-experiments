#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int i;
extern int j;
extern int j1;
extern float  b1[8] ;
extern float  d[8][8] ;
extern float  b[8] ;
extern float f0;
extern float f4;
extern float f6;
extern float f2;
extern float f7;
extern float f1;
extern float f3;
extern float f5;

void loop()
{
#pragma scop

    for(i = 0; i < 8; i++)
    {
        for(j = 0; j < 4; j++)
        {
            j1 = 7 - j;
            b1[j] = d[j][i] + d[j1][i];
            b1[j1] = d[j][i] - d[j1][i];
        }
        b[0] = b1[0] + b1[3];
        b[1] = b1[1] + b1[2];
        b[2] = b1[1] - b1[2];
        b[3] = b1[0] - b1[3];
        b[4] = b1[4];
        b[5] =(b1[6] - b1[5]) * f0;
        b[6] =(b1[6] + b1[5]) * f0;
        b[7] = b1[7];
        d[0][i] =(b[0] + b[1]) * f4;
        d[4][i] =(b[0] - b[1]) * f4;
        d[2][i] = b[2] * f6 + b[3] * f2;
        d[6][i] = b[3] * f6 - b[2] * f2;
        b1[4] = b[4] + b[5];
        b1[7] = b[7] + b[6];
        b1[5] = b[4] - b[5];
        b1[6] = b[7] - b[6];
        d[1][i] = b1[4] * f7 + b1[7] * f1;
        d[5][i] = b1[5] * f3 + b1[6] * f5;
        d[7][i] = b1[7] * f7 - b1[4] * f1;
        d[3][i] = b1[6] * f3 - b1[5] * f5;
    }

#pragma endscop
}
