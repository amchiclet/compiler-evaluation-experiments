#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int j;
extern int coded_picture_height;
extern int i;
extern int w;
extern int i2;
extern int im3;
extern int im2;
extern int im1;
extern int ip1;
extern int ip2;
extern int ip3;
extern unsigned char * restrict dst;
extern unsigned char * restrict clp;
extern unsigned char * restrict src;
extern int coded_picture_width;

void loop()
{
#pragma scop

    for(j = 0; j < coded_picture_height; j++)
    {
        for(i = 0; i < w; i++)
        {
            i2 = i << 1;
            im3 =(i < 3?0 : i - 3);
            im2 =(i < 2?0 : i - 2);
            im1 =(i < 1?0 : i - 1);
            ip1 =(i < w - 1?i + 1 : w - 1);
            ip2 =(i < w - 2?i + 2 : w - 1);
            ip3 =(i < w - 3?i + 3 : w - 1);
            dst[i2] = clp[((int )(5 * src[im3] - 21 * src[im2] + 70 * src[im1] + 228 * src[i] - 37 * src[ip1] + 11 * src[ip2] + 128)) >> 8];
            dst[i2 + 1] = clp[((int )(5 * src[ip3] - 21 * src[ip2] + 70 * src[ip1] + 228 * src[i] - 37 * src[im1] + 11 * src[im2] + 128)) >> 8];
        }
        src += w;
        dst += coded_picture_width;
    }

#pragma endscop
}
