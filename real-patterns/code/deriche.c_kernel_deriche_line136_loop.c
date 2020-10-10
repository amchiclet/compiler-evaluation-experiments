#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int j;
extern int h;
extern float tp1;
extern float tp2;
extern float yp1;
extern float yp2;
extern int i;
extern int w;
extern float  y2[4096 + 0][2160 + 0] ;
extern float a7;
extern float a8;
extern float b1;
extern float b2;
extern float  imgOut[4096 + 0][2160 + 0] ;

void loop()
{
#pragma scop

    for(j = 0; j < h; j++)
    {
        tp1 = 0.0f;
        tp2 = 0.0f;
        yp1 = 0.0f;
        yp2 = 0.0f;
        for(i = w - 1; i >= 0; i--)
        {
            y2[i][j] = a7 * tp1 + a8 * tp2 + b1 * yp1 + b2 * yp2;
            tp2 = tp1;
            tp1 = imgOut[i][j];
            yp2 = yp1;
            yp1 = y2[i][j];
        }
    }

#pragma endscop
}
