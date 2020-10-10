#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
typedef unsigned int png_uint_32;
extern png_uint_32 i;
extern png_uint_32 row_width;
typedef unsigned char png_byte;
typedef png_byte * png_bytep;
extern png_bytep restrict sp;
extern int v;
extern int mask;
extern png_bytep restrict dp;

void loop()
{
#pragma scop

    for(i = 0; i < row_width; i++)
    {
        if(( *sp) != 0) v |= mask;
        sp++;
        if(mask > 1) mask >>= 1;
        else
        {
            mask = 0x80;
            *dp =((png_byte )v);
            dp++;
            v = 0;
        }
    }

#pragma endscop
}
