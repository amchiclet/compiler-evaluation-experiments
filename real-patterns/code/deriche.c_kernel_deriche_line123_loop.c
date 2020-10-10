#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int j;
extern int h;
extern float tm1;
extern float ym1;
extern float ym2;
extern int i;
extern int w;
extern float  y1[4096 + 0][2160 + 0] ;
extern float a5;
extern float  imgOut[4096 + 0][2160 + 0] ;
extern float a6;
extern float b1;
extern float b2;

void loop()
{
#pragma scop

    for(j = 0; j < h; j++)
    {
        tm1 = 0.0f;
        ym1 = 0.0f;
        ym2 = 0.0f;
        for(i = 0; i < w; i++)
        {
            y1[i][j] = a5 * imgOut[i][j] + a6 * tm1 + b1 * ym1 + b2 * ym2;
            tm1 = imgOut[i][j];
            ym2 = ym1;
            ym1 = y1[i][j];
        }
    }

#pragma endscop
}
