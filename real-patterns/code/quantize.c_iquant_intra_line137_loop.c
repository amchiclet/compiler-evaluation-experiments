#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int i;
extern int val;
extern short * restrict src;
extern unsigned char * restrict quant_mat;
extern int mquant;
extern int sum;
extern short * restrict dst;

void loop()
{
#pragma scop

    for(i = 1; i < 64; i++)
    {
        val =((int )(src[i] * quant_mat[i] * mquant)) / 16;
        sum +=(dst[i] =((val > 2047?2047 :((val < - 2048?- 2048 : val)))));
    }

#pragma endscop
}
