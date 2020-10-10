#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int i;
extern int x;
extern short * restrict src;
extern int d;
extern unsigned char * restrict quant_mat;
extern int y;
extern int mquant;
extern int mpeg1;
extern short * restrict dst;
extern int nzflag;

void loop()
{
#pragma scop

    for(i = 0; i < 64; i++)
    {
        x = src[i];
        d = quant_mat[i];
        y =(32 *((x >= 0?x : -x)) +(d >> 1)) / d;
        y /= 2 * mquant;
        if(y > 255)
        {
            if(mpeg1) y = 255;
            else if(y > 2047) y = 2047;
        }
        if((dst[i] =((x >= 0?y : -y))) != 0) nzflag = 1;
    }

#pragma endscop
}
