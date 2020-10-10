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
extern unsigned int shift;
extern png_bytep restrict dp;

void loop()
{
#pragma scop

    for(i = 0; i < row_width; i++)
    {
        png_byte value;
        value =((png_byte )(( *sp) & 0x0f));
        v |= value << shift;
        if(shift == 0)
        {
            shift = 4;
            *dp =((png_byte )v);
            dp++;
            v = 0;
        }
        else shift -= 4;
        sp++;
    }

#pragma endscop
}
