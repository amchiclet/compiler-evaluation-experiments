#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int i;
extern int w;
extern int j;
extern int h;
extern float  imgOut[4096 + 0][2160 + 0] ;
extern float c1;
extern float  y1[4096 + 0][2160 + 0] ;
extern float  y2[4096 + 0][2160 + 0] ;

void loop()
{
#pragma scop

    for(i = 0; i < w; i++) for(j = 0; j < h; j++)
        {
            imgOut[i][j] = c1 *(y1[i][j] + y2[i][j]);
        }

#pragma endscop
}
