#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
typedef unsigned int png_uint_32;
extern png_uint_32 i;
extern png_uint_32 row_width;
extern int value;
typedef unsigned char png_byte;
typedef png_byte * png_bytep;
extern png_bytep restrict sp;
extern int shift;
extern png_bytep restrict dp;

void loop()
{
#pragma scop

    for(i = 0; i < row_width; i++)
    {
        value =( *sp) >> shift & 0x03;
        *dp =((png_byte )value);
        if(shift == 6)
        {
            shift = 0;
            sp--;
        }
        else shift += 2;
        dp--;
    }

#pragma endscop
}
