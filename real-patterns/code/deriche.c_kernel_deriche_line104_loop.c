#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int i;
extern int w;
extern float yp1;
extern float yp2;
extern float xp1;
extern float xp2;
extern int j;
extern int h;
extern float  y2[4096 + 0][2160 + 0] ;
extern float a3;
extern float a4;
extern float b1;
extern float b2;
extern float  imgIn[4096 + 0][2160 + 0] ;

void loop()
{
#pragma scop

    for(i = 0; i < w; i++)
    {
        yp1 = 0.0f;
        yp2 = 0.0f;
        xp1 = 0.0f;
        xp2 = 0.0f;
        for(j = h - 1; j >= 0; j--)
        {
            y2[i][j] = a3 * xp1 + a4 * xp2 + b1 * yp1 + b2 * yp2;
            xp2 = xp1;
            xp1 = imgIn[i][j];
            yp2 = yp1;
            yp1 = y2[i][j];
        }
    }

#pragma endscop
}
