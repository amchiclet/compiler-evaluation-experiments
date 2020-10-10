#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int j;
extern int height;
extern int i;
extern int width;
extern int im5;
extern int im3;
extern int im1;
extern int ip1;
extern int ip3;
extern int ip5;
extern unsigned char * restrict dst;
extern unsigned char * restrict clp;
extern unsigned char * restrict src;

void loop()
{
#pragma scop

    for(j = 0; j < height; j++)
    {
        for(i = 0; i < width; i += 2)
        {
            im5 =(i < 5?0 : i - 5);
            im3 =(i < 3?0 : i - 3);
            im1 =(i < 1?0 : i - 1);
            ip1 =(i < width - 1?i + 1 : width - 1);
            ip3 =(i < width - 3?i + 3 : width - 1);
            ip5 =(i < width - 5?i + 5 : width - 1);
            dst[i >> 1] = clp[((int )(22 *(src[im5] + src[ip5]) - 52 *(src[im3] + src[ip3]) + 159 *(src[im1] + src[ip1]) + 256 * src[i] + 256)) >> 9];
        }
        src += width;
        dst += width >> 1;
    }

#pragma endscop
}
