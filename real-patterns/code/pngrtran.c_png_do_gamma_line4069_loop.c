#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
typedef unsigned int png_uint_32;
extern png_uint_32 i;
extern png_uint_32 row_width;
typedef unsigned char png_byte;
typedef png_byte * png_bytep;
extern png_bytep restrict sp;
typedef const png_byte * png_const_bytep;
extern png_const_bytep restrict gamma_table;

void loop()
{
#pragma scop

    for(i = 0; i < row_width; i += 4)
    {
        int a =( *sp) & 0xc0;
        int b =( *sp) & 0x30;
        int c =( *sp) & 0x0c;
        int d =( *sp) & 0x03;
        *sp =((png_byte )(((int )gamma_table[a | a >> 2 | a >> 4 | a >> 6]) & 0xc0 |((int )gamma_table[b << 2 | b | b >> 2 | b >> 4]) >> 2 & 0x30 |((int )gamma_table[c << 4 | c << 2 | c | c >> 2]) >> 4 & 0x0c |((int )gamma_table[d << 6 | d << 4 | d << 2 | d]) >> 6));
        sp++;
    }

#pragma endscop
}
