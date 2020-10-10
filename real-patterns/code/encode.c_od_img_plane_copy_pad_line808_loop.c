#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int y;
extern int pic_height;
extern int plane_height;
extern int dst_xstride;
extern int x;
extern int plane_width;
extern unsigned char * restrict dst_data;
extern int dst_ystride;
typedef unsigned short uint16_t;

void loop()
{
#pragma scop

    for(y = pic_height; y < plane_height; y++)
    {
        if(dst_xstride == 1)
        {
            for(x = 0; x < plane_width; x++)
            {
                unsigned char uppercase_l;
                unsigned char uppercase_c;
                unsigned char uppercase_r;
                uppercase_c =(dst_data - dst_ystride)[x];
                uppercase_l =(dst_data - dst_ystride)[x -(x > 0)];
                uppercase_r =(dst_data - dst_ystride)[x +(x + 1 < plane_width)];
                dst_data[x] =(2 * uppercase_c + uppercase_l + uppercase_r + 2 >> 2);
            }
        }
        else
        {
            for(x = 0; x < plane_width; x++)
            {
                uint16_t uppercase_l;
                uint16_t uppercase_c;
                uint16_t uppercase_r;
                uppercase_c =((uint16_t *)(dst_data - dst_ystride))[x];
                uppercase_l =((uint16_t *)(dst_data - dst_ystride))[x -(x > 0)];
                uppercase_r =((uint16_t *)(dst_data - dst_ystride))[x +(x + 1 < plane_width)];
                ((uint16_t *)dst_data)[x] =(2 * uppercase_c + uppercase_l + uppercase_r + 2 >> 2);
            }
        }
        dst_data += dst_ystride;
    }

#pragma endscop
}
