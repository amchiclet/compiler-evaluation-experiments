#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int i;
extern int w;
extern int j;
extern int h;
extern float  imgIn[4096 + 0][2160 + 0] ;

void loop()
{
#pragma scop

    for(i = 0; i < w; i++) for(j = 0; j < h; j++) imgIn[i][j] =((float )((313 * i + 991 * j) % 65536)) / 65535.0f;

#pragma endscop
}
