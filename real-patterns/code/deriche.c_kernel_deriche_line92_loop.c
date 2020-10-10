#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int i;
extern int w;
extern float ym1;
extern float ym2;
extern float xm1;
extern int j;
extern int h;
extern float  y1[4096 + 0][2160 + 0] ;
extern float a1;
extern float  imgIn[4096 + 0][2160 + 0] ;
extern float a2;
extern float b1;
extern float b2;

void loop()
{
#pragma scop

    for(i = 0; i < w; i++)
    {
        ym1 = 0.0f;
        ym2 = 0.0f;
        xm1 = 0.0f;
        for(j = 0; j < h; j++)
        {
            y1[i][j] = a1 * imgIn[i][j] + a2 * xm1 + b1 * ym1 + b2 * ym2;
            xm1 = imgIn[i][j];
            ym2 = ym1;
            ym1 = y1[i][j];
        }
    }

#pragma endscop
}
