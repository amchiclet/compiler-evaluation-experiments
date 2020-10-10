#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int y;
extern int vert_padding;
extern int x;
extern int plane_width;
extern int horz_padding;
typedef long ptrdiff_t;
extern ptrdiff_t xstride;
extern unsigned char * restrict dst;
extern ptrdiff_t ystride;

void loop()
{
#pragma scop

    for(y = 0; y < vert_padding; y++)
    {
        for(x = 0; x <(plane_width + 2 * horz_padding) * xstride; x++)
        {
            (dst - ystride)[x] = dst[x];
        }
        dst -= ystride;
    }

#pragma endscop
}
