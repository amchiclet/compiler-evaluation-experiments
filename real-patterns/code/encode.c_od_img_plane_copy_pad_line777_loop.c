#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int x;
extern int pic_width;
extern int plane_width;
extern unsigned char * restrict dst_data;
struct daala_image_plane
{
    unsigned char *data;
    unsigned char xdec;
    unsigned char ydec;
    int xstride;
    int ystride;
    int bitdepth;
};

typedef struct daala_image_plane daala_image_plane;
extern daala_image_plane * restrict dst_p;
extern int dst_xstride;
extern int y;
extern int pic_height;
extern int dst_ystride;
typedef unsigned short uint16_t;

void loop()
{
#pragma scop

    for(x = pic_width; x < plane_width; x++)
    {
        dst_data = dst_p -> data +(x - 1) * dst_xstride;
        if(dst_xstride == 1)
        {
            for(y = 0; y < pic_height; y++)
            {
                unsigned char uppercase_u;
                unsigned char uppercase_c;
                unsigned char uppercase_d;
                uppercase_c = *dst_data;
                uppercase_u = *(dst_data -(dst_ystride & -(y > 0)));
                uppercase_d = *(dst_data +(dst_ystride & -(y + 1 < pic_height)));
                dst_data[1] =(2 * uppercase_c + uppercase_u + uppercase_d + 2 >> 2);
                dst_data += dst_ystride;
            }
        }
        else
        {
            for(y = 0; y < pic_height; y++)
            {
                uint16_t uppercase_u;
                uint16_t uppercase_c;
                uint16_t uppercase_d;
                uppercase_c = *((uint16_t *)dst_data);
                uppercase_u = *((uint16_t *)(dst_data -(dst_ystride & -(y > 0))));
                uppercase_d = *((uint16_t *)(dst_data +(dst_ystride & -(y + 1 < pic_height))));
                ((uint16_t *)dst_data)[1] =(2 * uppercase_c + uppercase_u + uppercase_d + 2 >> 2);
                dst_data += dst_ystride;
            }
        }
    }

#pragma endscop
}
