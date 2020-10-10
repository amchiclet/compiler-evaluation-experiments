#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int i;
extern int w;
extern int j;
extern int height;
extern int jm5;
extern int jm4;
extern int jm3;
extern int jm2;
extern int jm1;
extern int jp1;
extern int jp2;
extern int jp3;
extern int jp4;
extern int jp5;
extern int jp6;
extern unsigned char * restrict dst;
extern unsigned char * restrict clp;
extern unsigned char * restrict src;

void loop()
{
#pragma scop

    for(i = 0; i < w; i++)
    {
        for(j = 0; j < height; j += 2)
        {
            jm5 =(j < 5?0 : j - 5);
            jm4 =(j < 4?0 : j - 4);
            jm3 =(j < 3?0 : j - 3);
            jm2 =(j < 2?0 : j - 2);
            jm1 =(j < 1?0 : j - 1);
            jp1 =(j < height - 1?j + 1 : height - 1);
            jp2 =(j < height - 2?j + 2 : height - 1);
            jp3 =(j < height - 3?j + 3 : height - 1);
            jp4 =(j < height - 4?j + 4 : height - 1);
            jp5 =(j < height - 5?j + 5 : height - 1);
            jp6 =(j < height - 5?j + 6 : height - 1);
            dst[w *(j >> 1)] = clp[((int )(228 *(src[w * j] + src[w * jp1]) + 70 *(src[w * jm1] + src[w * jp2]) - 37 *(src[w * jm2] + src[w * jp3]) - 21 *(src[w * jm3] + src[w * jp4]) + 11 *(src[w * jm4] + src[w * jp5]) + 5 *(src[w * jm5] + src[w * jp6]) + 256)) >> 9];
        }
        src++;
        dst++;
    }

#pragma endscop
}
