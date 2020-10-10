#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int i;
extern int h;
extern int j;
extern int w;
extern int  tmp[16 * 16] ;
typedef unsigned char uint8_t;
extern uint8_t * restrict pix1;
extern uint8_t * restrict pix2;
extern int line_size;

void loop()
{
#pragma scop

    for(i = 0; i < h; i++)
    {
        for(j = 0; j < w; j += 4)
        {
            tmp[16 * i + j + 0] = pix1[j + 0] - pix2[j + 0] << 4;
            tmp[16 * i + j + 1] = pix1[j + 1] - pix2[j + 1] << 4;
            tmp[16 * i + j + 2] = pix1[j + 2] - pix2[j + 2] << 4;
            tmp[16 * i + j + 3] = pix1[j + 3] - pix2[j + 3] << 4;
        }
        pix1 += line_size;
        pix2 += line_size;
    }

#pragma endscop
}
