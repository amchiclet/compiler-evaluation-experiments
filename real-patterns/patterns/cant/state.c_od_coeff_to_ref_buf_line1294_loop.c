#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int y;
extern int h;
extern int x;
extern int w;
extern unsigned char * restrict dst;
typedef int int32_t;
typedef int32_t od_coeff;
extern od_coeff * restrict src;
extern int coeff_shift;
extern int dst_ystride;
extern int src_ystride;

void loop()
{
#pragma scop

    for(y = 0; y < h; y++)
    {
        for(x = 0; x < w; x++)
        {
            *(dst + x) =((unsigned char )(((src[x] +(1 << coeff_shift >> 1) >> coeff_shift) + 128 < 0) - 1 &((src[x] +(1 << coeff_shift >> 1) >> coeff_shift) + 128 | -((src[x] +(1 << coeff_shift >> 1) >> coeff_shift) + 128 > 255))));
        }
        dst += dst_ystride;
        src += src_ystride;
    }

#pragma endscop
}
