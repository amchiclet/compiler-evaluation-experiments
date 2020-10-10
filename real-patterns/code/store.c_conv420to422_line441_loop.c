#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int i;
extern int w;
extern int j;
extern int h;
extern int j2;
extern int jm3;
extern int jm2;
extern int jm1;
extern int jp1;
extern int jp2;
extern int jp3;
extern unsigned char * restrict dst;
extern unsigned char * restrict clp;
extern unsigned char * restrict src;

void loop()
{
#pragma scop

    for(i = 0; i < w; i++)
    {
        for(j = 0; j < h; j++)
        {
            j2 = j << 1;
            jm3 =(j < 3?0 : j - 3);
            jm2 =(j < 2?0 : j - 2);
            jm1 =(j < 1?0 : j - 1);
            jp1 =(j < h - 1?j + 1 : h - 1);
            jp2 =(j < h - 2?j + 2 : h - 1);
            jp3 =(j < h - 3?j + 3 : h - 1);
            dst[w * j2] = clp[((int )(3 * src[w * jm3] - 16 * src[w * jm2] + 67 * src[w * jm1] + 227 * src[w * j] - 32 * src[w * jp1] + 7 * src[w * jp2] + 128)) >> 8];
            dst[w *(j2 + 1)] = clp[((int )(3 * src[w * jp3] - 16 * src[w * jp2] + 67 * src[w * jp1] + 227 * src[w * j] - 32 * src[w * jm1] + 7 * src[w * jm2] + 128)) >> 8];
        }
        src++;
        dst++;
    }

#pragma endscop
}
